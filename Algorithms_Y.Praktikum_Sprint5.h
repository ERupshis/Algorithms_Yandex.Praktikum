#pragma once

#include <string>
#include <cassert>
#include <iostream>
#include <cmath>

/* for problem A
//#include "solution_tree.h"
#include <cmath>
#include <iostream>
#include <cassert>
*/

namespace s5_problems {
	using namespace std::literals;

	struct Node {
		int value;
		const Node* left = nullptr;
		const Node* right = nullptr;
	};

	const int INF = -1e9;
	//problem A_Lamps
	int Solution(const Node* root) {
		int res = INF;
		if (root->value > res) {
			res = root->value;
		}
		if (root->left != nullptr && Solution(root->left) > res ) {
			res = Solution(root->left);
		}
		if (root->right != nullptr && Solution(root->right) > res) {
			res = Solution(root->right);
		}
		return res;
	}	
	/*-------------------------------------------------------------------------*/

}

namespace s5_tests {
	using namespace std::literals;

	void A_Lamps() {
		s5_problems::Node node1({ 1, nullptr, nullptr });
		s5_problems::Node node2({ -5, nullptr, nullptr });
		s5_problems::Node node3({ 3, &node1, &node2 });
		s5_problems::Node node4({ 2, &node3, nullptr });
		assert(s5_problems::Solution(&node4) == 3);
	}
	/*-------------------------------------------------------------------------*/

}