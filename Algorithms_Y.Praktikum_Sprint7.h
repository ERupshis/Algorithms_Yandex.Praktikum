#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>


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
}