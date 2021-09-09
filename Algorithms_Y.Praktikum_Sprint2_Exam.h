#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <cmath>
#include <stack>

#include <sstream>
#include <assert.h>

namespace s2_exam_problems {
	using namespace std::literals;

	//SEND ID: 52798944

	class Deque {
		// *I've decided to use std::vector as an internal storage for deque due to:
		// storage_ size is limited in the begining by condition
		// All operations with existing cells will be executed at O(1) time
		// 
		// head_ and tail_ pointers will be used to observe where back (tail_) and front (head_)
		// of seq elements in storage
		// [][][val1][val2][val3][][][]
		//  head_ points to val1, tail_point to cell next to val3
		//    
		// *Time complexity - O(1)  due to constant time access to elements of vector.
		// Elements moving is not required
		// *Space complexity - O(n) where is n is a number of element in vector. 
		// This space is reserved in the Deque constructor
		// 

	public:
		explicit Deque(int max_size)
			:max_size_(max_size) {
			storage_ = std::vector<int>(max_size);
		}
		
		bool push_back(int num) {
			if (size_ == max_size_) {
				return false;
			}
			storage_[tail_] = num;
			tail_ = (tail_ + 1) % max_size_;
			++size_;
			return true;
		}

		bool push_front(int num) {
			if (size_ == max_size_) {
				return false;
			}
			(head_ == 0) ? head_ = max_size_ - 1 : head_ = (head_ - 1) % max_size_;
			storage_[head_] = num;
			++size_;
			return true;
		}

		std::optional<int> pop_back() {
			if (size_ == 0) {
				return std::nullopt;
			}			
			(tail_ == 0) ? tail_ = max_size_ - 1 : tail_ = (tail_ - 1) % max_size_;
			int res = storage_[tail_];
			--size_;
			return res;
		}

		std::optional<int> pop_front() {
			if (size_ == 0) {
				return std::nullopt;
			}
			int res = storage_[head_];
			head_ = (head_ + 1) % max_size_;
			--size_;
			return res;
		}

	private:
		int max_size_;
		int size_ = 0;
		int head_ = 0;
		int tail_ = 0;
		std::vector<int> storage_;
	};

	void A_Deque(std::istream& input, std::ostream& output) {
		int n, deq_size;
		input >> n >> deq_size;

		std::string error = "error\n"s;

		Deque deque(deq_size);
		while (n > 0) {
			std::string req;
			input >> req;
			if (req == "push_back"s) {
				int num;
				input >> num;
				if (!deque.push_back(num)) {
					output << error;
				}
			}
			else if (req == "push_front"s) {
				int num;
				input >> num;				
				if (!deque.push_front(num)) {
					output << error;
				}
			}
			else if (req == "pop_back"s) {
				std::optional<int> response = deque.pop_back();
				if (!response) {
					output << error;
				}
				else {
					output << response.value() << '\n';
				}
			}
			else if (req == "pop_front"s) {
				std::optional<int> response = deque.pop_front();
				if (!response) {
					output << error;
				}
				else {
					output << response.value() << '\n';
				}
			}
			--n;
		}
	}
	/*-------------------------------------------------------------------------*/
	// SEND ID: 52800303

	// IsSing() - check if 'str' in B_Calc contain an arithmetic sign 
	// Time complexity - O(1)
	// Space complexity - 0?

	bool IsSign(const std::string& str) { // check if str is a special sign
		if (str.size() == 1 && (str[0] == '+' 
								|| str[0] == '-' 
								|| str[0] == '*' 
								|| str[0] == '/')
			) {
			return true;
		}
		return false;
	}

	// PerformOperation()  - extract two last operand from stack and execute arithmetic 
	// operation according 'sign_str' varible value.
	// Time complexity - O(1)
	// Space complexity - 0? temporary variable are stored in automatic memory

	void PerformOperation(const std::string& sign_str, std::stack<int>& stack) {
		int num2 = stack.top(); // opposite sequnece of elements in stack
		stack.pop();
		int num1 = stack.top();
		stack.pop();

		if (sign_str[0] == '+') {
			stack.push(num1 + num2);
		}
		else if (sign_str[0] == '-') {
			stack.push(num1 - num2);
		}
		else if (sign_str[0] == '*') {
			stack.push(num1 * num2);
		}
		else if (sign_str[0] == '/') {
			int res = num1 / num2;
			if (num1 >= 0) {
				stack.push(res);
			}
			else {
				if (num1 == num2 * (num1 / num2)) {
					stack.push(res); // a = b * c (c is a result of a / b) integer division of a to b
				}
				else {
					stack.push(res - 1); // rounding of negative integers dividing;
				}
			}			
		}
	}

