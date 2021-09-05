#include "Algorithms_Y.Praktikum_Sprint1_Exam.h"

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
	void B_SleightOfHand(std::istream& input, std::ostream& output) {
		int one_kid_clicks;
		input >> one_kid_clicks;

		std::vector<int> buttons_on_board(10);
		char ch;
		while (input.peek() > -1) {
			ch = input.get();
			if (std::isdigit(ch)) {
				buttons_on_board[ch - '0'] += 1;
			}
		}
			
		int res = 0;
		for (int buttons : buttons_on_board) {
			if (buttons > 0 && buttons <= 2 * one_kid_clicks) {
				++res;
			}
		}

		output << res;		
	}
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
	void B_SleightOfHand_test() {
		{
			std::istringstream input("3\n1231\n2..2\n2..2\n2..2"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "2"s);
		}
		{
			std::istringstream input("4\n1111\n9999\n1111\n9911"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "1"s);
		}
		{
			std::istringstream input("4\n1111\n1111\n1111\n1111"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "0"s);
		}
		{
			std::istringstream input("1\n1999\n5436\n4368\n1712"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "7"s);
		}
		{
			std::istringstream input("3\n8844\n43.9\n2247\n4.48"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "6"s);
		}
		{
			std::istringstream input("1\n2293\n4912\n4836\n745."s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "7"s);
		}
		{
			std::istringstream input("1\n2.89\n2994\n8946\n63.."s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "5"s);
		}
		{
			std::istringstream input("1\n8177\n5321\n6633\n8213"s);
			std::ostringstream output(std::ios_base::ate);
			s1_exam_problems::B_SleightOfHand(input, output);
			assert(output.str() == "5"s);
		}
	}
}