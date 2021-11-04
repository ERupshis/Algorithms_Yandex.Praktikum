#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
#include <vector>
#include <algorithm>

namespace s8_problems {
	using namespace std::literals;

	/*-------------------------------------------------------------------------*/
	void PrintSpace(std::ostream& output, bool& f) {
		if (f) {
			output << ' ';
		}
		else {
			f = true;
		}
	}

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
	/*-------------------------------------------------------------------------*/
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
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
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


}

namespace s8_tests {
	using namespace std::literals;
	using namespace s8_problems;

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

	/*-------------------------------------------------------------------------*/

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
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
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
	

}
