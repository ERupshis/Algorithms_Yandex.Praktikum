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
	int A_Solution(const Node* root) {
		int res = INF;
		if (root->value > res) {
			res = root->value;
		}
		
		if (root->left != nullptr) {
			int left_res = A_Solution(root->left);
			if (left_res > res) {
				res = A_Solution(root->left);
			}
		}

		if (root->right != nullptr) {
			int right_res = A_Solution(root->right);
			if (right_res > res) {
				res = A_Solution(root->right);
			}
		}
		return res;


	}	
	/*-------------------------------------------------------------------------*/
	bool IsTreeLess(const Node* root, int max) {
		if (root == nullptr) {
			return true;
		}

		if (root->value >= max) {
			return false;
		}

		return IsTreeLess(root->left, max) && IsTreeLess(root->right, max);
	}

	bool IsTreeGreater(const Node* root, int min) {
		if (root == nullptr) {
			return true;
		}

		if (root->value <= min) {
			return false;
		}

		return IsTreeGreater(root->left, min) && IsTreeGreater(root->right, min);
	}

	bool IsSearchTree(const Node* root) {
		if (root == nullptr) { // case if tree is empty
			return true;
		}

		if (root->left == nullptr && root->right == nullptr) { // terminal node case
			return true;
		}

		if (IsSearchTree(root->left) && IsSearchTree(root->right) // check on every level that for current subnode left and right sub trees follow the rule
			&& IsTreeLess(root->left, root->value) && IsTreeGreater(root->right, root->value)) {
			return true;
		}

		return false;
	}

	bool E_Solution(const Node* root) {
		return IsSearchTree(root);
	}
	/*-------------------------------------------------------------------------*/
	int CountTrees(int n) {
		// Consider that each value could be the root
		// Recursively find the size of the left and right subtrees
		if (n <= 1) {
			return 1;
		}
		else {
			// there will be one value at the root, with whatever remains
			// on the left and right each forming their own subtrees.
			// Iterate through all the values that could be the root
			int sum = 0;
			int left, right;

			for (int root = 1; root <= n; ++root) {
				left = CountTrees(root - 1);
				right = CountTrees(n - root);
				//number of possible trees with this root == left*right
				sum += left * right;
			}

			return sum;
		}
	}

	void I_CountBST(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		output << CountTrees(n);
	}
}

namespace s5_tests {
	using namespace std::literals;

	void A_Lamps() {
		s5_problems::Node node1({ 1, nullptr, nullptr });
		s5_problems::Node node2({ -5, nullptr, nullptr });
		s5_problems::Node node3({ 3, &node1, &node2 });
		s5_problems::Node node4({ 2, &node3, nullptr });
		assert(s5_problems::A_Solution(&node4) == 3);
	}
	/*-------------------------------------------------------------------------*/


	/*-------------------------------------------------------------------------*/
	void E_SearchTree() {
		{
			s5_problems::Node node1({ 1, nullptr, nullptr });
			s5_problems::Node node2({ 4, nullptr, nullptr });
			s5_problems::Node node3({ 3, &node1, &node2 });
			s5_problems::Node node4({ 8, nullptr, nullptr });
			s5_problems::Node node5({ 5, &node3, &node4 });
			assert(s5_problems::E_Solution(&node5));
		}
		{
			s5_problems::Node node1({ 1, nullptr, nullptr });
			s5_problems::Node node2({ 5, nullptr, nullptr });
			s5_problems::Node node3({ 3, &node1, &node2 });
			s5_problems::Node node4({ 8, nullptr, nullptr });
			s5_problems::Node node5({ 5, &node3, &node4 });
			assert(!s5_problems::E_Solution(&node5));
		}
	}
	/*-------------------------------------------------------------------------*/
	void I_CountBST() {
		{
			std::stringstream input;
			input << "2"s;
			std::ostringstream output(std::ios_base::ate);
			s5_problems::I_CountBST(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3"s;
			std::ostringstream output(std::ios_base::ate);
			s5_problems::I_CountBST(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "5"s;
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s;
			std::ostringstream output(std::ios_base::ate);
			s5_problems::I_CountBST(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "14"s;
			assert(output.str() == res.str());
		}
	}
}