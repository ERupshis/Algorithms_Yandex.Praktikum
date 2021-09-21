#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <string_view>
#include <unordered_map>

namespace s4_problems {
	using namespace std::literals;

	/*-------------------------------------------------------------------------*/
	struct KeyValue {
		std::string key = ""s;
		int value = 0;		

		bool operator < (const KeyValue other) {
			return key < other.key;
		}
	};

	void set(std::vector<KeyValue>& arr, const std::string& key) {
		for (KeyValue& pair : arr) {
			if (pair.key == key) {
				++pair.value;
				return;
			}
		}
		arr.push_back({ key, 1 });
	}

	void D_Cups(std::istream& input, std::ostream& output) {
		
		std::string num;
		std::getline(input, num);
		int n = std::stoi(num);		

		std::vector<KeyValue> arr;
		arr.reserve(n);

		while (n > 0) {
			std::string name;
			std::getline(input, name);
			set(arr, name);
			--n;
		}

		for (KeyValue& pair : arr) {
			output << pair.key << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	void G_Competition(std::istream& input, std::ostream& output) {		
		int n;
		input >> n;
		std::vector<int> arr;
		arr.reserve(n);
		for (int i = 0; i < n; ++i) {
			int num;
			input >> num;
			arr.push_back(num);
		}
		
		for (size_t i = 0; i < arr.size(); ++i) {
			arr[i] = (arr[i] == 0) ? -1 : 1; // replace 0 to -1. it will help to get sequence sum
		}

		int sum = 0;
		int max_length = 0;
		std::vector<int> hash(2 * n);
		for (int i = 0; i < n; ++i) {
			sum += arr[i];
			if (sum == 0) {
				max_length = i + 1;
			}
			if (hash[n + sum] != 0) {
				if (max_length < i - hash[n + sum]) {
					max_length = i - hash[n + sum];
				}
			}
			else {
				hash[n + sum] = i;
			}
		}

		output << max_length << '\n';
	}
}

namespace s4_tests {
	using namespace std::literals;

	/*-------------------------------------------------------------------------*/
	void D_Cups() {
		{
			std::stringstream input;
			input << "8"s << '\n'		
				<< "вышивание крестиком"s << '\n'
				<< "рисование мелками на парте"s << '\n'
				<< "настольный керлинг"s << '\n'
				<< "настольный керлинг"s << '\n'
				<< "кухня африканского племени ужасмай"s << '\n'
				<< "тяжелая атлетика"s << '\n'
				<< "таракановедение"s << '\n'
				<< "таракановедение"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::D_Cups(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "вышивание крестиком"s << '\n'
				<< "рисование мелками на парте"s << '\n'
				<< "настольный керлинг"s << '\n'
				<< "кухня африканского племени ужасмай"s << '\n'
				<< "тяжелая атлетика"s << '\n'
				<< "таракановедение"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void G_Competition() {
		{
			std::stringstream input;
			input << "10"s << '\n'
				<< "0 0 1 0 1 1 1 0 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::G_Competition(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "8"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "0 1 0"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::G_Competition(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2"s << '\n'
				<< "0 1"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::G_Competition(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n';
			assert(output.str() == res.str());
		}
	}
}



