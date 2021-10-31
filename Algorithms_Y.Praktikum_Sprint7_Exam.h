#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>

namespace s7_exam_problems {
	using namespace std::literals;

	//SEND ID: 55745697	

	// For problem solving by Dynamic Programming way we have to answer on 5 questions:
	// 1. What will be stored in dp?
	//    - sum of required operation to make str1 and str2 equal. (the less operation we need to do, the better) 
	//    i - is a length of str1, j - length of str2.
	// 2. What will base case be for task?
	//    - in this task we have (str1.size() + str2.size()) base cases for problem. 
	//    If some string is empty and another is not - it means that we have to make strX.size() remove operations.    
	// 3. What will dynamic transition be for task?
	//    - We have to choose min count of operations from:
	//       - value when last operation was adding symbol to str1. In this way we have excess symbol (str1.size() == str2.size() + 1) and we need to remove this symbol 
	//       And in this way dp[i][j] = dp[i - 1][j] + 1(remove operation)
	//		 - value when last operation was adding symbol to str2. In this way we have excess symbol (str2.size() == str1.size() + 1) and we need to remove this symbol 
	//       And in this way dp[i][j] = dp[i][j - 1] + 1(remove operation)
	//       - value when both previous statements are not correct. In this way we have tow operation of symbol adding in the the ends of str1 and str2. If this symbols are equal than 
	//		 we don't need to make replacements for correlation of str1 and str2, otherwise we need +1 operation for equality str1 and str2
	//	     And in this way dp[i][j] = dp[i - 1][j - 1] + ((str1[i - 1] == str2[j - 1]) ? 0 : 1) *note: str indexes starts form 0, dp matrix from 1.
	//    formula of transition:
	//       dp[i][j] = min(cond1, cond2, cond3)
	// 4. What will the order of filling dp table be?
	//    - order will be from left-to-right, top-to-bottom.
	//       We will add min required count of operations to make str1 substr equal str2 substr at every condition of (i and j)
	//    - type of calculation:
	//      BACK dynamic programming
	// 5. Where will answer for problem be stored in dp table?
	//    - answer will be in dp[str1.size()][str2.size()] - final condition when we have checked whole str1 and str2
	//    
	// A_LevenshteinDistance() - function that recognize how many operation (symbol's add, remove, replace) are required to transform some string to another
	// 2D dynamic programming approach has been used. 
	// Function extends some str at every cycle step and checks if need new additional operation for transformation some str into another str or not.
	// 
	// Time Complexity: O(str1.size() * str2.size()). We extend some str by one symbol at every step and make comprasion of last operation.
	//
	// Space Complexity: O(str1.size() * str2.size()) of additional memory due to we need to store base cases answers 
	//    (located at left column with index 0 and top row with index 0)


