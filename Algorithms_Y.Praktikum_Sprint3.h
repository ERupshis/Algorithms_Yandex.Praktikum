#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Algorithms_Y.Praktikum_Sprint1_Exam.h"

namespace s3_problems {
	using namespace std::literals;


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