#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <stack>


namespace s7_problems {
	using namespace std::literals;

	void A_StockMarket(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<int> arr;
		arr.reserve(n);

		for (int i = 0; i < n; ++i) {
			int tmp;
			input >> tmp;
			arr.push_back(tmp);
		}

		if (n == 0 || n == 1) {
			output << 0;
			return;
		}

		int s = 0;
		int res = 0;
		for (int i = 1; i < n; ++i) {
			if (arr[i - 1] < arr[i]) {
				if ((i + 1) != n) {
					continue;
				}
				else {
					res += arr[i] - arr[s];
				}
			}
			else {
				res += arr[i - 1] - arr[s];
			}
			s = i;
		}
		output << res;
	}
	/*-------------------------------------------------------------------------*/
	struct Meeting {
		double start = 0.0;
		double end = 0.0;
	};

	void B_TimeSchedule(std::istream& input, std::ostream& output) {
		int n;
		input >> n;

		std::vector<Meeting> vec;
		int i = 0;
		while (i < n) {
			double s, e;
			input >> s >> e;
			vec.push_back({ s, e });

			++i;
		}

		auto cmp_Meeting = [](const Meeting& lhs, const Meeting& rhs) {if (lhs.end == rhs.end) 
																			return lhs.start < rhs.start; 
																		else 
																			return lhs.end < rhs.end; };
		std::sort(vec.begin(), vec.end(), cmp_Meeting);

		std::vector<Meeting> res;
		if (!vec.empty()) {
			res.push_back(vec[0]);
		}
		for (int i = 1; i < vec.size(); ++i) {
			if (vec[i].start == vec[i].end || res.back().end <= vec[i].start) {
				res.push_back(vec[i]);
			}			
		}

		output << res.size() << '\n';
		for (const auto& elem : res) {
			output << elem.start << ' ' << elem.end << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	struct SandPile {
		uint64_t cost = 0;
		uint64_t weight = 0;
	};

	void C_GoldRush(std::istream& input, std::ostream& output) {
		uint64_t m, n;
		input >> m >> n;

		std::vector<SandPile> vec;

		for (int i = 0; i < n; ++i) {
			uint64_t c, w;
			input >> c >> w;
			vec.push_back({ c, w });
		}

		auto cmp_SandPile = [](const SandPile& lhs, const SandPile& rhs) { return lhs.cost > rhs.cost; };

		std::sort(vec.begin(), vec.end(), cmp_SandPile);

		uint64_t res = 0;
		uint64_t weight = 0;
		for (auto& elem : vec) {
			while (elem.weight > 0 && weight < m) {
				res += elem.cost;
				--elem.weight;
				++weight;
			}
			if (weight == m) {
				break;
			}
		}
		output << res << '\n';
	}
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	void F_JumpsOnStair(std::istream& input, std::ostream& output) {
		int n, k;
		input >> n >> k;
		int mod = 1'000'000'007;

		std::vector<int> vec(n + 1);
		vec[1] = 1;
		for (int i = 1; i < vec.size(); ++i) {
			for (int j = 1; j <= k && (i + j) < vec.size(); ++j) {
				vec[i + j] = (vec[i + j] + vec[i]) % mod;				
			}
		}
		output << vec[n] << '\n';
	}
	/*-------------------------------------------------------------------------*/
	/*-------------------------------------------------------------------------*/
	void H_FlowerField(std::istream& input, std::ostream& output) {
		int n, m;
		input >> n >> m;
		std::vector<std::vector<int>> field(n + 1, std::vector<int>(m + 1, 0));
		int count = n * m;
		for (int i = n; i >= 1; --i) {
			std::string row;
			input >> row;
			for (int j = 1; j <= m; ++j) {
				field[i][j] += static_cast<int>(row[j - 1]) - 48;				
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				field[i][j] += std::max(field[i - 1][j], field[i][j - 1]);
			}
		}

		output << field[n][m] << '\n';
	}
	/*-------------------------------------------------------------------------*/
	void I_DifficultFlowerField(std::istream& input, std::ostream& output) {
		int n, m;
		input >> n >> m;
		std::vector<std::vector<int>> field(n + 1, std::vector<int>(m + 1, 0));
		int count = n * m;
		for (int i = n; i >= 1; --i) {
			std::string row;
			input >> row;
			for (int j = 1; j <= m; ++j) {
				field[i][j] += static_cast<int>(row[j - 1]) - 48;
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				field[i][j] += std::max(field[i - 1][j], field[i][j - 1]);
			}
		}

		std::stack<char> res;
		int i = n, j = m;
		while (i != 1 && j != 1) {
			if (field[i - 1][j] > field[i][j - 1]) {
				res.push('U');
				--i;
			}
			else if (j > 0) {
				res.push('R');
				--j;
			}		
		}

		while (i > 1) {
			res.push('U');
			--i;
		}
		while (j > 1) {
			res.push('R');
			--j;
		}
		
		output << field[n][m] << '\n';
		while (res.size() > 0) {
			output << res.top();
			res.pop();
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/

	/*-------------------------------------------------------------------------*/
	void PrintSpace(std::ostream& output, bool& f) {
		if (!f) {
			f = true;
		}
		else {
			output << ' ';
		}
	}

	void K_Horoscopes(std::istream& input, std::ostream& output) {
		int n, m;
		input >> n;
		std::vector<int> seq1, seq2;
		for (int i = 0; i < n; ++i) {
			int tmp;
			input >> tmp;
			seq1.push_back(tmp);
		}
		input >> m;
		for (int i = 0; i < m; ++i) {
			int tmp;
			input >> tmp;
			seq2.push_back(tmp);
		}

		std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (seq1[i - 1] == seq2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}

		std::vector<std::stack<int>> ans(2);
		int i = n, j = m;
		while (i != 0 && j != 0) {
			if (seq1[i - 1] == seq2[j - 1]) {
				ans[0].push(i);
				ans[1].push(j);
				--i;
				--j;
			}
			else {
				if (dp[i][j] == dp[i - 1][j]) {
					--i;
				}
				else if (dp[i][j] == dp[i][j - 1]) {
					--j;
				}
			}
		}
		output << dp[n][m] << '\n';		
		if (dp[n][m] != 0) {
			for (auto& seq : ans) {
				bool f = false;
				while (seq.size() > 0) {
					PrintSpace(output, f);
					output << seq.top();
					seq.pop();
				}
				output << '\n';
			}
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_LeprekonsGold(std::istream& input, std::ostream& output) {
		int n, m;
		input >> n >> m;


		std::vector<int> weight;
		int i = 0;
		while (i < n) {
			int tmp;
			input >> tmp;
			weight.push_back(tmp);
			++i;
		}
		/*std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (j - weight[i - 1] >= 0) {
					dp[i][j] = std::max(dp[i - 1][j], weight[i - 1] + dp[i - 1][j - weight[i - 1]]);
				}
				else {
					dp[i][j] = std::max(dp[i - 1][j], 0);
				}
			}
		}*/

		std::vector<int> dp_vec(m + 1);
		for (int i = 0; i < n; ++i) {
			std::vector<int> tmp_vec(m + 1);
			for (int j = 1; j <= m; ++j) {
				if (j - weight[i] >= 0) {
					tmp_vec[j] = std::max(dp_vec[j], weight[i] + dp_vec[j - weight[i]]);
				}
				else {
					tmp_vec[j] = std::max(dp_vec[j], 0);
				}
			}
			dp_vec = tmp_vec;
		}
		output << dp_vec[m] << '\n';
	}
}


namespace s7_tests {
	using namespace std::literals;
	using namespace s7_problems;

	void A_StockMarket() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "1 2 3 4 5"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::A_StockMarket(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "7 1 5 3 6 4"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::A_StockMarket(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "7"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "1 12 12 16 1 8"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::A_StockMarket(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "22"s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_TimeSchedule() {		
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "9 10"s << '\n'
				<< "9.3 10.3"s << '\n'
				<< "10 11"s << '\n'
				<< "10.3 11.3"s << '\n'
				<< "11 12"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::B_TimeSchedule(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "9 10"s << '\n'
				<< "10 11"s << '\n'
				<< "11 12"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "9 10"s << '\n'
				<< "11 12.25"s << '\n'
				<< "12.15 13.3"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::B_TimeSchedule(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n'
				<< "9 10"s << '\n'
				<< "11 12.25"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "7"s << '\n'
				<< "19 19"s << '\n'
				<< "7 14"s << '\n'
				<< "12 14"s << '\n'
				<< "8 22"s << '\n'
				<< "22 23"s << '\n'
				<< "5 21"s << '\n'
				<< "9 23"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::B_TimeSchedule(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "7 14"s << '\n'
				<< "19 19"s << '\n'
				<< "22 23"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void C_GoldRush() {
		{
			std::stringstream input;
			input << "10"s << '\n'
				<< "3"s << '\n'
				<< "8 1"s << '\n'
				<< "2 10"s << '\n'
				<< "4 5"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::C_GoldRush(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "36"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "10000"s << '\n'
				<< "1"s << '\n'
				<< "4 20"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::C_GoldRush(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "80"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void F_JumpsOnStair() {
		{
			std::stringstream input;
			input << "6 3"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::F_JumpsOnStair(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "13"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "7 7"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::F_JumpsOnStair(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "32"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 2"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::F_JumpsOnStair(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void H_FLowerField() {
		{
			std::stringstream input;
			input << "3 3"s << '\n'
				<< "100"s << '\n'
				<< "110"s << '\n'
				<< "001"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::H_FlowerField(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 3"s << '\n'
				<< "101"s << '\n'
				<< "110"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::H_FlowerField(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void I_DifficultFlowerField() {
		{
			std::stringstream input;
			input << "3 3"s << '\n'
				<< "100"s << '\n'
				<< "110"s << '\n'
				<< "001"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::I_DifficultFlowerField(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n'
				<< "UURR"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 3"s << '\n'
				<< "101"s << '\n'
				<< "110"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::I_DifficultFlowerField(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "URR"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/

	/*-------------------------------------------------------------------------*/
	void K_Horoscopes() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "4 9 2 4 6"s << '\n'
				<< "7"s << '\n'
				<< "9 4 0 0 2 8 4"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::K_Horoscopes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "1 3 4"s << '\n'
				<< "2 5 7"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "1 1 1 1"s << '\n'
				<< "2"s << '\n'
				<< "2 2"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::K_Horoscopes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "8"s << '\n'
				<< "1 2 1 9 1 2 1 9"s << '\n'
				<< "5"s << '\n'
				<< "9 9 1 9 9"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::K_Horoscopes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "3 4 8"s << '\n'
				<< "3 4 5"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_LeprekonsGold() {
		{
			std::stringstream input;
			input << "5 15"s << '\n'
				<< "3 8 1 2 5"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::L_LeprekonsGold(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "15"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5 19"s << '\n'
				<< "10 10 7 7 4"s;
			std::ostringstream output(std::ios_base::ate);
			s7_problems::L_LeprekonsGold(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "18"s << '\n';
			assert(output.str() == res.str());
		}
	}
}