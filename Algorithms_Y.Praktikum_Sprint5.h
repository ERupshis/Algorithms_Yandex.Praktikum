#pragma once

#include <string>
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>

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

	struct nNode {		
		nNode* left = nullptr;
		nNode* right = nullptr;
		int value;
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
	//B Balanced Tree

	bool IsBalancedTree(const Node* root, int* h = nullptr) {
		int l = 0, r = 0;
		if (root->left != nullptr) {
			if (!IsBalancedTree(root->left, &l)) {
				return false;
			}
		}
		if (root->right != nullptr) {
			if (!IsBalancedTree(root->right, &r)) {
				return false;
			}
		}

		if (std::abs(l - r) > 1) {
			return false;
		}

		*h = 1 + std::max(l, r);

		return true;
	}

	bool B_Solution(const Node* root) {
		int h = 0;
		return IsBalancedTree(root, &h);
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
	// I_DifferentTrees
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
	/*-------------------------------------------------------------------------*/
	// J_InsertNode
	nNode* insert(nNode* root, int key) {
		if (key < root->value) {
			if (root->left == nullptr) {
				root->left = new nNode({ nullptr, nullptr, key });
			}
			else {
				insert(root->left, key);
			}
		}
		else { // key >= root->value
			if (root->right == nullptr) {
				root->right = new nNode({ nullptr, nullptr, key });
			}
			else {
				insert(root->right, key);
			}
			
		}	
		return root;
	}
	/*-------------------------------------------------------------------------*/
	// K_PrintRange
	void PrintLMR(const Node* root) {
		if (root->left != nullptr) {
			PrintLMR(root->left);
		}
		
		std::cout << root->value << '\n';

		if (root->right != nullptr) {
			PrintLMR(root->right);
		}
	}

	void FindElement(const Node* root, int val) {		
		if (root->value < val) { // check right subtree due to seeking node located in right side	
			if (root->right != nullptr) {
				FindElement(root->right, val);
			}
		}
		else  {			
			if (root->left != nullptr) {
				FindElement(root->left, val);
			}
			std::cout << root->value;
		}
		
	}

	void print_range(const Node* root, int start, int end) {
		if (root->left != nullptr) {
			print_range(root->left, start, end);
		}

		if (start <= root->value && root->value <= end) {
			std::cout << root->value;
		}
		else if (root->value > end) {
			return;
		}

		if (root->right != nullptr) {
			print_range(root->right, start, end);
		}
	}
	/*-------------------------------------------------------------------------*/
	// L Binary Heap SiftDown
	int siftDown(std::vector<int>& heap, int idx) {
		int l_idx = 2 * idx;
		int r_idx = 2 * idx + 1;
		int size = heap.size() - 1;

		if (size < l_idx) {
			return idx;
		}

		int largest_idx = -1;
		if (r_idx <= size && heap[l_idx] < heap[r_idx]) {
			largest_idx = r_idx;
		}
		else {
			largest_idx = l_idx;
		}

		if (heap[idx] < heap[largest_idx]) {
			std::swap(heap[idx], heap[largest_idx]);
			return siftDown(heap, largest_idx);
		}
		return idx;
	}

	int pop_max(std::vector<int>& heap) {
		int res = heap[1];
		heap[1] = heap[heap.size()];

		heap.pop_back();
		siftDown(heap, 1);
		return res;
	}

	/*-------------------------------------------------------------------------*/
	// M Binary Heap SiftUP
	int siftUp(std::vector<int>& heap, int idx) {
		if (idx == 1) {
			return 1;
		}
		int parent_idx = idx / 2;
		if (heap[parent_idx] < heap[idx]) {
			std::swap(heap[parent_idx], heap[idx]);
			return siftUp(heap, parent_idx);
		}
		return idx;

	}

	void heap_add(std::vector<int>& heap, int key) {
		int idx = heap.size();
		heap.push_back(key);		
		siftUp(heap, idx);
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
		assert(s5_problems::A_Solution(&node4) == 3);
	}
	/*-------------------------------------------------------------------------*/
	void B_BalancedTree() {
		{
			s5_problems::Node node1({ 1, nullptr, nullptr });
			s5_problems::Node node2({ -5, nullptr, nullptr });
			s5_problems::Node node3({ 3, &node1, &node2 });
			s5_problems::Node node4({ 10, nullptr, nullptr });
			s5_problems::Node node5({ 2, &node3, &node4 });
			assert(s5_problems::B_Solution(&node5));
		}
		{
			s5_problems::Node node1({ 1, nullptr, nullptr });
			s5_problems::Node node2({ 5, nullptr, nullptr });
			s5_problems::Node node3({ 3, &node1, &node2 });
			assert(s5_problems::B_Solution(&node3) == true);
			s5_problems::Node node4({ 10, &node3, nullptr });
			assert(s5_problems::B_Solution(&node4) == false);
			s5_problems::Node node5({ 30, nullptr, nullptr });
			s5_problems::Node node6({ 20, &node4, &node5 });
			assert(s5_problems::B_Solution(&node6) == false);
		}
	}
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
	/*-------------------------------------------------------------------------*/
	void J_InsertNode() {
		{			
			s5_problems::nNode node1({ nullptr, nullptr, 7 });
			s5_problems::nNode node2({ &node1, nullptr, 8 });
			s5_problems::nNode node3({ nullptr, &node2, 7 });
			s5_problems::nNode* newHead = s5_problems::insert(&node3, 6);
			assert(newHead->left->value == 6);
			assert(newHead == &node3);			
		}
		{
			s5_problems::nNode node1({ nullptr, nullptr, 7 });
			s5_problems::nNode node2({ &node1, nullptr, 8 });
			s5_problems::nNode node3({ nullptr, &node2, 7 });
			s5_problems::nNode* newHead = s5_problems::insert(&node3, 7);
			assert(newHead->right->left->right->value == 7);
			assert(newHead == &node3);
		}
	}
	/*-------------------------------------------------------------------------*/
	void K_PrintRange() {
		{
			s5_problems::Node node1({ 2, nullptr, nullptr });
			s5_problems::Node node2({ 1, nullptr, &node1 });
			s5_problems::Node node3({ 8, nullptr, nullptr });
			s5_problems::Node node4({ 8, nullptr, &node3 });
			s5_problems::Node node5({ 9, &node4, nullptr });
			s5_problems::Node node6({ 10, &node5, nullptr });
			s5_problems::Node node7({5,  &node2, &node6 });
			//s5_problems::PrintLMR(&node7);
			//s5_problems::FindElement(&node7, 10);
			//s5_problems::print_range(&node7, 2, 8);
			// expected output: 2 5 8 8
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_BinaryHeap_SiftDown() {		
		{
			std::vector<int> sample = { -1, 12, 1, 8, 3, 4, 7 };
			assert(s5_problems::siftDown(sample, 2) == 5);
		}
	}
	/*-------------------------------------------------------------------------*/
	void M_BinaryHeap_SiftUp() {
		std::vector<int> sample = { -1, 12, 6, 8, 3, 15, 7 };
		assert(s5_problems::siftUp(sample, 5) == 1);
	}
}