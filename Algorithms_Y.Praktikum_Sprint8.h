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
	/*-------------------------------------------------------------------------*/
	

}
