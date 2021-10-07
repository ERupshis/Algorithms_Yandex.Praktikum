#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <tuple>

namespace s5_exam_problems {
	using namespace std::literals;

	//SEND ID: 54101199

	struct Participant {
		std::string name = ""s;
		int solved_problems = 0;
		int penalty = 0;

		bool operator < (const Participant& other) {
			if (solved_problems > other.solved_problems) {
				return true;
			}
			else if (solved_problems == other.solved_problems) {
				if (penalty < other.penalty) {
					return true;
				}
				else if (penalty == other.penalty) {
					return name < other.name;
				}
			}
			return false;
		}

		bool operator == (const Participant& other) {
			return name == other.name
				&& solved_problems == other.solved_problems
				&& penalty == other.penalty;
		}
	};

	std::vector<Participant> FillVectorOfParticipants(std::istream& input, int size = 0) {
		std::vector<Participant> res;
		if (size == 0) {
			int cnt;
			input >> cnt;
			res.reserve(cnt);
		}
		else {
			res.reserve(size);
		}

		for (size_t i = 0; i < res.capacity(); ++i) {
			std::string name;
			int problems, penalty;
			input >> name >> problems >> penalty;
			res.push_back({ name, problems, penalty });
		}
		return res;
	}

	std::ostream& operator << (std::ostream& output, const std::vector<Participant>& arr) {
		for (const Participant& member : arr) {
			output << member.name << '\n';
		}
		return output;
	}


	// Class MinHeap - class with std::vector as a storage. Using vector as a storage helps to access to heap 'nodes' 
	//    with O(1) time complexity without using excess memory. This can be achieved thanks to heap tree property - it's a full binary tree.
	//    It means that all edges on the levels 0 ... h - 2 has both childs. Only level h - 1 nodes children may be missing. It corresponds to 
	//    property of AVL binary tree - search reduces twice on every recursion level and search of any key can be done by O(h) time complexity.
	//    (difference between left subtree and right subgtree heights doesn't exceeds 1)
	// Time complexity: see below
	// Space complexity: O(N) - N is a number of elemnets in heap
	//
	// Method Add() - inserts new element to the end of vector and move it in correct position in tree. It's achieved by comprasioning new value with its 
	//    parent and if parent is bigger that new element then they should be swaped.
	// Time complexity: O(logN) or O(h), where's N - number of elements in heap, h - height of tree
	// Space complexity: O(logN) is used for definition of parent index on every recursion level
	//
	// Method Pop() - extract lowest element from heap (first (root) element in heap). It's achieved by swapping last and first element in heap.
	//    And after that new root value(that was last element before) should be placed in correct node. Behavior of this action is similar to part of Add(),
	//    but direction of checking is opposite
	// Time complexity: O(logN) or O(h), where's N - number of elements in heap, h - height of tree 
	// Space complexity: O(logN) is used for definition of child indexes on every recursion level

	class MinHeap {
	public:
		void Add(const Participant& member) {			
			heap_.push_back(member);
			int idx = heap_.size() - 1; // get index of new member. It's equal to vec.size() - 1, when element was already inserted
			SiftUp(idx); // launch new member positioning in heap
		}

		Participant Pop() {
			Participant res;
			if (heap_.size() == 1) { // case when heap has 1 member, recursion SiftDown is not needed
				res = heap_[0];
				heap_.pop_back();	// just remove this member form heap			
			} else if(heap_.size() > 1) {
				res = heap_[0]; // head value to extract
				heap_[0] = heap_[heap_.size() - 1]; // rewrite last member in top idx

				heap_.pop_back(); // remove last argument
				SiftDown(0); // move down last elem if neeeded				
			}
			return res; // return empty member if heap is empty;			
		}

		size_t Size() const {
			return heap_.size();
		}

	private:
		std::vector<Participant> heap_ = {}; // first value [0] is not operational

		int SiftUp(int idx) {
			if (idx == 0) { // first value in heap
				return 0;
			}

			int parent_idx = (idx - 1) / 2;

			if (heap_[idx] < heap_[parent_idx]) { // level up new member in heap
				std::swap(heap_[parent_idx], heap_[idx]);
				return SiftUp(parent_idx);
			}

			return idx; // case when Participant in right position
		}

		int SiftDown(int idx) {
			int l_idx = 2 * idx + 1;
			int r_idx = 2 * idx + 2;			

			if (heap_.size() - 1 < l_idx) { // idx doesn't have child nodes;
				return idx;
			}

			int lowest_idx = -1;
			if (heap_.size() - 1 >= r_idx && heap_[r_idx] < heap_[l_idx]) { // define which child is lowest. 
				lowest_idx = r_idx;								// It guarantees that another branch will be synchronized with new root member
			}
			else {
				lowest_idx = l_idx;
			}

			if (heap_[lowest_idx] < heap_[idx]) { // swap and launch recursion if needed
				std::swap(heap_[idx], heap_[lowest_idx]);
				return SiftDown(lowest_idx);
			}
			return idx; // new member is already in correct place
		}
	};


