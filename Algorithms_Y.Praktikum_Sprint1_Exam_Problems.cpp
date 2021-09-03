#include "Algorithms_Y.Praktikum_Sprint1_Exam_Problems.h"

namespace s1_exam_problems {
	using namespace std::literals;	

	std::vector<int> FillInputVector(std::istream& input) {		
		int cnt;
		input >> cnt;

		std::vector<int> res;
		res.reserve(cnt);
		for (int i = 0; i < cnt; ++i) {
			int num;
			input >> num;
			res.push_back(num);
		}

		return res;
	}

	void A_NearestZero(std::istream& input, std::ostream& output) {		
		std::vector<int> house_nums = std::move(FillInputVector(input));		

		std::vector<int> distances(house_nums.size());
		int curr_empty = -1; // index of empty land on start
		for (size_t i = 0; i < distances.size(); ++i) {
			int new_empty = -1; // index of NEW empty land on in cycle
			if (house_nums[i] == 0) { // NEW empty land
				new_empty = i;				
			}
			if (new_empty >= 0) { // need to revise previous lands
				int start_ind;
				if (curr_empty == -1) { // first empty land is on the middle of street
					start_ind = curr_empty + 1;
				}
				else { // second or next empty land is found
					start_ind = (new_empty + curr_empty) / 2 + 1;
				}
				for (int j = start_ind; j < new_empty; ++j) { // update distances for house before new empty land
					distances[j] = new_empty - j;
				}
				curr_empty = new_empty; // update land we start to count
			}
			else {
				if (curr_empty != -1) {
					distances[i] = i - curr_empty; // update land we start to count
				}
			}
		}

		output << distances;
	}
	/*-------------------------------------------------------------------------*/
}

namespace s1_exam_tests {
	using namespace std::literals;

	void A_NearestZero_test() {
		{
			std::istringstream input("6\n0 7 9 4 8 20"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "0 1 2 3 4 5"s);
		}
		{
			std::istringstream input("5\n0 1 4 9 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "0 1 2 1 0"s);
		}
		{
			std::istringstream input("5\n1 1 4 0 1"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "3 2 1 0 1"s);
		}
		{
			std::istringstream input("5\n1 1 0 0 1"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "2 1 0 0 1"s);
		}
		{
			std::istringstream input("5\n0 0 0 0 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "0 0 0 0 0"s);
		}
		{
			std::istringstream input("5\n1 2 3 4 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "4 3 2 1 0"s);
		}
		{
			std::istringstream input("5\n1 2 3 0 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "3 2 1 0 0"s);
		}
		{
			std::istringstream input("5\n0 0 3 0 0"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::A_NearestZero(input, output);
			assert(output.str() == "0 0 1 0 0"s);
		}
	}
	/*-------------------------------------------------------------------------*/
}