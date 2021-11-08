#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <stack>
#include <vector>
#include <unordered_map>
#include <cmath>


namespace s8_exam_problems {
	using namespace std::literals;	
	//SEND ID: 56280301

	// A_PackedPrefix method that unpacks strings and find common prefix for all strings
	// This method is two-step: On first step it unpack strings and on the second step it compares prefix.
	// Note: Full unpacking (in size of first string) is required only for first two strings. After that, program calculates 
	// their common prefix and unpacks only begining of next string limited by this common prefix size. No need to unpack or compare sufix
	// of string in this way. Prefix size redefinition is executed in cycle right after of unpacking of new string from vector of strings.
	// 
	//		Time Complexity: O(D) - overall length of all input strings, where's D = N * L:  N - count of strings, L - length of exact string
	//							+ O(K) - overall sum of mupltiplication of packed substring. Necessary for unpacking substrings several times in cycle
	//							+ O(M) - count of ']' brackets in all N input strings, necessary to limit reading of chars in packed substring area
	//							+ O(N * J) - comparing strings prefixes at every unpacking of new string, where's N - count of strings, 
	//														J - size(variable) of laready defined prefix. Can be reduced at every step
	//					Overall: O(D + K + M + N * J)
	// 
	//		Space Complexity: additional memory:
	//				- UnpackPrefix() - O(M), where's M - size of unpacked string. May be limited by pref parameter.
	//				- A_PackedPrefix() - O(N * M), where's N - count of strings, M -size of exact unpacked string (can be limited by pref during parsing process)
	//

	template <typename Type>
	void RemoveElemFromStack(std::stack<Type>& stack) {
		if (stack.size() > 0) { // in some conditions UnpackPrefix may try to remove elem from empty stack
			stack.pop();
		}
	}

	template <typename Type>
	std::string NewStringForStack(std::string&& tmp, std::stack<Type>& stack) {
		std::string st_str = ((stack.size() > 0) ? stack.top() : ""s); // merge current packed substring with previous part of string
		RemoveElemFromStack(stack); // stack may be empty here		
		return st_str + std::move(tmp);
	}

	std::string ReadSubStringFromLetters(const std::string& str, int& idx) {
		std::string tmp;
		while (!std::isdigit(str[idx]) && str[idx] != ']' && idx < str.size()) { // collect begining of packed substring or entire string
			tmp.push_back(str[idx]);
			++idx;
		}
		--idx; // step back on symbol-reason of cycle interruption
		return tmp;
	}

	std::string UnpackPrefix(const std::string& str, int size_to_get) {
		std::string res;

		std::stack<std::string> stack; // substring stack
		std::stack<int> stack_num; // multipliers stack
		
		for (int i = 0; i < str.size(); ++i) {	
			std::string tmp;
			if (std::isdigit(str[i])) {
				stack_num.push(str[i] - 48); // add multiplie into stack_num			
				continue; // next step
			}
			else if (str[i] == '[') { // packed string was found.				
				if (std::isdigit(str[i])) { //if digit right after '['  
					stack.push(""s); // insert empty str in stack
					continue; // next step
				}
				else {
					++i; // skip '['
					tmp = ReadSubStringFromLetters(str, i);
					stack.push(tmp); // insert begining of packed string in stack						
				}
			}
			else if (str[i] == ']') { // merging of packed substring is required
				int n = stack_num.top(); // count of repeats
				std::string st_str = stack.top(); // packed substring that will be repeated
				stack_num.pop();
				stack.pop(); 				
				for (int i = 0; i < n; ++i) { // repeat packed substring
					tmp += st_str;
				}
				stack.push(NewStringForStack(std::move(tmp), stack)); // pushing back the value.
							
			}
			else { //string begins from letters or packed substring has structure like 2[abc1[def]ghi]. ghi letters will be read here.
				tmp = ReadSubStringFromLetters(str, i);	// collect string exists from letters		
				stack.push(NewStringForStack(std::move(tmp), stack)); // pushing back the value.		
			}
			
			if (stack.size() == 1 && stack_num.size() == 0 && stack.top().size() >= size_to_get && size_to_get != -1) { 
				// no need to parse full string if we have already parsed substring 
				// that exceeds common prefix of other (already checked) strings
				break;
			}			
		}
		return stack.top();
	}