	// B Calc() - contains only one cycle of reading and processing signs and integers from istream
	// standard stack was chosen as a container due to it allows to extract last elements for a O(1) time complexity.
	// Every step of cycle read input stream and assign this value to 'str'  variable, check if special arithmetic sign (+, -, /, *) has come
	// from stream(func IsSign() which returns boolean value):
	//  - if yes - func PerformOperation() extracts two last integers from stack and perform arithmetic operation (according symbol that is stored in 'str')
	//    and push result in stack instead of two operands
	//  - if no - new integer has come from input stream which should be added in the end of stack for a O(1) time complexity due to
	//    std::stack generates stack based on deque by default. And the cost of pop and push operations is a O(1).
	//
	// Time complexity - O(n) where n is a count of operands and arithmetic signs. I would say that qty of operands may be 2*(n-1) + 1 due to we push in stack 
	//	  temporary result of arithm. execution. But we don't take into account multipliers in complexity execution. We are worry about the powers of n in formula.
	// 
	// Space compelixty - O(n) where is n - is qty of integer operands from input stream (n is max in case if all arithmetic sign in the end of input (example: 1 2 3 4 5 6 * + - + /),
	//	  the best situation when arithemtic sign are located one-by-one with operands (1 2 + 3 * 4 - 5 - 6 /) - in this way n is  equal 2)     

	void B_Calc(std::istream& input, std::ostream& output) {
		std::stack<int> stack;
		while (true) {
			std::string str;
			input >> str;
			if (str.empty()) { // end of cycle
				break;
			}
			if (IsSign(str)) { // check if str has special sign inside
				PerformOperation(str, stack); // Execute sign action
				continue;
			}
			stack.push(std::stoi(str));	// str has int inside - need to add in stack;		
		}
		output << stack.top();
	}
}

namespace s2_exam_tests {
	using namespace std::literals;

	void A_Deque() {
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "4"s << '\n'
				<< "push_front 861"s << '\n'
				<< "push_front -819"s << '\n'
				<< "pop_back"s << '\n'
				<< "pop_back"s;
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::A_Deque(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "861"s << '\n'
				<< "-819"s << '\n';				
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "7"s << '\n'
				<< "10"s << '\n'
				<< "push_front -855"s << '\n'
				<< "push_front 720"s << '\n'
				<< "pop_back"s << '\n'
				<< "pop_back"s << '\n'
				<< "push_back 844"s << '\n'
				<< "pop_back"s << '\n'
				<< "push_back 823"s;
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::A_Deque(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "-855"s << '\n'
				<< "720"s << '\n'
				<< "844"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "6"s << '\n'
				<< "push_front -201"s << '\n'
				<< "push_back 959"s << '\n'
				<< "push_back 102"s << '\n'
				<< "push_front 20"s << '\n'
				<< "pop_front"s << '\n'
				<< "pop_back"s; 				
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::A_Deque(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "20"s << '\n'
				<< "102"s << '\n';				
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "4"s << '\n'
				<< "push_front -201"s << '\n'
				<< "push_back 959"s << '\n'
				<< "push_back 102"s << '\n'
				<< "push_front 20"s << '\n'
				<< "push_front 100"s << '\n'
				<< "push_back 100"s;
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::A_Deque(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "error"s << '\n'
				<< "error"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "2"s << '\n'				
				<< "pop_front"s << '\n'
				<< "pop_back"s;
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::A_Deque(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "error"s << '\n'
				<< "error"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_Calc() {
		{
			std::istringstream input("4 2 * 4 / 25 * 2 - 12 / 500 2 * + 2 / -999 + 71 + -1 * 2 / 1000 + 6 * 8065 - 787 + 66 * 456 - 45 * 10 /"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "-2052"s);
		}
		{
			std::istringstream input("4 2 * 4 / 25 * 2 - 12 / 500 2 * + 2 / -999 + 71 + -1 * 2 / 1000 + 6 * 8065 - 787 + 66 * 456 - 45 * 10 / 3000 +"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "948"s);
		}
		{
			std::istringstream input("0 1 / 2 -4 - / 9 4 - -6 9 - - +"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "20"s);
		}		
		{
			std::istringstream input("2 1 + 3 *"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "9"s);
		}
		{
			std::istringstream input("7 2 + 4 * 2 +"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "38"s);
		}
		{
			std::istringstream input("-1 3 /"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "-1"s);
		}
		{
			std::istringstream input("-7 2 /"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "-4"s);
		}
		{
			std::istringstream input("12 5 /"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "2"s);
		}
		{
			std::istringstream input("10 2 4 * -"s);
			std::ostringstream output(std::ios_base::ate);
			s2_exam_problems::B_Calc(input, output);
			assert(output.str() == "2"s);
		}		
	}
}
