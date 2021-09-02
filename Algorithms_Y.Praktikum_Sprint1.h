#pragma once

#include <assert.h>

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

namespace s1_problems {
	using namespace std::literals;

	void A_FunctionValues(std::istream& input, std::ostream& output) {
		int a, x, b, c;
		input >> a >> x >> b >> c;

		int res = a * static_cast<int>(pow(x, 2)) + b * x + c;
		output << res;
	}
	/*-------------------------------------------------------------------------*/
	void B_EvenAndOddNumbers(std::istream& input, std::ostream& output) {
		int a, b, c;
		input >> a >> b >> c;

		if (a % 2 && b % 2 && c & 2 ||
			!(a % 2) && !(b % 2) && !(c % 2)) {
			output << "WIN"s;
		}
		else {
			output << "FAIL"s;
		}
	}
	/*-------------------------------------------------------------------------*/
	std::vector<std::vector<int>> CreateEmptyMatrix(int x, int y) {
		std::vector<std::vector<int>> res(y);	
		std::vector<int> empty_row(x);
		for (int i = 0; i < y; ++i) {
			res[i] = empty_row;
		}

		return res;
	}

	void FillMatrix(std::vector<std::vector<int>>& matrix, std::istream& input) {
		for (size_t i = 0; i < matrix.size(); ++i) {
			if (matrix.size() > 0) {
				for (size_t j = 0; j < matrix[0].size(); ++j) {
					int num;
					input >> num;
					matrix[i][j] = num;
				}
			}
		}
	}

	std::ostream& operator<< (std::ostream& out, std::vector<int>& vector) {
		bool f = false;
		for (size_t i = 0; i < vector.size(); ++i) {
			if (f) {
				out << ' ';
			}
			else {
				f = true;
			}
			out << vector[i];
		}
		return out;
	}
	
	void C_Neighbours(std::istream& input, std::ostream& output) {
		int y, x;
		input >> y >> x;
		std::vector<std::vector<int>> matrix = std::move(CreateEmptyMatrix(x, y));	
		FillMatrix(matrix, input);

		int seek_y, seek_x;
		input >> seek_y >> seek_x;

		std::vector<int> dy{ -1, 0, 0, 1 };
		std::vector<int> dx{ 0, -1, 1, 0 };

		std::vector<int> res;
		for (size_t i = 0; i < dy.size(); ++i) {
			if (matrix.size() > 0
				&& 0 <= dy[i] + seek_y && dy[i] + seek_y < static_cast<int>(matrix.size())
				&& 0 <= dx[i] + seek_x && dx[i] + seek_x < static_cast<int>(matrix[0].size())) {
				res.push_back(matrix[dy[i] + seek_y][dx[i] + seek_x]);
			}
		}
		std::sort(res.begin(), res.end());
		output << res;
	}
	/*-------------------------------------------------------------------------*/
}

namespace s1_tests {
	using namespace std::literals;

	void A_FunctionValues_test() {
		{
			std::istringstream input("-8 -5 -2 7"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::A_FunctionValues(input, output);
			assert(output.str() == "-183"s);
		}
		{
			std::istringstream input("8 2 9 -10"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::A_FunctionValues(input, output);
			assert(output.str() == "40"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_EvenAndOddNumbers_test() {
		{
			std::istringstream input("1 2 -3"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::B_EvenAndOddNumbers(input, output);
			assert(output.str() == "FAIL"s);
		}
		{
			std::istringstream input("7 11 7"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::B_EvenAndOddNumbers(input, output);
			assert(output.str() == "WIN"s);
		}
		{
			std::istringstream input("6 -2 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::B_EvenAndOddNumbers(input, output);
			assert(output.str() == "WIN"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void C_Neighbours_test() {
		{
			std::istringstream input("4\n3\n1 2 3\n0 2 6\n7 4 1\n2 7 0\n3\n0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::C_Neighbours(input, output);
			assert(output.str() == "7 7"s);
		}
		{
			std::istringstream input("4\n3\n1 2 3\n0 2 6\n7 4 1\n2 7 0\n0\n0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::C_Neighbours(input, output);
			assert(output.str() == "0 2"s);
		}
	}
}
