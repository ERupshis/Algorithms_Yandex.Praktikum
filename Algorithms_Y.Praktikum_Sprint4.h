#pragma once

#include <string>
#include <iostream>
#include <vector>


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
}