	// HeapSort() - sorting function that uses heap as a sort method. It's achieved by main heap property - every parent is less that its children
	//    This guarantee that root of heap will be the lowest element in heap all the time
	//
	// Time complexity: O(N*logN) - N is a number of elemnts in array
	// Space complexity: O(N)
	void A_HeapSort(std::istream& input, std::ostream& output) {
		std::vector<Participant> arr = std::move(FillVectorOfParticipants(input));

		MinHeap heap;
		for (size_t i = 0; i < arr.size(); ++i) {
			heap.Add(arr[i]);
		}

		std::vector<Participant> res;
		while (heap.Size() > 0) {
			res.push_back(heap.Pop());
		}

		output << res;
	}
	/*-------------------------------------------------------------------------*/
	// remove node from BST
	//#include "solution.h"

	//SEND ID: 53975526
	struct Node {
		Node* left;
		Node* right;
		int value;
	};
		

	// FindNodes() method that returns pointer to ode with value Key and pointer to parent of this node with definition which child 
	//    of parent this node is (left or right). It's a recursion method.
	//
	// Time colpexity: O(logN) or O(h) - N is a number of elements in BST, h - height of BST
	// Space compoexity: O(1)

	std::tuple<Node*, Node*> FindNodes(Node* root, int key) {
		while (root != nullptr) {
			if (root->value == key) { // base case - tree root should be removed
				return { nullptr, root };
			} 
			else if (root->left != nullptr && root->left->value == key) {	// base case when key was found;
				return { root, root->left };
			}
			else if (root->right != nullptr && root->right->value == key) { // base case when key was found;
				return { root, root->right };
			} 
			else if (key < root->value) {
				root = root->left;
			}
			else if (key > root->value) {
				root = root->right;
			}
		}
		return { nullptr, nullptr };
	}

	// FindBiggestNodes() - method that finds biggest element in tree. (name of method is not yet correct because biggest node will be p, 
	//    parent of p may be not the first before p due to p can have child less itself)
	//    This method return two pointers: to the rightest element in tree and to its parent
	//    It's a recursion method
	// 
	// Time complexity: O(logN) or O(h) - N is a number of nodes in tree, h - height of tree. Actually it can handle for O(h-1) because we check
	//    child of current node on the biggest value condition in tree
	// Space complexity: O(1)

	std::tuple<Node*, Node*> GetRightmostNode(Node* root) {
		if (root->right == nullptr) { //case when there's no right node in left subtree of d. Just need to 										
			return { nullptr, root }; //reconnect whole left subtree directly to d_par
		}

		while (root->right->right != nullptr) { //case of chain with 3 or more right subtrees
			root = root->right;
		}
		return { root, root->right };  // case when p_par -> p chain is found
	}

	// ReplaceDnodebyPnode() - method that disconnect links to node that should be deleted and link biggest node from d->left instead of d
	//
	// Time complexity: O(logN) or O(h) - N is a number of nodes in left subtree, h - height of left subtree. 
	//    Actually it can handle for O(h-1) because we check
	//    child of current node on the biggest value condition in left subtree
	// Space complexity: O(1)

	Node* ReplaceDnodebyPnode(Node* d) {
		Node* p_par;
		Node* p;		
		std::tie(p_par, p) = GetRightmostNode(d->left);
		if (p_par != nullptr) { //  opposite case when d->left has only one node in tree or d->left->left != nullptr		
			if (p->left == nullptr) { // case when biggest right sub tree in d->left doesn't have left subtree.
				p_par->right = nullptr;
			}
			else {// case when biggest right sub tree in d->left HAS left subtree.
				p_par->right = p->left;
			}
			p->left = d->left;
		}
		p->right = d->right;	

		return p;
	}

	// ConnectNodeToParent() - method that link new node to the parent of deleted node
	//
	// Time complexity: O(1)
	// Space complexity: O(1)

	void ConnectNodeToParent(Node* parent, Node* child, Node* old_child) {
		if (old_child == parent->left) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}
	}
	
	// remove() - method that removes node with value equal to key.
	//    
	// Time complexity: O(logN) or O(h) - N is a number of nodes in tree, h - height of tree
	// Space complexity: O(1)

	Node* remove(Node* root, int key) {
		if (root == nullptr) { // empty tree
			return nullptr;
		}

		Node* d_par; 
		Node* d;		
		std::tie(d_par, d) = FindNodes(root, key); // seek element to remove

		if (d_par == nullptr && d != nullptr) { // tree root should be removed
			if (d->left == nullptr) {
				return d->right;
			}
			else {
				return ReplaceDnodebyPnode(d);
			}
		}
		else if (d_par != nullptr && d != nullptr) { // element is found
			if (d->left == nullptr) { // d->left is missing, just connect d->right to d_par
				ConnectNodeToParent(d_par, d->right, d);
			}
			else {
				ConnectNodeToParent(d_par, ReplaceDnodebyPnode(d), d);
			}
		}
		//delete d;
		d = 0;
		return root; // if element was not found no action to do, otherwise return root of updated tree
	}
}