	void A_PackedPrefix(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<std::string> vec;		
		int pref = -1; // size of prefix. Reduces at every compare of strings (only equal previous prefixes are considering in new strings
		vec.reserve(n);
		for (int i = 0; i < n; ++i) {
			std::string tmp;
			input >> tmp;
			vec.push_back(UnpackPrefix(tmp, pref));
			if (i == 0) {
				pref = vec[0].size(); // pref is equal to size of first string in the begining
			}
			else {				
				int j = 0;
				while (j < pref) { // check only symbols that are included in common pref range
					if (vec[0][j] != vec[i][j]) { // mismatch of symbols. Need to decrease common pref range
						pref = j;
					}
					++j;
				}
			}
		}
				
		output << vec[0].substr(0, pref) << '\n';
	}
	/*-------------------------------------------------------------------------*/
	//SEND ID: 56279042

	// B_CheatSheet method that define if query can be assembled from other words. Words can be repeated any times.
	// Dynamic programming method was used for solving this problem. Hash values were got for all words for comparing them
	// with Hash of query's substrings. In case of hashes similarity and it's lengths - program add pointer into dp vector.
	// These pointers mean that all previous query prefix can be accumulated by using words. Pointer points next to prefix range. 
	// That's why dp vector size is +1 bigger than query size. If pointer shows that program has reached symbol next to last query symbol -
	// it means that whole query can be accumulated from words and no need to continue execution.
	//
	// Time Complexity: 
	//		- B_CheatSheet() - O(D) - get hash values for words, where's D = J * L : J - count of words, L - length(variable) of word
	//							+ O(K) - get pows of a ratio for calculating query substring, where's K - size of query string
	//							+ O(K) - calculation of prefix hashes for query, where's K - size of query string
	//							+ O(K * J) - filling dp vector (worst case when all query consists of unique repeated char and this char is in list of words),
	//											where's K - size of query string, J - count of words.
	//						Overall: O(D + K * (J + 2)) or O(D + K * J)
	// 
	//			- GetPrefixHashes() - O(N), where's N - size of input string
	//			- GetWordHash() - O(N), the same as GetPrefixHashes()
	//			- GetPowsOfA() - O(K), where's K - size of query string
	//			- GetSubStrHash() - O(1), thanks to preliminary calculation
	// 
	//	Space Complexity:
	//		- B_CheatSheet() - additional memory: O(J) - word's hashes, where' J - count of words
	//												+ O(K) - poes of a ratio, where's K - size of query
	//												+ O(K) - prefix hashes of query, where's K - size of query
	//												+ O(K) - dp vector values, where's K - size f query
	//							Overall: O(J + 3K)
	//


	std::vector<int64_t> GetPrefixHashes(const std::string& str, int64_t a, int64_t m) {
		std::vector<int64_t> pref_hashes;
		pref_hashes.reserve(str.size());
		pref_hashes.push_back(0);		
		for (size_t i = 0; i < str.size(); ++i) {
			pref_hashes.push_back((pref_hashes[i] * a + str[i]) % m);
		}
		return pref_hashes; // get prefix hashes of string
	}

	int64_t GetWordHash(const std::string& str, int64_t a , int64_t m) {
		std::vector<int64_t> pref_hashes = GetPrefixHashes(str, a, m);		
		return pref_hashes.back(); // get prefix hash for whole string
	}

	std::vector<int64_t> GetPowsOfA(int size, int64_t a, int64_t m) { // generates vector of a pows for GetSubStrHash
		std::vector<int64_t> pow_of_a;
		pow_of_a.reserve(size);
		pow_of_a.push_back(1);
		for (size_t i = 1; i <=size; ++i) {
			pow_of_a.push_back(pow_of_a[i - 1] * a % m);
		}
		return pow_of_a;
	}

	int64_t GetSubStrHash (size_t from, size_t to, const std::vector<int64_t>& pref_hashes, 
							const std::vector<int64_t>& pows_of_a, int64_t m) {
		int64_t hash = (pref_hashes[to] - pref_hashes[from] * pows_of_a[to - from]) % m; // get hash for substring
		if (hash < 0) {
			hash += m;
		}
		return hash;
	}
	
