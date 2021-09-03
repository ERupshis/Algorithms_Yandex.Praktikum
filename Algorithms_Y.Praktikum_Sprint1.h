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

	template <typename type>
	std::ostream& operator<< (std::ostream& out, std::vector<type>& vector) {
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
	bool CheckRightDay(std::vector<int>& vec, size_t i) { // Right - shift to +1 of i day
		return vec[i] > vec[i + 1];
	}

	bool CheckLeftDay(std::vector<int>& vec, size_t i) { // Left - shift to -1 of i day
		return vec[i] > vec[i - 1];
	}

	void D_WeatherRandomness(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		if (n == 0) { // if no data - NO randomness days
			output << 0;
			return;
		}
		else if (n == 1) { // if data for 1 day only - 1 randomness day
			output << 1;
			return;
		}
		// other conditions
		std::vector<int> vec(n); 
		for (int i = 0; i < n; ++i) {
			int num;
			input >> num;
			vec[i] = num;
		}

		int cnt = 0;
		for (size_t i = 0; i < vec.size(); ++i) {
			if (i == 0 && CheckRightDay(vec, i) 
				|| i == vec.size() - 1 && CheckLeftDay(vec, i)
				|| i > 0 && i < vec.size() - 1 && CheckLeftDay(vec, i) && CheckRightDay(vec, i)
				) {
				++cnt;
			}			
		}
		output << cnt;
	}
	/*-------------------------------------------------------------------------*/
	void E_LongestWord(std::istream& input, std::ostream& output) {
		int length;
		input >> length;

		size_t res = 0;
		std::string res_w;
		std::string tmp_word = ""s;
		while (input >> tmp_word) {
			if (tmp_word.size() > res) {
				res = tmp_word.size();
				res_w = tmp_word;
			}
		}

		output << res_w << '\n' << res;		
	}
	/*-------------------------------------------------------------------------*/
	std::string RemoveExcessSymbolsInRequest(std::string& in_str) {
		std::string res;
		res.reserve(in_str.size());
		for (size_t i = 0; i < in_str.size(); ++i) {
			if (islower(in_str[i]) || isdigit(in_str[i])) {
				res.push_back(in_str[i]);
			}
			else if (isupper(in_str[i])) {
				res.push_back(tolower(in_str[i]));
			}
		}
		return res;
	}
	/*-------------------------------------------------------------------------*/
	void F_Palindrome(std::istream& input, std::ostream& output) {
		std::string in_str;
		std::getline(input, in_str);

		std::string str_to_check = std::move(RemoveExcessSymbolsInRequest(in_str));		
		size_t i = 0;
		while (i < str_to_check.size() / 2) {
			if (str_to_check[i] != str_to_check[str_to_check.size() - 1 - i]) { //check symbols on opposite side of string
				output << "False"s;
				return;
			}
			++i;
		}
		output << "True"s;		
	}
	/*-------------------------------------------------------------------------*/
	void G_WorkFromHome(std::istream& input, std::ostream& output) { // convert dec int into binary
		int num;
		input >> num;

		std::string reversed_res;
		while (num != 0) {
			reversed_res.push_back((num % 2) ? '1' : '0');
			num /= 2;
		}
		std::string res(reversed_res.rbegin(), reversed_res.rend());
		output << res;
	}
	/*-------------------------------------------------------------------------*/
	void H_BinarySystem(std::istream& input, std::ostream& output) { // sum to binary numbers
		std::string a, b;
		input >> a >> b;
		
		if (a.size() < b.size()) {
			a.swap(b); // a is always > or == to b
		}		

		std::string rev_res;
		int buf = 0;
		for (size_t i = 0; i < a.size(); ++i) {
			int sum = (i < b.size()) ? (b[b.size() - 1 - i] - '0') + (a[a.size() - 1 - i] - '0') + buf : (a[a.size() - 1 - i] - '0') + buf;
			if (sum == 3) { // buf stays 1
				rev_res.push_back('1');
			}
			else if (sum == 2) {
				rev_res.push_back('0');
				buf = 1;
			}
			else if (sum == 1) {
				rev_res.push_back('1');
				buf = 0;
			}
			else {
				rev_res.push_back('0');
			}				
		}
		if (buf) {
			rev_res.push_back('1');
		}

		std::string res(rev_res.rbegin(), rev_res.rend());
		output << res;		
	}
	/*-------------------------------------------------------------------------*/
	void I_PowerOfFour(std::istream& input, std::ostream& output) { // check if input is the power of 4
		int num;
		input >> num;

		while (num != 1) {			
			if (num % 4 != 0) {
				output << "False"s;
				return;
			}
			num /= 4;
		}

		output << "True"s;
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int> FillVectorByIndexes(int num) {
		std::vector<int> res(num + 1);
		for (size_t i = 0; i < res.size(); ++i) {
			res[i] = i;
		}

		return res;
	}

	std::vector<int> EratothenesSieve(int num) { // return vector of prime numbers only from 2 up to num // O(n*log(log n))
		std::vector<int> vec = std::move(FillVectorByIndexes(num));
		if (num <= 2) {
			return { 0 };
		} 

		vec[1] = 0;
		for (size_t i = 2; i < vec.size(); ++i) { // 
			if (vec[i]) { // if number with ind i is not equal to 0
				for (size_t j = i * i; j < vec.size(); j += i) {
					vec[j] = 0;
				}
			}
		}

		std::vector<int> res;
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i]) {
				res.push_back(vec[i]);
			}
		}

		return res;
	}

	std::vector<int> LinearSieve(int num) {
		std::vector<int> least_prime(num + 1);
		std::vector<int> primes; // result of function
		if (num <= 2) {
			return { 0 };
		}

		for (size_t i = 2; i < least_prime.size(); ++i) {
			if (least_prime[i] == 0) { // if least prime is 0, suppose that i is prime
				least_prime[i] = i;
				primes.push_back(i);
			}
			for (auto p : primes) {
				size_t x = p * i;
				if (p > least_prime[i] || x > least_prime.size() - 1) {
					break;
				}
				least_prime[x] = p;
			}
		}
		return primes;
	}

	void J_Factorization(std::istream& input, std::ostream& output) {
		int in_num;
		input >> in_num;
		std::vector<int> prime_multipliers;
		/*//std::vector<int> primes = std::move(EratothenesSieve(in_num));	//can't handle too big numbers	
		//std::vector<int> primes = std::move(LinearSieve(in_num));	
		for (int p : primes) {
			if (in_num == 1) {
				break;
			}
			while (in_num % p == 0) {
				prime_multipliers.push_back(p);
				in_num /= p;
			}
		}*/
		int max_num = in_num;
		for (int i = 2; i <= max_num; ++i) {
			if (in_num == 1 || in_num < i) {
				break;
			}
			while (in_num % i == 0) {
				prime_multipliers.push_back(i);
				in_num /= i;
			}
		}
		
		if (in_num != 1) { // remains after division on primes is prime itself 
			prime_multipliers.push_back(in_num);
		}

		output << prime_multipliers;
	}
	/*-------------------------------------------------------------------------*/
	std::vector<int> FillVectorFromStream(std::istream& input, int cnt) {
		std::vector<int> res;
		res.reserve(cnt);

		for (int i = 0; i < cnt; ++i) {
			int num;
			input >> num;
			res.push_back(num);
		}

		return res;
	}

	void K_ListForm(std::istream& input, std::ostream& output) {
		int cnt;
		input >> cnt;
		std::vector<int> in_vec = std::move(FillVectorFromStream(input, cnt));		
		int addend;
		input >> addend;
		
		std::vector<int> reversed_res;
		for (auto it = in_vec.rbegin(); it != in_vec.rend(); ++it) {
			int tmp = *it + addend;
			if (tmp < 10) { 
				reversed_res.push_back(tmp);
			}
			else { // we need to move remains higher
				reversed_res.push_back(tmp % 10);				
				
			}
			addend = tmp / 10; // NA for numbers with 0 i nthe begining
		}

		while (addend != 0) { // if addend number is bigger than first
			reversed_res.push_back(addend % 10);
			addend /= 10;
		}

		std::vector<int> res(reversed_res.rbegin(), reversed_res.rend());

		output << res;
	}
	/*-------------------------------------------------------------------------*/
	std::unordered_map<char, int> FillCharsDict(std::string& str) {
		std::unordered_map<char, int> dict;

		for (size_t i = 0; i < str.size(); ++i) {
			dict[str[i]] += 1;
		}

		return dict;
	}

	void L_ExtraLetter(std::istream& input, std::ostream& output) {
		std::string s, t;
		input >> s >> t;

		std::unordered_map<char, int> dict_s, dict_t;
		dict_s = std::move(FillCharsDict(s));
		dict_t = std::move(FillCharsDict(t));		

		for (auto elem : dict_t) {
			if (!dict_s.count(elem.first) || elem.second != dict_s.at(elem.first)) {
				output << elem.first;
				break;
			}
		}
	}
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
	/*-------------------------------------------------------------------------*/
	void D_WeatherRandomness_test() {
		{
			std::istringstream input("7\n-1 -10 -8 0 2 0 5"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::D_WeatherRandomness(input, output);
			assert(output.str() == "3"s);
		}
		{
			std::istringstream input("5\n1 2 5 4 8"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::D_WeatherRandomness(input, output);
			assert(output.str() == "2"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void E_LongestWord_test() {
		{
			std::istringstream input("19\ni love segment tree"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::E_LongestWord(input, output);
			assert(output.str() == "segment\n7"s);
		}
		{
			std::istringstream input("21\nfrog jumps from river"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::E_LongestWord(input, output);
			assert(output.str() == "jumps\n5"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void F_Palindrome_test() {
		{
			std::istringstream input("A man, a plan, a canal: Panama"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::F_Palindrome(input, output);
			assert(output.str() == "True"s);
		}
		{
			std::istringstream input("zo"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::F_Palindrome(input, output);
			assert(output.str() == "False"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void G_WorkFromHome_test() {
		{
			std::istringstream input("5"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::G_WorkFromHome(input, output);
			assert(output.str() == "101"s);
		}
		{
			std::istringstream input("14"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::G_WorkFromHome(input, output);
			assert(output.str() == "1110"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void H_BinarySystem_test() {
		{
			std::istringstream input("1010\n1011"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::H_BinarySystem(input, output);
			assert(output.str() == "10101"s);
		}
		{
			std::istringstream input("111010\n1011"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::H_BinarySystem(input, output);
			assert(output.str() == "1000101"s);
		}
		{
			std::istringstream input("1\n1"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::H_BinarySystem(input, output);
			assert(output.str() == "10"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void I_PowerOfFour_test() {
		{
			std::istringstream input("15"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::I_PowerOfFour(input, output);
			assert(output.str() == "False"s);
		}
		{
			std::istringstream input("16"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::I_PowerOfFour(input, output);
			assert(output.str() == "True"s);
		}
		{
			std::istringstream input("24"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::I_PowerOfFour(input, output);
			assert(output.str() == "False"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_Factorization_test() {
		{
			std::istringstream input("8"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "2 2 2"s);
		}
		{
			std::istringstream input("13"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "13"s);
		}
		{
			std::istringstream input("100"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "2 2 5 5"s);
		}
		{
			std::istringstream input("794897"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "73 10889"s);
		}
		{
			std::istringstream input("120683"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "17 31 229"s);
		}
		{
			std::istringstream input("669392"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "2 2 2 2 17 23 107"s);
		}
		{
			std::istringstream input("802066951"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "7 4951 23143"s);
		}
		{
			std::istringstream input("464458159"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "11 23 89 20627"s);
		}
		{
			std::istringstream input("333826595"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "5 53 281 4483"s);
		}
		{
			std::istringstream input("917521579"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::J_Factorization(input, output);
			assert(output.str() == "13 70578583"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_K_ListForm_test() {
		{
			std::istringstream input("4\n1 2 0 0\n34"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::K_ListForm(input, output);
			assert(output.str() == "1 2 3 4"s);
		}
		{
			std::istringstream input("2\n9 5\n17"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::K_ListForm(input, output);
			assert(output.str() == "1 1 2"s);
		}
		{
			std::istringstream input("2\n9 5\n906"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::K_ListForm(input, output);
			assert(output.str() == "1 0 0 1"s);
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_ExtraLetter_test() {
		{
			std::istringstream input("abcd\nabcde"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::L_ExtraLetter(input, output);
			assert(output.str() == "e"s);
		}
		{
			std::istringstream input("go\nogg"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::L_ExtraLetter(input, output);
			assert(output.str() == "g"s);
		}
		{
			std::istringstream input("xtkpx\nxkctpx"s);
			std::ostringstream output(std::ios_base::ate);
			s1_problems::L_ExtraLetter(input, output);
			assert(output.str() == "c"s);
		}
	}
}
