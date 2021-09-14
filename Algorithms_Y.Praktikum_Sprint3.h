#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
	std::vector<std::string> FillInputVector(std::istream& input) {
		int cnt;
		input >> cnt;

		std::vector<std::string> res;
		res.reserve(cnt);
		for (int i = 0; i < cnt; ++i) {
			std::string num;
			input >> num;
			res.push_back(num);
		}

		return res;
	}	
	
	void H_BigNumber(std::istream& input, std::ostream& output) {		
		std::vector<std::string> arr = std::move(FillInputVector(input));		

		auto comparator = [](const std::string& lhs, const std::string& rhs)
			{return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); };

		for (size_t i = 1; i < arr.size(); ++i) {			
			for (size_t j = i; j > 0 && comparator(arr[j - 1], arr[j]); --j) {
				std::swap(arr[j], arr[j - 1]);				
			}				
		}

		for (size_t i = 0; i < arr.size(); ++i) {
			output << arr[i];
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/
	void InsertSort(std::istream& input, std::ostream& output) {
		using namespace s1_problems;
		std::vector<int> arr = std::move(s1_exam_problems::FillInputVector(input));

		for (size_t i = 1; i < arr.size(); ++i) {
			int num_to_insert = arr[i];
			size_t j = i;
			while (j > 0 && num_to_insert < arr[j - 1]) {
				arr[j] = arr[j - 1];
				--j;
			}
			arr[j] = num_to_insert;
		}
		output << arr << '\n';
	}

	void J_Bubble(std::istream& input, std::ostream& output) { // bubble sort O(n^2) // total amount of comprasions (N-1)N
		using namespace s1_problems;
		std::vector<int> arr = std::move(s1_exam_problems::FillInputVector(input));

		bool sorted = true;;
		for (size_t i = 1; i < arr.size(); ++i) { // outer cycle (N-1)
			bool f = false;
			for (size_t j = 0; j < arr.size() - i; ++j) { // internal cycle N/2 step due to we reduce the qty of compare iterations
				if (arr[j] > arr[j + 1]) {
					std::swap(arr[j], arr[j + 1]);
					f = true;
				}				
			}
			if (f) { 
				output << arr << '\n';
				sorted = false;
			}
			else { // helps to reduce better case to 2(N-1) - if already sorted arr comes to input
				if (sorted) {
					output << arr << '\n';
				}
				return;
			}
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
	void H_BigNumber() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "15 56 2"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "56215"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "1 783 2"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "78321"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "2 4 5 2 10"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "542210"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "5 73 7"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "7735"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_Bubble() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "4 3 9 2 1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::J_Bubble(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 4 2 1 9"s << '\n'
				<< "3 2 1 4 9"s << '\n'
				<< "2 1 3 4 9"s << '\n'
				<< "1 2 3 4 9"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "12 8 9 10 11"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::J_Bubble(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "8 9 10 11 12"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "8 9 10 11 12"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::J_Bubble(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "8 9 10 11 12"s << '\n';
			assert(output.str() == res.str());
		}
		//InsertSort test
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "4 3 9 2 1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::InsertSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2 3 4 9"s << '\n';
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