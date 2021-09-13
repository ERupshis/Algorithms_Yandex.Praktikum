#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stack>

#include "Algorithms_Y.Praktikum_Sprint1_Exam.h"

namespace s3_problems {
	using namespace std::literals;

	bool CheckBracketSeq(std::string& str) {
		std::stack<int> stack;

		for (size_t i = 0; i < str.size(); ++i) {
			if (str[i] == '(') {
				stack.push('(');
			}
			else if (!stack.empty() && str[i] == ')') {
				stack.pop();
			}
			else {
				return false;
			}
		}
		//check stack
		if (stack.empty()) { // if empty - correct sequence
			return true;
		}
		else {
			return false;
		}
	}

	void GenerateBinaryBracketsVariants(int n, std::string str, std::vector<std::string>& arr) {
		if (n == 0) {
			if (CheckBracketSeq(str)) {
				arr.push_back(str);
			}
		}
		else {
			GenerateBinaryBracketsVariants(n - 1, str + '(', arr);
			GenerateBinaryBracketsVariants(n - 1, str + ')', arr);
		}
	}

	void A_BracketsGenerator(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<std::string> arr;
		GenerateBinaryBracketsVariants(2 * n, ""s, arr);

		for (std::string& str : arr) {			
			output << str << '\n';			
		}		
	}
	/*-------------------------------------------------------------------------*/
	void GenCombinations(size_t n, const std::string& input, const std::vector<std::string>& letters, std::string str, std::vector<std::string>& arr) {
		if (n == input.size()) {
			arr.push_back(str);
		}
		else {
			for (char ch : letters[input[n] - '0']) {
				GenCombinations(n + 1, input, letters , str + ch, arr);
			}
		}
	}

	void B_Combinations(std::istream& input, std::ostream& output) {
		std::string str;
		input >> str;
		std::vector<std::string> lett_to_num{ {}, {},{"abc"s}, {"def"s}, {"ghi"s}, {"jkl"s}, {"mno"s}, {"pqrs"s}, {"tuv"s}, {"wxyz"s} };


		std::vector<std::string> combinations;
		GenCombinations(0, str, lett_to_num , ""s, combinations);

		bool f = false;
		for (std::string& str : combinations) {
			if (!f) {
				f = true;
			}
			else {
				output << ' ';
			}
			output << str;
		}
	}
	/*-------------------------------------------------------------------------*/
	template <typename Container>
	int BinarySearchRecursion(const Container& array, int x, size_t left, size_t right) {
		if (left >= right) { // base case
			return -1;
		}		

		size_t mid = (left + right) / 2;
		if (x <= array[0]) { // base case
			return 1;
		}
		else if (mid >= 1 && array[mid - 1] < x && x <= array[mid]) {
			return mid + 1; // base case
		}		 
		else if (x <= array[mid]) {
			BinarySearchRecursion(array, x, left, mid);  // recursion case
		}
		else {
			BinarySearchRecursion(array, x, mid + 1, right); // recursion case
		}
	}

	void L_TwoBikes(std::istream& input, std::ostream& output) {
		std::vector<int> input_array = std::move(s1_exam_problems::FillInputVector(input));

		int cost;
		input >> cost;

		output << BinarySearchRecursion(input_array, cost, 0, input_array.size()) << ' ' 
			<< BinarySearchRecursion(input_array, 2 * cost, 0, input_array.size()) << '\n';

	}

}

namespace s3_tests {
	using namespace std::literals;

	void A_BracketsGenerator() {
		{
			std::stringstream input;
			input << "1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::A_BracketsGenerator(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "()"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::A_BracketsGenerator(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "(())"s << '\n'
				<< "()()"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::A_BracketsGenerator(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "((()))"s << '\n'
				<< "(()())"s << '\n'
				<< "(())()"s << '\n'
				<< "()(())"s << '\n'
				<< "()()()"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_Combinations() {
		{
			std::stringstream input;
			input << "23"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::B_Combinations(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "ad ae af bd be bf cd ce cf"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "92"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::B_Combinations(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "wa wb wc xa xb xc ya yb yc za zb zc"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << ""s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::B_Combinations(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << ""s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_TwoBikes() {
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 2 4 4 6 8"s << '\n'
				<< "3"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 5"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 2 4 4 4 4"s << '\n'
				<< "3"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 -1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 2 4 4 4 4"s << '\n'
				<< "10"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "-1 -1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 1 4 4 4 4"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 3"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 1 4 4 4 4"s << '\n'
				<< "4"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 -1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "7"s << '\n'
				<< "1 1 4 4 4 4 8"s << '\n'
				<< "4"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::L_TwoBikes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 7"s << '\n';
			assert(output.str() == res.str());
		}
	}


}