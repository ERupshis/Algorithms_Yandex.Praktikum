#pragma once

#include <string>
#include <iostream>
#include <sstream>

// includes for problam A
//#include "solution.h"
#include <vector>
#include <cassert>


namespace s3_exam_problems {
	using namespace std::literals;

	std::vector<int> FillInputVectorInt(std::istream& input, int size = 0) {
		std::vector<int> res;
		if (size == 0) {
			int cnt;
			input >> cnt;
			res.reserve(cnt);
		}
		else {
			res.reserve(size);
		}

		for (size_t i = 0; i < res.capacity(); ++i) {
			int num;
			input >> num;
			res.push_back(num);
		}

		return res;
	}

	//SEND ID: ...

	int BinarySearch(const std::vector<int>& arr, int l, int r, int k) { // O(log n) due to we decrease search range in 2 times every recursion call	
		if (l > r) { // base case - value is not found
			return -1;
		}

		int mid = (l + r) / 2;
		if (arr[mid] == k) { // base case - value is found
			return mid;
		}

		if (arr[l] <= arr[mid]) { // left part of arr is sorted.
			if (arr[l] <= k && k <= arr[mid]) {
				return BinarySearch(arr, l, mid - 1, k); // value is in left part
			}
			else {
				return BinarySearch(arr, mid + 1, r, k); // value in right part of array
			}
		} 
		if (arr[mid] <= k && k <= arr[r]) { // right part of arr is sorted
			return BinarySearch(arr, mid + 1, r, k); // value is in right part
		}
		return BinarySearch(arr, l, mid - 1, k); // next recursion call to find sorted part of array		
	}

	int broken_search(const std::vector<int>& vec, int k) {		
		return BinarySearch(vec, 0, vec.size() - 1, k);			
	}

	void A_BrokenSearch(std::istream& input, std::ostream& output) {
		int n, k;
		input >> n >> k;
		std::vector<int> arr = std::move(FillInputVectorInt(input, n));

		output << broken_search(arr, k);
	}

	/*-------------------------------------------------------------------------*/

	//SEND ID: ...

}

namespace s3_exam_tests {
	using namespace std::literals;

	void A_BrokenSearch() {
		{
			std::stringstream input;
			input << "2"s << '\n'
				<< "1"s << '\n'
				<< "5 1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "20"s << '\n'
				<< "19 21 100 101 1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "-1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "101"s << '\n'
				<< "19 21 100 101 1"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "5"s << '\n'
				<< "1 4 5 7 12 19 21 100 101"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "21"s << '\n'
				<< "19 21 100 101 1 4 5 7 12"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "19"s << '\n'
				<< "19 21 100 101 1 4 5 7 12"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "1"s << '\n'
				<< "19 21 100 101 1 4 5 7 12"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "9"s << '\n'
				<< "5"s << '\n'
				<< "19 21 100 101 1 4 5 7 12"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::A_BrokenSearch(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "6"s;
			assert(output.str() == res.str());
		}			
	}

}
