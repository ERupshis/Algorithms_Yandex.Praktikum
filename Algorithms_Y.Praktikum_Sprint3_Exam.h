#pragma once

#include <string>
#include <iostream>
#include <sstream>

//includes for problam A
//#include "solution.h"
#include <vector>
#include <cassert>


namespace s3_exam_problems {
	using namespace std::literals;	

	//SEND ID: 53237371

	// BinarySearch - implementation of standard binarysearch on the damaged array* 
	// * - elements of array are sorted, but first element may be in any position in the array (in other words - start of array may be shifted from array.begin())
	// This function has two base cases:
	// - left and right pointers are overlapping - in this case value is not found and function returns -1
	// - arr[mid] == k - in this case value is found
	// Qty of recursion calls is also two, but before call we have to make sure that current part of array is in consistent state.
	// Possible variants of consistent state are:
	// - arr[l] <= k <= arr[mid] - left part of recursion call considering part of array is OK and seeking value inside of this range
	// - arr[mid] <=k <= arr[r] - the same but applicable to right part
	// Variants of non-consistent state:
	// - arr[l] <= arr[mid] - left part of array is OK, but seeking value is not included in this range
	// - arr[l] > arr[mid] - left part is NOT OK, but seeking value in this range (below that arr[mid]. 
	//	 It means that we need to split this part till some sub part of recursion call will be OK
	// Time coplexity: O(log n)
	// search range decreases in 2 times on every recursion call;
	// 
	// Space complexity: O(1)
	// space is required for mid (pivot) calculation;

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

	void A_BrokenSearch(std::istream& input, std::ostream& output) {
		int n, k;
		input >> n >> k;
		std::vector<int> arr = std::move(FillInputVectorInt(input, n));

		output << broken_search(arr, k);
	}

	/*-------------------------------------------------------------------------*/
	//SEND ID: 53268385

	struct Participant {
		std::string name = ""s;
		int solved_problems = 0;
		int penalty = 0;

		bool operator < (const Participant& other) {
			if (solved_problems > other.solved_problems) {
				return true;
			}
			else if (solved_problems == other.solved_problems) {
				if (penalty < other.penalty) {
					return true;
				}
				else if (penalty == other.penalty) {
					return name < other.name;					
				}
			}			
			return false;			
		}

		bool operator == (const Participant& other) {			
			return name == other.name 
				&& solved_problems == other.solved_problems 
				&& penalty == other.penalty;
		}		
	};

	std::vector<Participant> FillVectorOfParticipants(std::istream& input, int size = 0) {
		std::vector<Participant> res;
		if (size == 0) {
			int cnt;
			input >> cnt;
			res.reserve(cnt);
		}
		else {
			res.reserve(size);
		}

		for (size_t i = 0; i < res.capacity(); ++i) {
			std::string name;
			int problems, penalty;
			input >> name >> problems >> penalty;
			res.push_back({ name, problems, penalty });
		}
		return res;
	}

	// EffectiveQuickSort - method that sort array in ascending sequence.
	// Pivot point - border condition in array on sub stage of sorting that guarantee:
	// less values are located on the left side of border and bigger values are located on the right side of value;
	// Pivot point choose is random (in the middle of array) that gives time complexity O(log n) in average
	// This method are performed in recursion variant that allows to simplify code view
	// It has two base cases: when considering array consist of two elements (sequence order should be checked before return) and overlapping left and right pointers
	// Also it has two recursion cases: left part of array where all elements are less that pivot and other elements are located in right part
	// Cycle while(l < r) helps to find elements that located incorrect in array relatively to pivot value
	// Time coplexity:
	// - O(n log n) - on average, if pivot is choosen as a middle value of elements in sorting array part. In this way array will split on two ~equal parts
	// on every recursion call n elements is going to be considered
	// - O(n * n) - worst case, when pivot point will be border value (the less or the biggest one). In this case only pivot value will be excluded on the next recursion call
	// Space complexity:
	// - additional space is not requred, due to this variant of quick sort modify sorting array without memory allocation for temporary values storage,
	// except three temporary fields - start, end, pivot

	void EffectiveQuickSort(std::vector<Participant>& arr, int l, int r) {
		int start = l, end = r; // end border of current recursion call
		if (l >= r) { // base case  to exit
			return;
		}
		if (l + 1 == r) { // base case to exit
			if (arr[r] < arr[l]) {
				std::swap(arr[l], arr[r]);
			}
			return; 
		}
		
		Participant pivot = arr[(l + r) / 2]; // take last element as a pivot						
		while (l < r) {	
			if (arr[l] < pivot) { // move ptr to right if left element is less than pivot
				++l;
				continue;
			}
			if (pivot < arr[r]) { // move ptr to left, if right element is bigger than pivot
				--r;
				continue;
			}
			std::swap(arr[l], arr[r]); // case when two element are found for swapping (pivot <= arr[l] && arr[r] < pivot)
			
		}		

		EffectiveQuickSort(arr, start, l - 1); // recursion call of left part
		EffectiveQuickSort(arr, l, end); // recursion call of right part
	}

