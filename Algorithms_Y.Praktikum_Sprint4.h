#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <string_view>
#include <unordered_map>

namespace s4_problems {
	using namespace std::literals;

	
	void A_PolynomialHash(std::istream& input, std::ostream& output) {
		int a, m;
		std::string str;
		input >> a >> m >> str;

		uint64_t res = 0;
		for (size_t i = 0; i < str.size(); ++i) {
			if (i == str.size() - 1) {
				res = (res + str[i]) % m;
			}
			else {
				res = (((res + str[i]) % m) * (a % m)) % m;
			}
		}

		output << res;
	}
	/*-------------------------------------------------------------------------*/
	int64_t B_PolynomialHash(int a, int m, std::string_view str) {
		uint64_t res = 0;
		for (size_t i = 0; i < str.size(); ++i) {
			if (i == str.size() - 1) {
				res = (res + str[i]) % m;
			}
			else {
				res = (((res + str[i]) % m) * (a % m)) % m;
			}
		}
		return res;
	}
	
	void B_BreakMe() {
		//std::cout << B_PolynomialHash(1000, 123'987'123, "kijuhygtfrdews") << ' ' << B_PolynomialHash(1000, 123'987'123, "kijuhygtfrdew");
		std::string in_str;
		std::cin >> in_str;
		std::unordered_map<int64_t, std::string> map;
		int substr_size = 170;
		while (substr_size > 5) {
			for (size_t i = 0; i < in_str.size() - substr_size - 1; ++i) {
				int64_t hash = B_PolynomialHash(1000, 123'987'123, in_str.substr(i, substr_size));				
				if (!map.count(hash)) {					
					map[hash] = in_str.substr(i, substr_size);
				}
				else if (map[hash] != in_str.substr(i, substr_size)) {
					std::cout << in_str.substr(i, substr_size) << '\n' << map.at(hash);
					return;
				}
			}
			--substr_size;
		}

	}
	/*-------------------------------------------------------------------------*/	
	struct RangeHasher {		
		size_t operator() (const std::pair<int, int> r) const {
			return int_hash(r.first) + 37 * int_hash(r.second);
		}
		std::hash<int> int_hash;
	};

	void C_PrefixHashes(std::istream& input, std::ostream& output) {
		int a, m, n;
		std::string str;		
		input >> a >> m >> str >> n;
		
		std::vector<int64_t> pref_hashes;
		
		pref_hashes.reserve(str.size());	
		pref_hashes.push_back(0);
		int64_t hash = 0;		
		for (size_t i = 0; i < str.size(); ++i) {			
			pref_hashes.push_back((pref_hashes[i] * a + str[i]) % m);
		}

		std::vector<int64_t> pow_of_a;
		pow_of_a.reserve(str.size());
		pow_of_a.push_back(1);
		for (size_t i = 1; i <= str.size(); ++i) {			
			pow_of_a.push_back(pow_of_a[i-1] * a % m);
		}

		while (n > 0) {
			int req_s, req_e;
			input >> req_s >> req_e;			
			int64_t res = (pref_hashes[req_e] - pref_hashes[req_s - 1] * pow_of_a[req_e - req_s + 1]) % m;
			if (res < 0) {
				res += m;
			}
			output << res << '\n';
			--n;
		}		
	}
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
	/*-------------------------------------------------------------------------*/
	std::string H_Hash(const std::string& str) {
		std::unordered_map<char, int> dict;

		std::string res;
		for (size_t i = 0; i < str.size(); ++i) {
			if (!dict.count(str[i])) {
				dict[str[i]] = dict.size();
			}

			res += std::to_string(dict[str[i]]);
		}

		return res;
	}

	std::vector<int> H_HashVector(const std::string& str) {
		std::unordered_map<char, int> dict;
		std::vector<int> res;
		res.reserve(str.size());
		for (size_t i = 0; i < str.size(); ++i) {
			if (!dict.count(str[i])) {
				dict[str[i]] = dict.size();
			}

			res.push_back(dict[str[i]]);
		}

		return res;
	}

	void H_StrangeComprasion(std::istream& input, std::ostream& output) {
		std::string str1, str2;
		input >> str1 >> str2;

		//if (H_Hash(str1) == H_Hash(str2)) {
		if (H_HashVector(str1) == H_HashVector(str2)) {
			output << "YES"s;
		}
		else {
			output << "NO"s;
		}		
	}
}

namespace s4_tests {
	using namespace std::literals;

	void A_PolynomialHash() {
		{
			std::stringstream input;
			input << "123"s << '\n'
				<< "100003"s << '\n'
				<< "a"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::A_PolynomialHash(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "97"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "123"s << '\n'
				<< "100003"s << '\n'
				<< "hash"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::A_PolynomialHash(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "6080"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "123"s << '\n'
				<< "100003"s << '\n'
				<< "HaSH"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::A_PolynomialHash(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "56156"s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void C_PrefixHashes() {
		{
			std::stringstream input;
			input << "1000"s << '\n'
				<< "1000009"s << '\n'
				<< "abcdefgh"s << '\n'
				<< "7"s << '\n'
				<< "1 1"s << '\n'
				<< "1 5"s << '\n'
				<< "2 3"s << '\n'
				<< "3 4"s << '\n'
				<< "4 4"s << '\n'
				<< "1 8"s << '\n'
				<< "5 8"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::C_PrefixHashes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "97"s << '\n'
				<< "225076"s << '\n'
				<< "98099"s << '\n'
				<< "99100"s << '\n'
				<< "100"s << '\n'
				<< "436420"s << '\n'
				<< "193195"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "100"s << '\n'
				<< "10"s << '\n'
				<< "a"s << '\n'
				<< "1"s << '\n'
				<< "1 1"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::C_PrefixHashes(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "7"s << '\n';
			assert(output.str() == res.str());
		}
	}
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
	/*-------------------------------------------------------------------------*/
	void H_StrangeComprasion() {
		{
			std::stringstream input;
			input << "mxyskaoghi"s << '\n'
				<< "qodfrgmslc"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::H_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "agg"s << '\n'
				<< "xdd"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::H_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "agg"s << '\n'
				<< "xda"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::H_StrangeComprasion(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s;
			assert(output.str() == res.str());
		}
	}
}