	void B_CheatSheet(std::istream& input, std::ostream& output) {
		std::string query;
		int n;
		input >> query >> n;

		std::vector<std::string> words; 
		words.reserve(n);
		for (int i = 0; i < n; ++i) {
			std::string tmp;
			input >> tmp;
			words.push_back(tmp);
		}

		int64_t a = 1'000'000'007;
		int64_t m = std::pow(2, 32);
		std::vector<int64_t> pows_of_a = GetPowsOfA(query.size(), a, m); // vec of coef a pows for extracting substring hash from query
		std::unordered_map<int64_t, size_t> words_hashes; // map for storage word hash / word size pairs
		words_hashes.reserve(n);
		for (const std::string& str : words) {
			words_hashes[GetWordHash(str, a, m)] = str.size();
		}

		std::vector<int64_t> query_pref_hashes = GetPrefixHashes(query, a, m); // calculate query prefix hashes

		std::vector<bool> dp(query.size() + 1, false);  // size() + 1 - position right after last char
		dp[0] = true; // initial point for filling dp vector
		for (int i = 0; i < dp.size(); ++i) { // check all chars in query
			if (dp[i]) { // we have a route till this char from the begining
				for (auto& elem : words_hashes) { // check all words by hash comprasion of word itself and substring of query with size equal to word's size
					if (i + elem.second < dp.size() && elem.first == GetSubStrHash(i, i + elem.second, query_pref_hashes, pows_of_a, m)) { // limit of checking elements. Prevent out of range exception					
						dp[i + elem.second] = true; // word's hash and query substring hash are equal. Mark for checking next char later						
					}
				}
			}
			if (dp.back()) { // if we already have route till the last char, no need to continue
				break;
			}
		}

		if (dp.back()) {
			output << "YES"s << '\n';
		}
		else {
			output << "NO"s << '\n';
		}
	}
}

namespace s8_exam_tests {
	using namespace std::literals;
	using namespace s8_exam_problems;

	void A_PackedPrefix() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "abacabaca"s << '\n'
				<< "2[abac]a"s << '\n'
				<< "3[aba]"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::A_PackedPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "aba"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "3[a]2[r2[t]]"s << '\n'
				<< "2[a]2[ab]"s << '\n'
				<< "a2[aa3[b]]"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::A_PackedPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "aaa"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::string str("2[1[emgu]]"s);
			std::string res = s8_exam_problems::UnpackPrefix(str, 0);
			assert(res == "emguemgu"s);
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "jwcnjwcnemguemgu2[ctr]2[1[cnma]3[y]2[b]3[v]3[gas]]3[oc]"s << '\n'
				<< "2[jwcn]2[1[emgu]]1[bzgy]"s << '\n'				
				<< "jwcnjwcnemguemgu2[2[mou]1[y]2[dd]]1[1[ynt]]1[nnq]2[qfw]2[e]1[1[k]1[utz]1[fal]2[g]]"s << '\n'
				<< "jwcnjwcnemguemgu1[j]3[2[h]3[iqd]3[xen]1[ia]]2[3[i]]2[li]"s << '\n'
				<< "2[jwcn]2[1[emgu]]2[whub]3[qdrz]3[3[potn]2[l]1[wc]1[snzs]]1[3[u]3[myi]2[fdk]2[ot]]2[qp]"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::A_PackedPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "jwcnjwcnemguemgu"s << '\n';
			assert(output.str() == res.str());
		}
		
		
	}
	/*-------------------------------------------------------------------------*/
	void B_CheatSheet() {
		{
			std::stringstream input;
			input << "theexamiwillpasstheexam"s << '\n'
				<< "5"s << '\n'
				<< "will"s << '\n'
				<< "pass"s << '\n'
				<< "the"s << '\n'
				<< "exam"s << '\n'
				<< "i"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::B_CheatSheet(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abacaba"s << '\n'
				<< "2"s << '\n'
				<< "abac"s << '\n'
				<< "caba"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::B_CheatSheet(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abacaba"s << '\n'
				<< "3"s << '\n'
				<< "abac"s << '\n'
				<< "caba"s << '\n'
				<< "aba"s;
			std::ostringstream output(std::ios_base::ate);
			s8_exam_problems::B_CheatSheet(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
	}

}