namespace s5_exam_tests {
	using namespace std::literals;
	using namespace s5_exam_problems;

	void A_HeapSort() {
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 4 100"s << '\n'
				<< "gena 6 1000"s << '\n'
				<< "gosha 2 90"s << '\n'
				<< "rita 2 90"s << '\n'
				<< "timofey 4 80"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "gena"s << '\n'
				<< "timofey"s << '\n'
				<< "alla"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 0 0"s << '\n'
				<< "gena 0 0"s << '\n'
				<< "gosha 0 0"s << '\n'
				<< "rita 0 0"s << '\n'
				<< "timofey 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "alla"s << '\n'
				<< "gena"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n'
				<< "timofey"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "13"s << '\n'
				<< "tufhdbi 76 58"s << '\n'
				<< "rqyoazgbmv 59 78"s << '\n'
				<< "qvgtrlkmyrm 35 27"s << '\n'
				<< "tgcytmfpj 70 27"s << '\n'
				<< "xvf 84 19"s << '\n'
				<< "jzpnpgpcqbsmczrgvsu 30 3"s << '\n'
				<< "evjphqnevjqakze 92 15"s << '\n'
				<< "wwzwv 87 8"s << '\n'
				<< "tfpiqpwmkkduhcupp 1 82"s << '\n'
				<< "tzamkyqadmybky 5 81"s << '\n'
				<< "amotrxgba 0 6"s << '\n'
				<< "easfsifbzkfezn 100 28"s << '\n'
				<< "kivdiy 70 47"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "easfsifbzkfezn"s << '\n'
				<< "evjphqnevjqakze"s << '\n'
				<< "wwzwv"s << '\n'
				<< "xvf"s << '\n'
				<< "tufhdbi"s << '\n'
				<< "tgcytmfpj"s << '\n'
				<< "kivdiy"s << '\n'
				<< "rqyoazgbmv"s << '\n'
				<< "qvgtrlkmyrm"s << '\n'
				<< "jzpnpgpcqbsmczrgvsu"s << '\n'
				<< "tzamkyqadmybky"s << '\n'
				<< "tfpiqpwmkkduhcupp"s << '\n'
				<< "amotrxgba"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "8"s << '\n'
				<< "04 0 0"s << '\n'
				<< "08 0 0"s << '\n'
				<< "09 0 0"s << '\n'
				<< "20 0 0"s << '\n'
				<< "01 0 0"s << '\n'
				<< "05 0 0"s << '\n'
				<< "03 0 0"s << '\n'
				<< "10 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "01"s << '\n'
				<< "03"s << '\n'
				<< "04"s << '\n'
				<< "05"s << '\n'
				<< "08"s << '\n'
				<< "09"s << '\n'
				<< "10"s << '\n'
				<< "20"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "alla 4 100"s << '\n'
				<< "gena 6 1000"s << '\n'
				<< "gosha 2 90"s << '\n'
				<< "rita 2 90"s << '\n'
				<< "timofey 7 80"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "timofey"s << '\n'
				<< "gena"s << '\n'
				<< "alla"s << '\n'
				<< "gosha"s << '\n'
				<< "rita"s << '\n';
			assert(output.str() == res.str());
		}

		{
			std::stringstream input;
			input << "1"s << '\n'
				<< "a 0 0"s;
			std::ostringstream output(std::ios_base::ate);
			s5_exam_problems::A_HeapSort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "a"s << '\n';
			assert(output.str() == res.str());
		}			
	}
	/*-------------------------------------------------------------------------*/
	void B_RemoveNodeFromBST() {		
		{			
			Node node10({ nullptr, nullptr, 99 });
			Node node9({ nullptr, nullptr, 72 });
			Node node8({ &node9, &node10, 91 });
			Node node7({ nullptr, nullptr, 50 });
			Node node6({ nullptr, nullptr, 32 });
			Node node5({ nullptr, &node6, 29 });
			Node node4({ nullptr, nullptr, 11 });
			Node node3({ &node7, &node8, 65 });
			Node node2({ &node4, &node5, 20 });
			Node node1({ &node2, &node3, 41 });
			Node* newHead = remove(&node1, 41);
			assert(newHead->value == 32);
			assert(newHead->right == &node3);
			assert(newHead->left == &node2);
		}
		{
			Node node2({ nullptr, nullptr, 2 });
			Node node1({ nullptr, &node2, 1 });
			Node* newHead = remove(&node1, 1);
			assert(newHead->value == 2);
		}
		{
			Node node1({ nullptr, nullptr, 2 });
			Node node2({ &node1, nullptr, 3 });
			Node node3({ nullptr, &node2, 1 });
			Node node4({ nullptr, nullptr, 6 });
			Node node5({ &node4, nullptr, 8 });
			Node node6({ &node5, nullptr, 10 });
			Node node7({ &node3, &node6, 5 });
			Node* newHead = remove(&node7, 10);
			assert(newHead->value == 5);
			assert(newHead->right == &node5);
			assert(newHead->right->value == 8);
		}
	}
}