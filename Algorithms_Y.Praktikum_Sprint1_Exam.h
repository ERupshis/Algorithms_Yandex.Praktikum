#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>

namespace s1_exam_problems {
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

	std::vector<int> FillInputVector(std::istream& input);

	void A_NearestZero(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
	void B_SleightOfHand(std::istream& input, std::ostream& output);
}

namespace s1_exam_tests {
	void A_NearestZero();
	/*-------------------------------------------------------------------------*/
	void B_SleightOfHand();
}