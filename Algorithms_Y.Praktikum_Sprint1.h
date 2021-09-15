#pragma once

#include <assert.h>

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace s1_problems {
	using namespace std::literals;

	void A_FunctionValues(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void B_EvenAndOddNumbers(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	std::vector<std::vector<int>> CreateEmptyMatrix(int x, int y);

	void FillMatrix(std::vector<std::vector<int>>& matrix, std::istream& input);

	template <typename type>
	std::ostream& operator<< (std::ostream& out, const std::vector<type>& vector) {
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
	
	void C_Neighbours(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	bool CheckRightDay(std::vector<int>& vec, size_t i);

	bool CheckLeftDay(std::vector<int>& vec, size_t i);

	void D_WeatherRandomness(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void E_LongestWord(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	std::string RemoveExcessSymbolsInRequest(std::string& in_str);
	
	void F_Palindrome(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void G_WorkFromHome(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void H_BinarySystem(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void I_PowerOfFour(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	std::vector<int> FillVectorByIndexes(int num);

	std::vector<int> EratothenesSieve(int num);

	std::vector<int> LinearSieve(int num);

	void J_Factorization(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	std::vector<int> FillVectorFromStream(std::istream& input, int cnt);

	void K_ListForm(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	std::unordered_map<char, int> FillCharsDict(std::string& str);

	void L_ExtraLetter(std::istream& input, std::ostream& output);
}

namespace s1_tests {
	using namespace std::literals;

	void A_FunctionValues_test();
	/*-------------------------------------------------------------------------*/
	void B_EvenAndOddNumbers_test();
	/*-------------------------------------------------------------------------*/
	void C_Neighbours_test();
	/*-------------------------------------------------------------------------*/
	void D_WeatherRandomness_test();
	/*-------------------------------------------------------------------------*/
	void E_LongestWord_test();
	/*-------------------------------------------------------------------------*/
	void F_Palindrome_test();
	/*-------------------------------------------------------------------------*/
	void G_WorkFromHome_test();
	/*-------------------------------------------------------------------------*/
	void H_BinarySystem_test();
	/*-------------------------------------------------------------------------*/
	void I_PowerOfFour_test();
	/*-------------------------------------------------------------------------*/
	void J_Factorization_test();
	/*-------------------------------------------------------------------------*/
	void J_K_ListForm_test();
	/*-------------------------------------------------------------------------*/
	void L_ExtraLetter_test();
}
