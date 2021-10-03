#pragma once

#include <string>
#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>

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
	// C_Anagram trees
	void TraversalLMR(const Node* root, std::vector<int>& vec) {
		if (root->left != nullptr) {
			TraversalLMR(root->left, vec);
		}
		vec.push_back(root->value);
		if (root->right != nullptr) {
			TraversalLMR(root->right, vec);
		}
	}
	void TraversalRML(const Node* root, std::vector<int>& vec) {
		if (root->right != nullptr) {
			TraversalRML(root->right, vec);
		}
		vec.push_back(root->value);
		if (root->left != nullptr) {
			TraversalRML(root->left, vec);
		}
	}

	bool C_Solution(const Node* root) {
		if (root->left != nullptr && root->right != nullptr) {
			std::vector<int> left, right;
			TraversalLMR(root->left, left);
			TraversalRML(root->right, right);
			return left == right;
		}
		else if (root->left == nullptr && root->right == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	/*-------------------------------------------------------------------------*/
	// D Twin Trees
	bool D_Solution(const Node* root1, const Node* root2) {
		if (root1 != nullptr && root2 != nullptr) {
			std::vector<int> first, second;
			TraversalLMR(root1, first);
			TraversalLMR(root2, second);
			return first == second;
		}
		else if (root1 == nullptr && root2 == nullptr) {
			return true;
		}
		else {
			return false;
		}
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
	// F Max Depth
	int FindTreeHeight(const Node* root) {
		if (root == nullptr) { // terminal node case
			return 0;
		}

		return 1 + std::max(FindTreeHeight(root->left), FindTreeHeight(root->right));
	}


	int F_Solution(const Node* root) {
		return FindTreeHeight(root);
	}
	/*-------------------------------------------------------------------------*/
	// G Max Path
	int FindMaxPath(const Node* root, int* max_len) {
		if (root == nullptr) {
			return 0;
		}

		int left_path = FindMaxPath(root->left, max_len);
		int right_path = FindMaxPath(root->right, max_len);
		int subtree_path = root->value + ((left_path > 0) ? left_path : 0) + ((right_path > 0) ? right_path : 0);
		if (*max_len < subtree_path) {
			*max_len = subtree_path;
		}

		return root->value + ((std::max(left_path, right_path) > 0) ? std::max(left_path, right_path) : 0);
	}

	int G_Solution(const Node* root) {
		int max_length = INT32_MIN;
		if (root != nullptr) {
			FindMaxPath(root, &max_length);
			return max_length;
		}
		else {
			return 0;
		}
	}
	/*-------------------------------------------------------------------------*/
	// H_NumberPaths	
	void SumNumberPaths(const Node* root, int* res, int path_sum = 0) {
		int merged_num = path_sum * 10 + root->value;
		if (root->left == nullptr && root->right == nullptr) {
			*res += merged_num;
		}
		else {			
			if (root->left != nullptr) { // base case
				SumNumberPaths(root->left, res, merged_num);
			}
			if (root->right != nullptr) {
				SumNumberPaths(root->right, res, merged_num);
			}
		}
	}

	int H_Solution(const Node* root) {
		int res = 0;
		SumNumberPaths(root, &res);
		return res;
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
	using namespace s5_problems;

	void A_Lamps() {
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ -5, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			Node node4({ 2, &node3, nullptr });
			assert(A_Solution(&node4) == 3);
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_BalancedTree() {
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ -5, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			Node node4({ 10, nullptr, nullptr });
			Node node5({ 2, &node3, &node4 });
			assert(B_Solution(&node5));
		}
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 5, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			assert(B_Solution(&node3) == true);
			Node node4({ 10, &node3, nullptr });
			assert(B_Solution(&node4) == false);
			Node node5({ 30, nullptr, nullptr });
			Node node6({ 20, &node4, &node5 });
			assert(B_Solution(&node6) == false);
		}
	}
	/*-------------------------------------------------------------------------*/
	void C_AnagramTrees() {
		{
			Node node8({ 0, nullptr, nullptr });
			Node node7({ 1, nullptr, nullptr });
			Node node6({ 1, nullptr, nullptr });
			Node node5({ 0, nullptr, nullptr });
			Node node4({ 3, &node7, &node8 });
			Node node3({ 3, &node5, &node6 });
			Node node2({ 2, nullptr, &node4 });
			Node node1({ 2, &node3, nullptr });
			Node node0({ 0, &node1, &node2 });
			assert(C_Solution(&node0));
		}
		{
			Node node1({ 3, nullptr, nullptr });
			Node node2({ 4, nullptr, nullptr });
			Node node3({ 4, nullptr, nullptr });
			Node node4({ 3, nullptr, nullptr });
			Node node5({ 2, &node1, &node2 });
			Node node6({ 2, &node3, &node4 });
			Node node7({ 1, &node5, &node6 });
			assert(C_Solution(&node7));
		}		
	}
	/*-------------------------------------------------------------------------*/
	void D_TwinTrees() {
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 2, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });

			Node node4({ 1, nullptr, nullptr });
			Node node5({ 2, nullptr, nullptr });
			Node node6({ 3, &node4, &node5 });
			assert(D_Solution(&node3, &node6));
		}
	}
	/*-------------------------------------------------------------------------*/
	void E_SearchTree() {
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 4, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			Node node4({ 8, nullptr, nullptr });
			Node node5({ 5, &node3, &node4 });
			assert(E_Solution(&node5));
		}
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 5, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			Node node4({ 8, nullptr, nullptr });
			Node node5({ 5, &node3, &node4 });
			assert(!E_Solution(&node5));
		}
	}
	/*-------------------------------------------------------------------------*/
	void F_MaxDepth() {
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 4, nullptr, nullptr });
			Node node3({ 3, &node1, &node2 });
			Node node4({ 8, nullptr, nullptr });
			Node node5({ 5, &node3, &node4 });
			assert(F_Solution(&node5) == 3);
		}
	}
	/*-------------------------------------------------------------------------*/
	void G_MaxPath() {
		{
			Node node1({ -1, nullptr, nullptr });			
			assert(G_Solution(&node1) == -1);
		}
		{
			Node node1({ -2, nullptr, nullptr });
			Node node2({ 3, nullptr, nullptr });
			Node node3({ 1, &node1, &node2 });			
			assert(G_Solution(&node3) == 4);
		}
		{
			Node node1({ -2, nullptr, nullptr });
			Node node2({ -3, nullptr, nullptr });
			Node node3({ 1, &node1, &node2 });
			assert(G_Solution(&node3) == 1);
		}
		{
			Node node1({ -2, nullptr, nullptr });
			Node node2({ -3, nullptr, nullptr });
			Node node3({ -1, &node1, &node2 });
			assert(G_Solution(&node3) == -1);
		}
		{
			Node node1({ -6, nullptr, nullptr });
			Node node2({ 9, nullptr, nullptr });
			Node node3({ -1, nullptr, nullptr });
			Node node4({ 0, nullptr, nullptr });
			Node node5({ 4, nullptr, nullptr });
			Node node6({ 3, &node2, &node1 });
			Node node7({ 7, &node3, nullptr });
			Node node8({ 3, &node5, &node4 });
			Node node9({ 2, &node7, &node6 });
			Node node10({ -1, &node9, &node8 });
			assert(G_Solution(&node10) == 21);
		}
		{
			Node node1({ 5, nullptr, nullptr });
			Node node2({ 1, nullptr, nullptr });
			Node node3({ -3, &node2, &node1 });
			Node node4({ 2, nullptr, nullptr });
			Node node5({ 2, &node4, &node3 });
			assert(G_Solution(&node5) == 6);
		}
	}
	/*-------------------------------------------------------------------------*/
	void H_NumberPaths() {
		{
			Node node1({ 9, nullptr, nullptr });
			Node node2({ 8, &node1, nullptr });
			Node node3({ 7, nullptr, nullptr });
			Node node4({ 6, nullptr, nullptr });
			Node node5({ 2, nullptr, nullptr });
			Node node6({ 4, &node3, &node2 });
			Node node7({ 3, &node5, &node4 });
			Node node8({ 2, nullptr, &node6 });
			Node node9({ 1, &node7, nullptr });
			Node node10({ 1, &node9, &node8 });
			assert(H_Solution(&node10) == 16004);
		}
		{
			Node node1({ 5, nullptr, nullptr });
			Node node2({ 3, nullptr, nullptr });
			Node node3({ 1, &node2, &node1 });			
			assert(H_Solution(&node3) == 28);
		}
		{
			Node node1({ 1, nullptr, nullptr });
			Node node2({ 2, nullptr, nullptr });
			Node node3({ 3, &node2, &node1 });
			Node node4({ 2, nullptr, nullptr });
			Node node5({ 1, &node4, &node3 });
			assert(H_Solution(&node5) == 275);
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
			nNode node1({ nullptr, nullptr, 7 });
			nNode node2({ &node1, nullptr, 8 });
			nNode node3({ nullptr, &node2, 7 });
			nNode* newHead = insert(&node3, 6);
			assert(newHead->left->value == 6);
			assert(newHead == &node3);			
		}
		{
			nNode node1({ nullptr, nullptr, 7 });
			nNode node2({ &node1, nullptr, 8 });
			nNode node3({ nullptr, &node2, 7 });
			nNode* newHead = insert(&node3, 7);
			assert(newHead->right->left->right->value == 7);
			assert(newHead == &node3);
		}
	}
	/*-------------------------------------------------------------------------*/
	void K_PrintRange() {
		{
			Node node1({ 2, nullptr, nullptr });
			Node node2({ 1, nullptr, &node1 });
			Node node3({ 8, nullptr, nullptr });
			Node node4({ 8, nullptr, &node3 });
			Node node5({ 9, &node4, nullptr });
			Node node6({ 10, &node5, nullptr });
			Node node7({5,  &node2, &node6 });
			//PrintLMR(&node7);
			//FindElement(&node7, 10);
			//print_range(&node7, 2, 8);
			// expected output: 2 5 8 8
		}
	}
	/*-------------------------------------------------------------------------*/
	void L_BinaryHeap_SiftDown() {		
		{
			std::vector<int> sample = { -1, 12, 1, 8, 3, 4, 7 };
			assert(siftDown(sample, 2) == 5);
		}
	}
	/*-------------------------------------------------------------------------*/
	void M_BinaryHeap_SiftUp() {
		std::vector<int> sample = { -1, 12, 6, 8, 3, 15, 7 };
		assert(siftUp(sample, 5) == 1);
	}
}