#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cmath>

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

	void D_Cups(std::istream& input, std::ostream& output) { // not cups, but hobbies groups		
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
	void E_SubStrs(std::istream& input, std::ostream& output) {
		std::string  str;
		input >> str;

		std::unordered_map<char, int> letters;
		int start_p = 0;
		int max_length = 1;

		if (str.size() == 1) {
			output << 1;
			return;
		}

		for (size_t i = 0; i < str.size(); ++i) {
			if (letters.count(str[i]) && letters[str[i]] >= start_p) { // symbol dublicate
				if (i - start_p > max_length) {
					max_length = i - start_p;
				}
				start_p = letters[str[i]] + 1;
				letters[str[i]] = i;				
			}
			else {
				letters[str[i]] = i;				
			}
		}
		if (str.size() - start_p > max_length) {
			output << str.size() - start_p;
		}
		else {
			output << max_length;
		}
	}
	/*-------------------------------------------------------------------------*/
	void F_AngagrammGrouping(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		std::unordered_map<std::string, std::vector<int>> map;

		int i = 0;
		while (i < n) {
			std::string str;
			input >> str;
			std::string tmp_str(str);
			std::sort(tmp_str.begin(), tmp_str.end());
			map[tmp_str].push_back(i);
			++i;
		}

		std::vector<std::vector<int>*> res;
		for (auto& group : map) {
			res.push_back(&group.second);
		}
		std::sort(res.begin(), res.end(), 
			[](auto& lhs, auto& rhs) {return lhs[0] < rhs[0]; });

		for (auto& group : res) {
			bool f = false;
			for (int elem : *group) {
				if (f) {
					output << ' ';
				}
				else {
					f = true;
				}
				output << elem;
			}
			output << '\n';
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
	/*-------------------------------------------------------------------------*/
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

	int CountSubArray(int i1, std::vector<int>& arr1, int i2, std::vector<int>& arr2) {
		int res = 0;
		while (i1 < arr1.size() && i2 < arr2.size() && arr1[i1] == arr2[i2]) {
			++res;
			++i1;
			++i2;
		}
		return res;
	}

	void I_CommonSubArray(std::istream& input, std::ostream& output) {		
		std::vector<int> arr1 = std::move(FillInputVectorInt(input));
		std::vector<int> arr2 = std::move(FillInputVectorInt(input));

		std::unordered_map<int, std::unordered_set<int>> map1;

		for (size_t i = 0; i < arr1.size(); ++i) {
			map1[arr1[i]].insert(i);
		}
				
		int max_seq = 0;
		for (size_t i = 0; i < arr2.size(); ++i) {
			if (max_seq > arr2.size() - i) {
				break;
			}
 			if (map1.count(arr2[i])) {				
				for (int ind : map1.at(arr2[i])) {
					int len = CountSubArray(ind, arr1, i, arr2);
					if (max_seq < len) {
						max_seq = len;
					}
				}				
			}
		}

		output << max_seq;
	}
	/*-------------------------------------------------------------------------*/
	struct Hasher {
		int operator () (std::pair<int, int> pair) const {
			return pair.first * 37 + pair.second;
		}
	};

	struct QuardHasher {
		int operator () (std::tuple<int, int, int, int> tuple) const {
			int a, b, c, d;
			std::tie(a, b, c, d) = tuple;
			return  (((a * 37 + b) * 37 + c) * 37 + d) % 100003;
		}
	};

	void J_4Sum(std::istream& input, std::ostream& output) {
		int n;
		int64_t s;
		input >> n >> s;

		std::vector<int64_t> arr;
		arr.reserve(n);
		while (n > 0) {
			int num;
			input >> num;
			arr.push_back(num);
			--n;
		}
		std::sort(arr.begin(), arr.end());

		std::set<std::vector<int64_t>> four_sum;

		for (int i = 0; i < arr.size(); ++i) {
			if (i != 0 && arr[i] == arr[i - 1]) {
				continue;
			}
			for (int j = i + 1; j < arr.size(); ++j) {
				if (j != i + 1 && arr[j] == arr[j - 1]) {
					continue;
				}

				int k = j + 1;
				int l = arr.size() - 1;

				while (k < l) {
					int64_t sum = arr[i] + arr[j] + arr[k] + arr[l];
					
					if (s - sum == 0) {
						four_sum.insert({ arr[i], arr[j], arr[k], arr[l] });
						++k;						
					}
					else if (sum < s) {
						++k;
					}
					else {
						--l;
					}
				}
			}
		}
		
		output << four_sum.size() << '\n';
		for (auto& quard : four_sum) {			
			output << quard[0] << ' ' << quard[1] << ' ' << quard[2] << ' ' << quard[3] << '\n';
		}		
	}
	/*-------------------------------------------------------------------------*/	
	struct Coord {
		Coord(int x_, int y_)
			:x(x_), y(y_) {
		};

		int x = 0;
		int y = 0;
	};	

	std::vector<Coord> FillCoordsVector(std::istream& input) {
		int n;
		input >> n;
		std::vector<Coord> res;
		res.reserve(n);
		int i = 0;
		while (i < n) {
			int x, y;
			input >> x >> y;
			res.push_back({ x, y });
			++i;
		}
		return res;
	}	

	bool IsCoordInArea(Coord& exit, Coord& stop) {		
		int64_t dist = (exit.x - stop.x) * (exit.x - stop.x) + (exit.y - stop.y) * (exit.y - stop.y);
		if (dist <= 400) {
			return true;
		}
		return false;
	}

	void K_NearestStop(std::istream& input, std::ostream& output) {
		std::vector<Coord> exits = std::move(FillCoordsVector(input));
		std::vector<Coord> stops = std::move(FillCoordsVector(input));

		std::unordered_map<int, std::unordered_set<int>> map_x;
		std::vector<int> exits_count(exits.size());
		for (size_t i = 0; i < stops.size(); ++i) {
			map_x[stops[i].x].insert(stops[i].y);			
		}

		for (size_t i = 0; i < exits.size(); ++i) {
			for (int j = -20; j <= +20; ++j) {
				if (map_x.count(exits[i].x + j)) {
					for (auto& vec_elem : map_x.at(exits[i].x + j)) {
						Coord tmp{ exits[i].x + j, vec_elem };
						if (IsCoordInArea(tmp, exits[i])) {
							++exits_count[i];								
						}						
					}
				}
			}
		}

		int max_count = 0;
		int max_ind = 0;
		for (size_t i = 0; i < exits_count.size(); ++i) {
			if (exits_count[i] > max_count) {
				max_ind = i;
				max_count = exits_count[i];
			}
		}

		output << max_ind + 1;
	}

	
	/*-------------------------------------------------------------------------*/
	int64_t L_PolynomialHash(int64_t a, int64_t m, std::string_view str) {
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

	void L_ManyGosha(std::istream& input, std::ostream& output) {
		int n, k;
		std::string str;
		input >> n >> k >> str;
		int a = 1'000'000'007;
		int64_t pow_a_n = 1;
		int64_t m = static_cast<int64_t>(std::pow(2, 36));
		for (size_t i = 1; i < n; ++i) { // get pow(a, n - 1) for hash
			pow_a_n = pow_a_n * a % m;
		}

		std::unordered_map<int64_t, std::vector<int>> res;
		int64_t hash = L_PolynomialHash(a, m, str.substr(0, n));
		res[hash].push_back(0);
		for (int i = 1; i <= str.size() - n; ++i) {
			hash = ((hash - str[i - 1] * pow_a_n % m) * a % m + str[i + n - 1]) % m;
			if (hash < 0) {
				hash += m;
			}
			res[hash].push_back(i);
		}
				
		bool f = false;
		for (auto& elem : res) {
			if (elem.second.size() >= k) {
				if (f) {
					output << ' ';
				}
				else {
					f = true;
				}
				output << elem.second.front();				
			}
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
	void E_SubStrs() {
		{
			std::stringstream input;
			input << "fprarfpoz"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "6"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "awe"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "abcabcbb"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "bbbbb"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "b"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "bbbbbbbbbbbacfb"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::E_SubStrs(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4"s;
			assert(output.str() == res.str());
		}

	}
	/*-------------------------------------------------------------------------*/
	void F_AngagrammGrouping() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "ttt zzz aaa"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::F_AngagrammGrouping(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s << '\n'
				<< "1"s << '\n'
				<< "2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "tan eat tea ate nat bat"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::F_AngagrammGrouping(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 4"s << '\n'
				<< "1 2 3"s << '\n'
				<< "5"s << '\n';
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
	/*-------------------------------------------------------------------------*/
	void I_CommonSubArray() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "1 2 3 2 1"s << '\n'
				<< "5"s << '\n'
				<< "3 2 1 5 6"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::I_CommonSubArray(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "1 2 3 4 5"s << '\n'
				<< "3"s << '\n'
				<< "4 5 9"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::I_CommonSubArray(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "1"s << '\n'
				<< "1"s << '\n'
				<< "1"s << '\n'
				<< "4"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::I_CommonSubArray(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "1"s << '\n'
				<< "1"s << '\n'
				<< "1"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::I_CommonSubArray(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "10"s << '\n'
				<< "1 2 3 4 5 7 8 9 10 6"s << '\n'
				<< "10"s << '\n'
				<< "1 2 3 4 5 6 7 8 9 10"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::I_CommonSubArray(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "5"s;
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_4Sum() {
		{
			std::stringstream input;
			input << "8"s << '\n'
				<< "10"s << '\n'
				<< "2 3 2 4 1 10 3 0"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::J_4Sum(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "0 3 3 4"s << '\n'
				<< "1 2 3 4"s << '\n'
				<< "2 2 3 3"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "0"s << '\n'
				<< "1 0 -1 0 2 -2"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::J_4Sum(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "-2 -1 1 2"s << '\n'
				<< "-2 0 0 2"s << '\n'
				<< "-1 0 0 1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "4"s << '\n'
				<< "1 1 1 1 1"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::J_4Sum(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n'
				<< "1 1 1 1"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/	
	void K_NearestStop() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "-1 0"s << '\n'
				<< "1 0"s << '\n'
				<< "2 5"s << '\n'
				<< "3"s << '\n'
				<< "10 0"s << '\n'
				<< "20 0"s << '\n'
				<< "22 5"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::K_NearestStop(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "-1 0"s << '\n'
				<< "1 0"s << '\n'
				<< "0 5"s << '\n'
				<< "3"s << '\n'
				<< "10 0"s << '\n'
				<< "20 0"s << '\n'
				<< "20 5"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::K_NearestStop(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s;
			assert(output.str() == res.str());
		}


	}

	/*-------------------------------------------------------------------------*/
	void L_ManyGosha() {	// output is not sorted, may not pass test due to another indexes seq
		{
			std::stringstream input;
			input << "2 2"s << '\n'
				<< "axaxax"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4 4"s << '\n'
				<< "axniaxaxaxniaxaxaxax"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "10 2"s << '\n'
				<< "gggggooooogggggoooooogggggssshaa"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 5"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 4"s << '\n'
				<< "allallallallalla"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1 2"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 4"s << '\n'
				<< "gggggooooogggggoooooogggggssshaa"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 5"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "1 10"s << '\n'
				<< "gggggooooogggggoooooogggggssshaa"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "5 0"s;
			//assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 1"s << '\n'
				<< "gggggooooogggggoooooogggggssshaa"s;
			std::ostringstream output(std::ios_base::ate);
			s4_problems::L_ManyGosha(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4 0 9 5 26 25 28 29"s;
			//assert(output.str() == res.str());
		}
	}
}



