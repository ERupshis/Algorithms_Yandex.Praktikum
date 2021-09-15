#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <optional>
#include <cmath>
#include <stack>
#include <cassert>

namespace s2_problems {
	using namespace std::literals;


    std::vector<std::vector<int>> FillMatrix(std::istream& input);

    std::vector<std::vector<int>> TransposeMatrix(const std::vector<std::vector<int>>& matrix);

    template <typename type>
    std::ostream& operator<< (std::ostream& out, const std::vector<std::vector<type>>& vector) {
        for (size_t i = 0; i < vector.size(); ++i) {
            bool f = false;
            for (size_t j = 0; j < vector[i].size(); ++j) {
                if (f) {
                    out << ' ';
                }
                else {
                    f = true;
                }
                out << vector[i][j];
                if (j == vector[i].size() - 1) {
                    out << '\n';
                }
            }            
        }
        return out;
    }

    void A_Monitoring(std::istream& input, std::ostream& output);
	/*-------------------------------------------------------------------------*/
    void B_ListToDo();
    /*-------------------------------------------------------------------------*/
    void С_LeastFavoriteThing();
    /*-------------------------------------------------------------------------*/
    void D_CaringMother();
    /*-------------------------------------------------------------------------*/    
    void E_EverythingOppsite();
    /*-------------------------------------------------------------------------*/
    class StackMax {
    public:
        void Push(int num) {
            stack.push_back(num);
        }

        bool Pop() {
            if (stack.size() == 0) {
                return false;
            }
            stack.pop_back();
            return true;
        }

        std::string GetMax() const {
            if (stack.size() == 0) {
                return "None"s;
            }

            int res = INT32_MIN;
            for (int num : stack) {
                if (num > res) {
                    res = num;
                }
            }
            return std::to_string(res);
        }

    private:
        std::string empty = ""s;
        std::vector<int> stack{};
    };

    void F_StackMax(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    void H_BracketSequence(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    class StackMaxEffective {
    public:
        void Push(int num) {
            if (num > max_elem_) {
                max_elem_ = num;
            } 
            max_elem_stack_.push_back(max_elem_);            
            stack_.push_back(num);
        }

        bool Pop() {
            if (stack_.size() == 0) {
                return false;
            }
            max_elem_stack_.pop_back();
            stack_.pop_back();
            if (max_elem_stack_.size() == 0) {
                max_elem_ = INT32_MIN;
            }
            else {
                max_elem_ = max_elem_stack_.back();
            }
            return true;
        }

        std::string GetMax() const {
            if (stack_.size() == 0) {
                return "None"s;
            }

            return std::to_string(max_elem_stack_.back());
        }

        
    private:   
        int max_elem_ = INT32_MIN;
        std::string empty_ = ""s;        
        std::vector<int> stack_{}; 
        std::vector<int> max_elem_stack_{};        
    };

    void G_StackMaxEffective(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    class MyQueueSized {
    public:
        explicit MyQueueSized(int size)
            : max_n_(size), queue_(std::vector<int>(size)) { 
        }

        bool Push(int num) {  
            if (size_ == max_n_) {
                return false;
            }
            queue_[(tail_) % max_n_] = num;
            ++size_;
            tail_ = (tail_ + 1) % max_n_;

            return true;
        }

        std::string Pop() {
            if (IsEmpty()) {
                return "None"s;
            }

            int tmp = queue_[head_];
            queue_[head_] = 0; // not necessary
            --size_;
            head_ = (head_ + 1) % max_n_;
            return std::to_string(tmp);
        }

        std::string Peek() {
            if (IsEmpty()) {
                return "None"s;
            }
            return std::to_string(queue_[head_]);
        }

        int Size() {
            return size_;
        }

    private:
        int head_ = 0;
        int tail_ = 0;
        int max_n_;
        int size_ = 0;

        std::vector<int> queue_;

        bool IsEmpty() {
            return size_ == 0;
        }

    };

    void I_LimitedQueue(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    class MyQueueOnList {
    public:
        MyQueueOnList() = default;

        std::optional<int> Get() {
            if (queue_.size() == 0) {
                return std::nullopt;
            }
            int tmp = queue_.front();
            queue_.pop_front();
            return tmp;
        }

        void Put(int num) {
            queue_.push_back(num);
        }

        int Size() {
            return queue_.size();
        }

    private:
        std::list<int> queue_;
    };

    void J_ListedQueue(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    int RecFibo(int n);

    void K_RecursionFibonacci(std::istream& input, std::ostream& output);
    /*-------------------------------------------------------------------------*/
    int RecFiboAbs(int n, int k);

    void L_RecursionFibonacciAbs(std::istream& input, std::ostream& output);
}

namespace s2_tests {
	using namespace std::literals;

    void A_Monitoring();
	/*-------------------------------------------------------------------------*/
    void F_StackMax();
    /*-------------------------------------------------------------------------*/
    void G_StackMaxEffective();
    /*-------------------------------------------------------------------------*/
    void H_BracketSequence();
    /*-------------------------------------------------------------------------*/
    void I_LimitedQueue();
    /*-------------------------------------------------------------------------*/
    void J_ListedQueue();
    /*-------------------------------------------------------------------------*/
    void K_RecursionFibonacci();
    /*-------------------------------------------------------------------------*/
    void L_RecursionFibonacciAbs();
}
