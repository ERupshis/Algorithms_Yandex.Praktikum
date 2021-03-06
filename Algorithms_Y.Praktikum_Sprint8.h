#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cmath>

namespace s8_problems {
	using namespace std::literals;
	
	void PrintSpace(std::ostream& output, bool& f) {
		if (f) {
			output << ' ';
		}
		else {
			f = true;
		}
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int> A_HashVector(const std::string& str) {
		std::unordered_map<char, int> hash_map;
		std::vector<int> res;

		for (int i = 0; i < str.size(); ++i) {
			if (!hash_map.count(str[i])) {
				hash_map[str[i]] = hash_map.size();
			}

			res.push_back(hash_map[str[i]]);
		}
		return res;
	}

	void A_StrangeComprasion(std::istream& input, std::ostream& output) {
		std::string str1, str2;
		input >> str1 >> str2;

		if (A_HashVector(str1) == A_HashVector(str2)) {
			output << "YES"s << '\n';
		}
		else {
			output << "NO"s << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_StringReverse(std::istream& input, std::ostream& output) {
		std::stack<std::string> stack;
		std::string str;
		while (input >> str) {
			stack.push(str);
		}

		bool f = false;
		while (stack.size() > 0) {
			PrintSpace(output, f);
			output << stack.top();
			stack.pop();
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/
	void C_BorderControl(std::istream& input, std::ostream& output) {
		std::string str1, str2;
		input >> str1 >> str2;

		if (std::abs(static_cast<int>(str1.size() - str2.size())) > 1) {
			output << "FAIL"s << '\n';
			return;
		}

		int l1 = 0, l2 = 0, diff = 0;
		while (l1 < str1.size() && l2 < str2.size()) {

			if (str1[l1] != str2[l2]) {
				if (str1[l1 + 1] == str2[l2]) {
					++l1;
				}
				else if (str1[l1] == str2[l2 + 1]) {
					++l2;
				}
				else if (str1[l1 + 1] == str2[l2 + 1]) {
					++l1;
					++l2;
				}
				else { // second seq symbol incorrect
					++diff;
				}
				++diff;
			}
			else {
				++l1;
				++l2;
			}
			if (diff >= 2) {
				output << "FAIL"s << '\n';
				return;
			}
		}
		if (str1.size() != l1 || str2.size() != l2 && diff > 0) {
			output << "FAIL"s << '\n';
			return;
		}
		output << "OK"s << '\n';
	}
	/*-------------------------------------------------------------------------*/
	void D_BiggestPalindrome(std::istream& input, std::ostream& output) {
		std::string str;
		input >> str;

		std::vector<int> vec(26);
		for (int i = 0; i < str.size(); ++i) {
			++vec[str[i] - 97];
		}
		char pivot = static_cast<char>(0);
		std::string left;
		for (int i = 0; i < vec.size(); ++i) {
			char ch = static_cast<char>(97 + i);
			if (pivot == static_cast<char>(0) && vec[i] % 2 == 1) {
				pivot = ch;
			}			
			left.insert(left.size(), (vec[i] / 2), ch);
		}	
		std::string right{ left };
		std::reverse(right.begin(), right.end());
		if (pivot != '\0') {
			output << left << pivot << right << '\n';
		}
		else {
			output << left << right << '\n';
		}		
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int64_t> PrefixHashes(const std::string& str) {
		int64_t a = 1'000'000'007;
		int64_t m = std::pow(2, 32);
			
		std::vector<int64_t> pref_hashes;

		pref_hashes.reserve(str.size());
		pref_hashes.push_back(0);
		int64_t hash = 0;
		for (size_t i = 0; i < str.size(); ++i) {
			pref_hashes.push_back((pref_hashes[i] * a + str[i]) % m);
		}		
		return pref_hashes;
	}

	int ComparePrefixHashes(const std::string& str, int to_check, const std::vector<int64_t> prefix_hashes) {
		int64_t a = 1'000'000'007;
		int64_t m = std::pow(2, 32);

		std::vector<int64_t> pref_hashes;

		pref_hashes.reserve(str.size());
		pref_hashes.push_back(0);
		int64_t hash = 0;
		for (size_t i = 0; i < std::min(static_cast<int>(str.size()), to_check); ++i) {			
			pref_hashes.push_back((pref_hashes[i] * a + str[i]) % m);
			if (prefix_hashes[i + 1] != pref_hashes[i + 1]) {
				return i;
			}
		}
		return std::min(to_check, static_cast<int>(str.size()));
	}

	void E_CommonPrefix(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<std::string> vec;
		vec.reserve(n);
		for (int i = 0; i < n; ++i) {
			std::string tmp;
			input >> tmp;
			vec.push_back(tmp);
		}
		
		std::vector<int64_t> prefix_hash = PrefixHashes(vec[0]);
		int pref = vec[0].size();
		for (int i = 1; i < vec.size(); ++i) {
			pref = ComparePrefixHashes(vec[i], pref, prefix_hash);
			if (pref == 0) {
				output << "0"s;
				return;
			}			
		}
		output << pref;
	}
	/*-------------------------------------------------------------------------*/
	struct SubStr {
		std::string str = ""s;
		int idx = 0;

		bool operator<(const SubStr& other) {
			return idx < other.idx;
		}
	};
	
	void F_StringInsert(std::istream& input, std::ostream& output) {
		std::string str;
		input >> str;
		
		int n;
		input >> n;
		std::vector<SubStr> vec_substr(n);
		for (int i = 0; i < n; ++i) {
			SubStr tmp;			
			input >> tmp.str >> tmp.idx;
			vec_substr[i] = tmp;
		}
		std::sort(vec_substr.begin(), vec_substr.end());

		output << str.substr(0, vec_substr[0].idx);
		for (int i = 0; i < vec_substr.size() - 1; ++i) {
			output << vec_substr[i].str;
			output << str.substr(vec_substr[i].idx, vec_substr[i + 1].idx - vec_substr[i].idx);
		}
		output << vec_substr[vec_substr.size() - 1].str;
		output << str.substr(vec_substr[vec_substr.size() - 1].idx, str.size()) << '\n';		
	}
	/*-------------------------------------------------------------------------*/
	void G_MostFreqWord(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::unordered_map<std::string, int> unord_map;
		for (int i = 0; i < n; ++i) {
			std::string tmp;
			input >> tmp;
			unord_map[tmp] += 1;
		}

		std::vector<std::string> res_words;
		int word_freq = 0;
		for (auto& elem : unord_map) {
			if (elem.second > word_freq) {
				res_words.clear();
				res_words.push_back(elem.first);
				word_freq = elem.second;
			}
			else if (elem.second == word_freq) {
				res_words.push_back(elem.first);
			}
		}

		if (res_words.size() != 1) {
			std::sort(res_words.begin(), res_words.end(), std::less<std::string>{});
		}
		output << res_words[0] << '\n';
	}
	/*-------------------------------------------------------------------------*/
	int Find(const std::vector<int>& vec, const std::vector<int>& pattern, int s = 0) {
		if (vec.size() < pattern.size()) {
			return -1;
		}
		for (int pos = s; pos < vec.size() - pattern.size() + 1; ++pos) {
			int match = true;
			int c = vec[pos] - pattern[0];
			for (int offset = 0; offset < pattern.size(); ++offset) {
				if (vec[pos + offset] != pattern[offset] + c) {
					match = false;
					break;
				}
			}
			if (match) {
				return pos;
			}
		}
		return -1;
	}

	std::vector<int> FindAll(const std::vector<int>& vec, const std::vector<int>& pattern) {
		std::vector<int> res;
		int s = 0;
		int pos = -1;
		while ((pos = Find(vec, pattern, s)) != -1) {
			res.push_back(pos + 1);
			s = pos + 1;
		}
		return res;
	}


	void H_ShiftSearch(std::istream& input, std::ostream& output) {
		int n, m;
		input >> n;

		std::vector<int> vec;
		vec.reserve(n);
		for (int i = 0; i < n; ++i) {
			int num;
			input >> num;
			vec.push_back(num);
		}

		input >> m;
		std::vector<int> pattern;
		pattern.reserve(m);
		for (int i = 0; i < m; ++i) {
			int num;
			input >> num;
			pattern.push_back(num);
		}

		std::vector<int> res = FindAll(vec, pattern);
		bool f = false;
		for (int i = 0; i < res.size(); ++i) {
			PrintSpace(output, f);
			output << res[i];
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int> Search(const std::string& str, const std::string& pattern) {
		std::vector<int> res;
		std::string tmp = pattern + '#' + str;

		std::vector<int> pref_func(pattern.size());
		int pref_prev = 0;
		for (int i = 1; i < tmp.size(); ++i) {
			int k = pref_prev;
			while (k > 0 && tmp[i] != tmp[k]) {
				k = pref_func[k - 1];
			}
			if (tmp[k] == tmp[i]) {
				++k;
			}
			if (i < pattern.size()) {
				pref_func[i] = k;
			}
			pref_prev = k;
			if (k == pattern.size()) {
				res.push_back(i - 2 * pattern.size());
			}
		}
		return res;
	}

	void I_GlobalChange(std::istream& input, std::ostream& output) {
		std::string str, patt, change_patt;
		input >> str >> patt >> change_patt;

		std::vector<int> occur = Search(str, patt);

		int ptr = 0;
		for (int i = 0; i < occur.size(); ++i) {
			if (ptr != occur[i]) {
				output << str.substr(ptr, occur[i] - ptr);
				ptr = occur[i];
			}
			output << change_patt;
			ptr += patt.size();
		}
		if (ptr < str.size()) {
			output << str.substr(ptr);
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/
	void J_Repeat(std::istream& input, std::ostream& output) {
		std::string str;
		input >> str;

		std::string repeat;
		for (int i = 0; i < str.size(); ++i) {
			repeat.push_back(str[i]);
			if (i >= str.size() / 2) {
				break;
			}
			if (str.size() % repeat.size() != 0) {
				continue;
			}
			
			int k = i + 1;
			while (k <= str.size() && repeat == str.substr(k, repeat.size())) {
				k += repeat.size();
			}
			if (k == str.size()) {
				output << str.size() / repeat.size() << '\n';
				return;
			}
			
		}
		output << 1 << '\n';
	}
	/*-------------------------------------------------------------------------*/
	struct Node {
		bool terminal = false;
		std::unordered_map<char, Node*> links;
		std::vector<std::string> data;
	};

	Node* FindNode(Node* root, std::string str) {
		Node* curr_node = root;
		for (int i = 0; i < str.size(); ++i) {
			char symbol = str[i];
			if (curr_node->links.count(symbol) == 0) {
				return nullptr;
			}
			curr_node = curr_node->links.at(symbol);
		}
		return curr_node;
	}

	Node* AddString(Node* root, std::string& str) {
		Node* curr_node = root;
		for (int i = 0; i < str.size(); ++i) {
			if (std::isupper(str[i])) {
				char symbol = str[i];
				if (curr_node->links.count(symbol) == 0) {
					Node* new_node = new Node();
					curr_node->links[symbol] = new_node;
				}
				curr_node = curr_node->links.at(symbol);
			}
		}
		curr_node->data.push_back(std::move(str));
		curr_node->terminal = true;
		return curr_node;
	}

	void AddPtrToStr(Node* node, std::vector<std::string*>& vec) {
		if (node->terminal) {
			for (int i = 0; i < node->data.size(); ++i) {
				vec.push_back(&node->data[i]);
			}
		}

		if (node->links.size() > 0) {
			for (auto& link : node->links) {
				AddPtrToStr(link.second, vec);
			}
		}
	}

	std::vector<std::string*> FindCamelCases(Node* root, const std::string& key) {
		std::vector<std::string*> res;

		Node* curr_node = root;
		for (int i = 0; i < key.size(); ++i) {
			if (curr_node->links.count(key[i]) == 0) {
				return {};
			}
			curr_node = curr_node->links.at(key[i]);
		}

		AddPtrToStr(curr_node, res);

		return res;
	}

	void K_CamelCase(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		Node* root = new Node();		
		for (int i = 0; i < n; ++i) {
			std::string tmp;
			input >> tmp;			
			AddString(root, std::move(tmp));
		}
		
		int m;
		input >> m;
		for (int i = 0; i < m; ++i) {
			std::string key;
			input >> key;

			std::vector<std::string*> vec = FindCamelCases(root, key);
			std::sort(vec.begin(), vec.end(), 
				[](std::string* lhs, std::string* rhs) 
				{ return std::lexicographical_compare(lhs->begin(), lhs->end(), 
					rhs->begin(), rhs->end()); });
			for (auto& name : vec) {
				output << *name << '\n';
			}
		}
	}
	/*-------------------------------------------------------------------------*/
	std::string GetKeyToCompare(const std::string str) {
		std::string res;
		res.reserve(str.size());

		for (int i = 0; i < str.size(); ++i) {
			if (str[i] % 2 == 0) {
				res.push_back(str[i]);
			}
		}
		return res;
	}

	void L_CompareTwoStrings(std::istream& input, std::ostream& output) {
		std::string str1, str2;
		input >> str1 >> str2;

		std::string k1, k2;
		k1 = GetKeyToCompare(str1);
		k2 = GetKeyToCompare(str2);
		bool swap = false;
		if (k1.size() > k2.size()) {
			std::swap(k1, k2);
			swap = true;
		}

		for (int i = 0; i < k1.size(); ++i) {
			if (k1[i] != k2[i]) {
				if (k1[i] > k2[i]) {
					output << ((swap == true) ? "-1"s : "1"s) << '\n';					
				}
				else {
					output << ((swap == true) ? "1"s : "-1"s) << '\n';
				}
				return;
			}
		}
		if (k2.size() > k1.size()) {
			output << ((swap == true) ? "1"s : "-1"s) << '\n';
		}
		else {
			output << "0"s << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int> PrefixFunction(const std::string& str) {
		std::vector<int> res(str.size());		
		for (int i = 1; i < str.size(); ++i) {
			int k = res[i - 1];
			while (k > 0 && str[i] != str[k]) {
				k = res[k - 1];
			}
			if (str[i] == str[k]) {
				++k;
			}
			res[i] = k;
		}
		return res;
	}

	void M_PrefixFuncCount(std::istream& input, std::ostream& output) {
		std::string str;
		input >> str;

		std::vector<int> res = PrefixFunction(str);

		bool f = false;
		for (int i = 0; i < str.size(); ++i) {
			PrintSpace(output, f);
			output << res[i];
		}
		output << '\n';
	}
}

namespace s8_tests {
	using namespace std::literals;
	using namespace s8_problems;


	void A_StrangeComprasion() {
		{
			std::stringstream input;
			input << "mxyskaoghi"s << '\n'
				<< "qodfrgmslc"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::A_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "agg"s << '\n'
				<< "xdd"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::A_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "agg"s << '\n'
				<< "xda"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::A_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_StringReverse() {
		{
			std::stringstream input;
			input << "one two three"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::B_StringReverse(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "three two one"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "hello"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::B_StringReverse(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "hello"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "may the force be with you"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::B_StringReverse(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "you with be force the may"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void C_BorderControl() {
		{
			std::stringstream input;
			input << "m"s << '\n'
				<< "mm"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "jvcppyxvhklpolbtxnulimmxhaeswvfknfjikekj"s << '\n'
				<< "jvcppyxvhklqpolbtxnulimmxhaeswvfknfjikek"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "FAIL"s << '\n';
			assert(output.str() == res.str());
		}
		
		{
			std::stringstream input;
			input << "mmm"s << '\n'
				<< "mmma"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "mmma"s << '\n'
				<< "mmaa"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "mama"s << '\n'
				<< "papa"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "FAIL"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abcdefg"s << '\n'
				<< "abdefg"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "helo"s << '\n'
				<< "hello"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "dog"s << '\n'
				<< "fog"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::C_BorderControl(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "OK"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void D_BiggestPalindrome() {
		{
			std::stringstream input;
			input << "aaaabb"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::D_BiggestPalindrome(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "aabbaa"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "pabcd"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::D_BiggestPalindrome(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "a"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "aaabbb"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::D_BiggestPalindrome(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "ababa"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void E_CommonPrefix() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "abacaba"s << '\n'
				<< "abudabi"s << '\n'
				<< "abcdefg"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::E_CommonPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2"s << '\n'
				<< "tutu"s << '\n'
				<< "kukuku"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::E_CommonPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "qwe"s << '\n'
				<< "qwerty"s << '\n'
				<< "qwerpy"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::E_CommonPrefix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void F_StringInsert() {
		{
			std::stringstream input;
			input << "kukareku"s << '\n'
				<< "2"s << '\n'
				<< "p 1"s << '\n'
				<< "q 2"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::F_StringInsert(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "kpuqkareku"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abacaba"s << '\n'
				<< "3"s << '\n'
				<< "queue 2"s << '\n'
				<< "deque 0"s << '\n'
				<< "stack 7"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::F_StringInsert(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "dequeabqueueacabastack"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void G_MostFreqWord() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "caba"s << '\n'
				<< "aba"s << '\n'
				<< "caba"s << '\n'
				<< "abac"s << '\n'
				<< "aba"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::G_MostFreqWord(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "aba"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "b"s << '\n'
				<< "bc"s << '\n'
				<< "bcd"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::G_MostFreqWord(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "b"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "10"s << '\n'
				<< "ciwlaxtnhhrnenw"s << '\n'
				<< "ciwnvsuni"s << '\n'
				<< "ciwaxeujmsmvpojqjkxk"s << '\n'
				<< "ciwnvsuni"s << '\n'
				<< "ciwnvsuni"s << '\n'
				<< "ciwuxlkecnofovq"s << '\n'
				<< "ciwuxlkecnofovq"s << '\n'
				<< "ciwodramivid"s << '\n'
				<< "ciwlaxtnhhrnenw"s << '\n'
				<< "ciwnvsuni"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::G_MostFreqWord(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "ciwnvsuni"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void H_ShiftSearch() {
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "3 9 1 2 5 10 9 1 7"s << '\n'
				<< "2"s << '\n'
				<< "4 10"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::H_ShiftSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 8"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "1 2 3 4 5"s << '\n'
				<< "3"s << '\n'
				<< "10 11 12"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::H_ShiftSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2 3"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void I_GlobalChange() {
		{
			std::stringstream input;
			input << "pingpong"s << '\n'
				<< "ng"s << '\n'
				<< "mpi"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::I_GlobalChange(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "pimpipompi"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "aaa"s << '\n'
				<< "a"s << '\n'
				<< "ab"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::I_GlobalChange(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "ababab"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_Repeat() {
		{
			std::stringstream input;
			input << "zzzzzz"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::J_Repeat(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "6"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abacaba"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::J_Repeat(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abababab"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::J_Repeat(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void K_CamelCase() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "MamaMilaRamu"s << '\n'
				<< "MamaMia"s << '\n'
				<< "MonAmi"s << '\n'
				<< "2"s << '\n'
				<< "MM"s << '\n'
				<< "MA"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::K_CamelCase(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "MamaMia"s << '\n'
				<< "MamaMilaRamu"s << '\n'
				<< "MonAmi"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2"s << '\n'
				<< "AlphaBetaGgamma"s << '\n'
				<< "AbcdBcdGggg"s << '\n'
				<< "2"s << '\n'
				<< "ABGG"s << '\n'
				<< "ABG"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::K_CamelCase(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "AbcdBcdGggg"s << '\n'
				<< "AlphaBetaGgamma"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "WudHnagkbhfwrbci"s << '\n'
				<< "WCUkvoxboxufsdap"s << '\n'
				<< "jdrxomezzrpuhbgi"s << '\n'
				<< "ZcGHdrPplfoldemu"s << '\n'
				<< "cylbtqwuxhiveznc"s << '\n'
				<< "3"s << '\n'
				<< "WGHV"s << '\n'
				<< "NKVDT"s << '\n'
				<< "ZGHU"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::K_CamelCase(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			//res
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_CompareTwoStrings() {
		{
			std::stringstream input;
			input << "iduclzyfmdp"s << '\n'
				<< "aaeqrcgozsdcp"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::L_CompareTwoStrings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "-1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "z"s << '\n'
				<< "aaaaaaa"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::L_CompareTwoStrings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "gggggbbb"s << '\n'
				<< "bbef"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::L_CompareTwoStrings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "-1"s << '\n';
			assert(output.str() == res.str());
		}		
		{
			std::stringstream input;
			input << "ccccz"s << '\n'
				<< "aaaaaz"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::L_CompareTwoStrings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void M_PrefixFuncCount() {
		{
			std::stringstream input;
			input << "abracadabra"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::M_PrefixFuncCount(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 0 0 1 0 1 0 1 2 3 4"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "xxzzxxz"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::M_PrefixFuncCount(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1 0 0 1 2 3"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "aaaaa"s;
			std::ostringstream output(std::ios_base::ate);
			s8_problems::M_PrefixFuncCount(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1 2 3 4"s << '\n';
			assert(output.str() == res.str());
		}
	}
}