	std::ostream& operator << (std::ostream& output, const std::vector<Participant>& arr) {
		for (const Participant& member : arr) {
			output << member.name << '\n';
		}
		return output;
	}


	void B_EffectiveQuickSort(std::istream& input, std::ostream& output) {				
		std::vector<Participant> arr = std::move(FillVectorOfParticipants(input));

		EffectiveQuickSort(arr, 0, arr.size() - 1);

		output << arr;
	}

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

	void B_EffectiveQuickSort() {
		{
			s3_exam_problems::Participant user1{ "alla"s, 4 ,100 };
			s3_exam_problems::Participant user2{ "alla"s, 2, 100 };
			s3_exam_problems::Participant user3{ "alla"s, 2, 90 };
			s3_exam_problems::Participant user4{ "gosha"s, 2, 90 };

			assert(user1 < user2);
			assert(user3 < user2);
			assert(user3 < user4);
			assert(!(user2 < user1));
			assert(!(user2 < user3));
		}
		{
			std::stringstream input;
			input << "13"s << '\n'
				<< "tufhdbi 76 58"s << '\n'
				<< "rqyoazgbmv 59 78"s << '\n'
				<< "qvgtrlkmyrm 35 27"s << '\n'
				<< "tgcytmfpj 70 27"s << '\n'
				<< "xvf 84 19"s << '\n'
				<< "jzpnpgpcqbsmczrgvsu 30 3"s << '\n'
				<< "evjphqnevjqakze 92 15"s << '\n'
				<< "wwzwv 87 8"s << '\n'
				<< "tfpiqpwmkkduhcupp 1 82"s << '\n'
				<< "tzamkyqadmybky 5 81"s << '\n'
				<< "amotrxgba 0 6"s << '\n'
				<< "easfsifbzkfezn 100 28"s << '\n'
				<< "kivdiy 70 47"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "easfsifbzkfezn"s << '\n'
				<< "evjphqnevjqakze"s << '\n'
				<< "wwzwv"s << '\n'
				<< "xvf"s << '\n'
				<< "tufhdbi"s << '\n'
				<< "tgcytmfpj"s << '\n'
				<< "kivdiy"s << '\n'
				<< "rqyoazgbmv"s << '\n'
				<< "qvgtrlkmyrm"s << '\n'
				<< "jzpnpgpcqbsmczrgvsu"s << '\n'
				<< "tzamkyqadmybky"s << '\n'
				<< "tfpiqpwmkkduhcupp"s << '\n'
				<< "amotrxgba"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "8"s << '\n'
				<< "04 0 0"s << '\n'
				<< "08 0 0"s << '\n'
				<< "09 0 0"s << '\n'
				<< "20 0 0"s << '\n'
				<< "01 0 0"s << '\n'
				<< "05 0 0"s << '\n'
				<< "03 0 0"s << '\n'
				<< "10 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "01"s << '\n'
				<< "03"s << '\n'
				<< "04"s << '\n'
				<< "05"s << '\n'
				<< "08"s << '\n'
				<< "09"s << '\n'
				<< "10"s << '\n'
				<< "20"s << '\n';
			assert(output.str() == res.str());
		}		
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 4 100"s << '\n'
				<< "gena 6 1000"s << '\n'
				<< "gosha 2 90"s << '\n'
				<< "rita 2 90"s << '\n'
				<< "timofey 7 80"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "timofey"s << '\n'
				<< "gena"s << '\n'
				<< "alla"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n';
			assert(output.str() == res.str());
		}
		
		{
			std::stringstream input;
			input << "1"s << '\n'
				<< "a 0 0"s;				
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "a"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 4 100"s << '\n'
				<< "gena 6 1000"s << '\n'
				<< "gosha 2 90"s << '\n'
				<< "rita 2 90"s << '\n'
				<< "timofey 4 80"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "gena"s << '\n'
				<< "timofey"s << '\n'
				<< "alla"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 0 0"s << '\n'
				<< "gena 0 0"s << '\n'
				<< "gosha 0 0"s << '\n'
				<< "rita 0 0"s << '\n'
				<< "timofey 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s3_exam_problems::B_EffectiveQuickSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "alla"s << '\n'
				<< "gena"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n'
				<< "timofey"s << '\n';
			assert(output.str() == res.str());
		}
	}
}