	void A_LevenshteinDistance(std::istream& input, std::ostream& output) {
		std::string str1, str2;
		input >> str1 >> str2;

		std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1));
		//fill in elements with indexes i = 0 for str1 and j = 0 for str2 of matrix data range.
		//It shows how many elements should be removed if another word is empty.
		for (int i = 0; i <= str1.size(); ++i) {												
			dp[i][0] = i;  
		}
		for (int i = 0; i <= str2.size(); ++i) {
			dp[0][i] = i;
		}

		for (int i = 1; i <= str1.size(); ++i) { // filling dp is from left-to-right and from top to bottom
			for (int j = 1; j <= str2.size(); ++j) {	
				int a = dp[i - 1][j] + 1; // case when str1 is converted into str2 by removing excess symbol in str1. last opration is adding symbol to str1
				int b = dp[i][j - 1] + 1; // case when str1 is converted into str2 by removing excess symbol in str1. last opration is adding symbol to str2
				int c = dp[i - 1][j - 1] + ((str1[i - 1] == str2[j - 1]) ? 0 : 1); // case when both previous cases are incorrect. In this case we need to 
																				   // replace some element if symbols are not equal
				dp[i][j] = std::min({ a, b, c }); // the less operations we made to achieve equality of strings, the better solution
			}
		}
		output << dp[str1.size()][str2.size()] << '\n';
	}
	/*-------------------------------------------------------------------------*/
	//SEND ID: 55743635

	// For problem solving by Dynamic Programming way we have to answer on 5 questions:
	// 1. What will be stored in dp?
	//    - sum of some numbers set. (maximum possible sum that doesn't exceeds j index) 
	//    In comprasion with task about bag - j is a max capacity of bag
	// 2. What will base case be for task?
	//    - in this task we have N base cases for problem. If half_sum of elements is 0. we cannot take any number from list.
	//    Besides if sum is Odd or 0 - we cannot split it on equal sums.
	// 3. What will dynamic transition be for task?
	//    - We have to choose max value from:
	//       - value when we don't add current i number to sum (this value is equal to i-1 set of number)
	//       - value when we add current i number to sum of numbers set (we need to ensure that (desired new sum can be get by sum current 
	//		 i number with sum of already checked elements that equal to (desired sum - i number)
	//    formula of transition:
	//       dp[i][j] = max(dp[i - 1][j], i_number + dp[i - 1][j - i_number])
	// 4. What will the order of filling dp table be?
	//    - order will be from left-to-right, top-to-bottom.
	//       We will add max max possible sum of considered sums that doesn't exceed max possible sum (j idx here is max possible sum)
	//    - type of calculation:
	//      BACK dynamic programming
	// 5. Where will answer for problem be stored in dp table?
	//    - answer will be in column j = half_sum due to we are seeking for a combination of number's set which sum is exactly equal to half_sum.
	//    In this way we check if dp[i][j] = half_sum, where's j is equal to half_sum itself.

	// B_EqualSums() - function that recognize if input set of numbers can be split on two equal sum parts.
	// 2D dynamic programming approach has been used, but without keeping all data in memory.
	// For considered problem, only previous value's row is needed to check all combonations. 
	// If at some i-step we get dp[i][j] = half_sum (where's j is equal to half_sum itself) than we can stop execution of cycle 
	// and return positive answer, otherwise we have to check all combination and return negative.
	// Also, if overall sum of numbers set is odd number - it means we cannot split set on two smaller sets with equal number's sum
	// 
	// Time Complexity: O (N * M), where's N - count of input numbers, M - is a range from 1 to (SUM of all numbers) / 2 with step 1.
	// 
	// Space Complexity: O(2 * M) of additional memory, where's M - is a range from 1 to (SUM of all numbers) / 2 with step 1.
	//    We need to keep 2 rows i and i - 1 at any i-step of adding new number in considering set.
	//    To make this possible, we have to check dp[i][j] = half_sum (where's j is equal to half_sum itself) at every i-step

	void B_EqualSums(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<int> vec(n + 1, 0);
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			int tmp;
			input >> tmp;
			vec[i] = tmp;
			sum += tmp;
		}

		if (sum % 2 == 1) { // if overall sum is odd number - cannot split it on two equal sums;
			output << "False"s << '\n';
			return; // no need to continue;
		}

		int half_sum = sum / 2; // horizontal limit of dp 2d array
		std::vector<int> dp(half_sum + 1, 0); // no need to keep all data. We just need to find exact condition when sum of some numbers set is equal to half sum.
											// in this way, other numbers will give also half_sum
		for (int i = 1; i <= n; ++i) {			
			std::vector<int> tmp_dp(half_sum + 1, 0); // temporary array for keeping numbers sum at i step
			for (int j = 1; j <= half_sum; ++j) { // fill tmp_dp
				if (j - vec[i] >= 0) { // j - is a possible sum. Substract current i number from J size sum and check if remains exists in dp
					tmp_dp[j] = std::max(dp[j], vec[i] + dp[j - vec[i]]);
				}
				else { // invalid index of cell - no possible sum if i number with sum of some other numbers
					tmp_dp[j] = dp[j]; // just assign i-1 sum for j 
				}
			}			
			dp = tmp_dp; // write temporary dp to defined tmp for next i step
			if (tmp_dp[half_sum] == half_sum) { // check if we've got sum of numbers set equal to desired value
				output << "True"s << '\n';
				return;
			}
		}		
		output << "False"s << '\n';
	}
}

namespace s7_exam_tests {
	using namespace std::literals;
	using namespace s7_exam_problems;
		
	void A_LevenshteinDistance() {
		{
			std::stringstream input;
			input << "r"s << '\n'
				<< "x"s;
			std::ostringstream output(std::ios_base::ate);
			s7_exam_problems::A_LevenshteinDistance(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abacaba"s << '\n'
				<< "abaabc"s;
			std::ostringstream output(std::ios_base::ate);
			s7_exam_problems::A_LevenshteinDistance(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "innokentiy"s << '\n'
				<< "innnokkentia"s;
			std::ostringstream output(std::ios_base::ate);
			s7_exam_problems::A_LevenshteinDistance(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_EqualSums() {
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "1 5 7 1"s;
			std::ostringstream output(std::ios_base::ate);
			s7_exam_problems::B_EqualSums(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "True"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "2 10 9"s;
			std::ostringstream output(std::ios_base::ate);
			s7_exam_problems::B_EqualSums(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "False"s << '\n';
			assert(output.str() == res.str());
		}
	}
}
