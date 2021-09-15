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
	void C_Subsequence(std::istream& input, std::ostream& output) {
		std::string s, t;
		std::getline(input, s);
		std::getline(input, t);
		size_t s_cntr = 0, t_cntr = 0;

		while (s_cntr < s.size() && t_cntr < t.size()) {			
			if (t[t_cntr] == s[s_cntr]) {					
				++s_cntr;				
			}							
			++t_cntr;
		}
		if (s_cntr == s.size() && t_cntr <= t.size()) {
			output << "True"s;
			return;
		}
		output << "False"s;
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

		auto less_sum = [](const std::string& lhs, const std::string& rhs) { return lhs + rhs < rhs + lhs; };
		for (size_t i = 1; i < arr.size(); ++i) {
			for (size_t j = i; j > 0 && less_sum(arr[j - 1], arr[j]); --j) {
				std::swap(arr[j], arr[j - 1]);
			}
		}
		/*for (size_t i = 1; i < arr.size(); ++i) {
			bool f = false;
			for (size_t j = 0; j < arr.size() - i; ++j) {
				if (less_sum(arr[j], arr[j + 1])) {
					std::swap(arr[j], arr[j + 1]);
					f = true;
				}
			}
			if (!f) {
				break;
			}
		}*/
		
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
	/*-------------------------------------------------------------------------*/	
	std::vector<std::vector<int>> MergeSort(const std::vector<std::vector<int>>& arr) {
		if (arr.size() == 1) { // base case of recursion
			return arr;
		}

		std::vector<std::vector<int>> left = MergeSort({ arr.begin(), arr.begin() + arr.size() / 2 }); // recursion sort of left part
		std::vector<std::vector<int>> right = MergeSort({ arr.begin() + arr.size() / 2, arr.end() }); // recursion sort of right part

		std::vector<std::vector<int>> res(arr.size());

		auto comp = [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
			if (lhs[0] == rhs[0]) {
				return -lhs[1] < -rhs[1];
			}
			return lhs[0] < rhs[0]; };

		size_t l = 0, r = 0, k = 0; 
		while (l < left.size() && r < right.size()) {
			if (comp(left[l], right[r])) {
				res[k] = left[l];
				++l;
			}
			else {
				res[k] = right[r];
				++r;
			}
			++k;
		}

		while (l < left.size()) {
			res[k] = left[l];
			++l;
			++k;
		}
		while (r < right.size()) {
			res[k] = right[r];
			++r;
			++k;
		}

		return res;

	}

	void N_FlowerBeds(std::istream& input, std::ostream& output) {
		std::vector<std::vector<int>> arr;
		int count;
		input >> count;

		while (count != 0) {
			int start, end;
			input >> start >> end;
			arr.push_back({ start, end });
			--count;
		}
		// insert sort is too slow
		/*auto comp = [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
			if (lhs[0] == rhs[0]) {
				return -lhs[1] < -rhs[1];
			}
			return lhs[0] < rhs[0]; };


		for (size_t i = 1; i < arr.size(); ++i) {
			for (size_t j = i; j > 0 && comp(arr[j], arr[j - 1]); --j) {
				std::swap(arr[j], arr[j - 1]);
			}
		}*/

		std::vector<std::vector<int>> sorted_vec = std::move(MergeSort(arr));

		int start = 0, end = 0;
		for (size_t i = 0; i < sorted_vec.size(); ++i) {
			if (start == 0 && end == 0) { // initialize new flower bed area
				start = sorted_vec[i][0];
				end = sorted_vec[i][1];
			}
			else if (end >= sorted_vec[i][0] && end < sorted_vec[i][1]) { // check extension of curr flower bed
				end = sorted_vec[i][1];
			}
			else if (end < sorted_vec[i][0]) { // new flower bed
				output << start << ' ' << end << '\n';
				start = sorted_vec[i][0];
				end = sorted_vec[i][1];
			}
		}
		output << start << ' ' << end << '\n';
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
	void C_Subsequence() {
		{
			std::stringstream input;
			input << "ijha"s << '\n'
				<< "hmrqvftefyixinahlzgbkidroxiptbbkjmtwpsujevkulgrjiwiwzyhngulrodiwyg"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "False"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abc"s << '\n'
				<< "ahbgdcu"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "True"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abc"s << '\n'
				<< "abc"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "True"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "a"s << '\n'
				<< "hbgadcu"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "True"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abcp"s << '\n'
				<< "ahpc"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "False"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << ""s << '\n'
				<< "ahbgdcu"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "True"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abc"s << '\n'
				<< ""s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::C_Subsequence(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "False"s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void H_BigNumber() {
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "15 20 56 2"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "5622015"s << '\n';
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
		{
			std::stringstream input;
			input << "38"s << '\n'
				<< "82 58 66 34 64 37 40 97 93 52 28 98 90 64 19 22 21 83 56 70 46 17 31 51 55 41 68 18 98 89 88 74 6 6 31 36 35 8"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "9898979390898888382747068666664645856555251464140373635343131282221191817"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "100"s << '\n'
				<< "82 468 941 181 287 861 291 515 263 424 470 "
				<< "620 954 894 565 69 148 587 823 57 730 389 921 "
				<< "1000 447 1000 748 104 831 943 174 24 340 1000 "
				<< "150 937 324 919 748 271 980 575 392 779 222 316 "
				<< "944 1000 160 501 319 436 26 828 348 211 825 857 "
				<< "486 1000 419 509 409 679 576 700 418 810 674 83 "
				<< "785 251 947 868 964 384 497 192 1000 998 756 649 "
				<< "269 290 197 30 95 796 642 980 474 122 443 707 839 "
				<< "213 1000 530 263 193"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::H_BigNumber(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "998980980964959549479449439419379219"
				<< "198948688618578398383182882825823810"
				<< "796785779756748748730707700696796746"
				<< "496426205875765757556553051550950149"
				<< "748647447046844744343642441941840939"
				<< "238938434834032431931630291290287271"
				<< "269263263262512422221321119719319218"
				<< "117416015014812210410001000100010001"
				<< "00010001000"s << '\n';
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
	/*-------------------------------------------------------------------------*/
	void N_FlowerBeds() {
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "7 8"s << '\n'
				<< "7 12"s << '\n'
				<< "2 3"s << '\n'
				<< "6 10"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::N_FlowerBeds(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2 3"s << '\n'
				<< "6 12"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "7 8"s << '\n'
				<< "7 8"s << '\n'
				<< "2 3"s << '\n'
				<< "6 10"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::N_FlowerBeds(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2 3"s << '\n'				
				<< "6 10"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 3"s << '\n'
				<< "3 5"s << '\n'
				<< "4 6"s << '\n'
				<< "5 6"s << '\n'
				<< "2 4"s << '\n'
				<< "7 10"s;
			std::ostringstream output(std::ios_base::ate);
			s3_problems::N_FlowerBeds(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 6"s << '\n'
				<< "7 10"s << '\n';
			assert(output.str() == res.str());
		}
	}
}