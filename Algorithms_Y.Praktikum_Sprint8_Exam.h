#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <stack>
#include <vector>


namespace s8_exam_problems {
	using namespace std::literals;	
	//SEND ID: ???
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

		std::stack<std::string> stack;
		std::stack<int> stack_num;
		
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
				// that exceeds common prefix of ohter (checked) strings
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
	//SEND ID: ???
	void B_CheatSheet(std::istream& input, std::ostream& output) {

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
			input << "examiwillpasstheexam"s << '\n'
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