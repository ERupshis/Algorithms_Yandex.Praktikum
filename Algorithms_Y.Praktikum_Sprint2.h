#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

namespace s2_problems {
	using namespace std::literals;

	/*-------------------------------------------------------------------------*/
    void B_ListToDo() {
        /* //remove comment quote before sending Send for checking only as file in Y.Contest
        #include "solution.h"

        #include <string>
        #include <iostream>
        */
        /*
        //Comment it before submitting
        struct Node {
            std::string value;
            Node* next;
            Node(const std::string& value_, Node* next_)
                :value(value_), next(next_) {
            }
        };
        */
        /* //remove comment quote before sending
        void solution(Node * head) {
            Node* tmp = head;
            while (tmp != nullptr) {
                std::cout << tmp->value << '\n';
                tmp = tmp->next;
            }
        }

        */
    }
    /*-------------------------------------------------------------------------*/
    void С_LeastFavoriteThing() {
        /* //remove comment quote before sending Send for checking only as file in Y.Contest
        #include "solution.h"

        #include <string>
        #include <iostream>
        */
        /*
        //Comment it before submitting
        struct Node {
            std::string value;
            Node* next;
            Node(const std::string& value_, Node* next_)
                :value(value_), next(next_) {
            }
        };
        */
        /* //remove comment quote before sending
        Node* solution(Node * head, int idx) {
            Node* tmp = head;
            if (idx == 0) {
                return head->next;
            }

            while (idx != 1) {
                tmp = tmp->next;
                --idx;
            }

            tmp->next = tmp->next->next;
            return head;
        }

        void remove_test() {
            Node node3("node3", nullptr);
            Node node2("node2", &node3);
            Node node1("node1", &node2);
            Node node0("node0", &node1);
            Node* new_head = solution(&node0, 3);

            Node* tmp = new_head;
            while (tmp != nullptr) {
                std::cout << tmp->value << '\n';
                tmp = tmp->next;
            }
            // result is : node0 -> node2 -> node3
        }
        */
    }
    /*-------------------------------------------------------------------------*/
    void D_CaringMother() {
        /* //remove comment quote before sending Send for checking only as file in Y.Contest
        #include "solution.h"

        #include <string>
        #include <iostream>
        */
        /*
        //Comment it before submitting
        struct Node {
            std::string value;
            Node* next;
            Node(const std::string& value_, Node* next_)
                :value(value_), next(next_) {
            }
        };
        */
        /* //remove comment quote before sending
        int solution(Node* head, const std::string& elem) {
            int idx = 0;
            Node* tmp = head;
            while (tmp->value != elem) {        
                tmp = tmp->next;
                if (tmp == nullptr) {
                    idx = -1;
                    break;
                }
                ++idx;
        
            }
            return idx;
        }

        void seek_test() {
            Node node3("node3", nullptr);
            Node node2("node2", &node3);
            Node node1("node1", &node2);
            Node node0("node0", &node1);
            int idx = solution(&node0, "node4");
            // result is : idx == 2
            std::cout << idx;
        }

        */
    }
    /*-------------------------------------------------------------------------*/    
    void E_EverythingOppsite() {
        /* //remove comment quote before sending Send for checking only as file in Y.Contest
        #include "solution.h"

        #include <string>
        #include <iostream>
        */
        
        /*
        // Comment it before submitting
        // Bidirectional list
        struct Node {
            Node(const std::string &value, Node* next, Node* prev)
                : value(value)
                , next(next)
                , prev(prev)
                {}
            std::string value;
            Node* next;
            Node* prev;
        };
        */
        /* //remove comment quote before sending
        Node* solution(Node * head) {
            Node* tmp = head;

            while (tmp != nullptr) {
                Node* tmp_ptr = tmp->next;
                tmp->next = tmp->prev;
                tmp->prev = tmp_ptr;
                if (tmp_ptr == nullptr) {
                    break;
                }
                tmp = tmp_ptr;
            }

            return tmp;
        }

        void opposite_head_return_test() {
            Node node3("node3", nullptr, nullptr);
            Node node2("node2", nullptr, nullptr);
            Node node1("node1", nullptr, nullptr);
            Node node0("node0", nullptr, nullptr);
            node0.next = &node1;

            node1.next = &node2;
            node1.prev = &node0;

            node2.next = &node3;
            node2.prev = &node1;

            node3.prev = &node2;
            Node* new_head = solution(&node0);

            Node* tmp = new_head;
            while (tmp != nullptr) {
                std::cout << "Value: " << tmp->value << " Prev: " << ((tmp->prev != nullptr) ? tmp->prev->value : "error") << " Next: " << ((tmp->next != nullptr) ? tmp->next->value : "error") << '\n';
                tmp = tmp->next;
            }


            // result is : new_head == node3
            // node3->next == node2
            // node2->next == node1
            // node2->prev == node3
            // node1->next == node0
            // node1->prev == node2
            // node0->prev == node1
        }
        */
    }
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

    void F_StackMax(std::istream& input, std::ostream& output) {
        int req_num;
        input >> req_num;
        StackMax stack;
        
        while (req_num != 0) {
            std::string req;
            input >> req;
            if (req == "get_max"s) {
                output << stack.GetMax() << '\n';
            }
            else if (req == "push"s) {
                int num;
                input >> num;
                stack.Push(num);
            }
            else if (req == "pop"s) {                                 
                if (!stack.Pop()) {
                    output << "error"s << '\n';
                    
                }
            }
            --req_num;
        }
    }
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

    void G_StackMaxEffective(std::istream& input, std::ostream& output) {
        int req_num;
        input >> req_num;
        StackMaxEffective stack;

        while (req_num != 0) {
            std::string req;
            input >> req;
            if (req == "get_max"s) {
                output << stack.GetMax() << '\n';
            }
            else if (req == "push"s) {
                int num;
                input >> num;
                stack.Push(num);
            }
            else if (req == "pop"s) {
                if (!stack.Pop()) {
                    output << "error"s << '\n';
                }
            }
            --req_num;
        }
    }
}

namespace s2_tests {
	using namespace std::literals;

	/*-------------------------------------------------------------------------*/
    void F_StackMax() {
        {                        
            std::stringstream input;
            input << "8"s << '\n'
                << "get_max"s << '\n'
                << "push 7"s << '\n'
                << "pop"s << '\n'
                << "push -2"s << '\n'
                << "push -1"s << '\n'
                << "pop"s << '\n'
                << "get_max"s << '\n'
                << "get_max"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::F_StackMax(static_cast<std::iostream&>(input), output);   
            std::stringstream res;
            res << "None"s << '\n'
                << "-2"s << '\n'
                << "-2"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "7"s << '\n'
                << "get_max"s << '\n'
                << "pop"s << '\n'
                << "pop"s << '\n'
                << "pop"s << '\n'
                << "push 10"s << '\n'
                << "get_max"s << '\n'                
                << "push -9"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::F_StackMax(input, output);  
            std::stringstream res;
            res << "None"s << '\n'
                << "error"s << '\n'
                << "error"s << '\n'
                << "error"s << '\n'
                << "10"s << '\n';
            assert(output.str() == res.str());
        }
    }
    /*-------------------------------------------------------------------------*/
    void G_StackMaxEffective() {
        {
            std::stringstream input;
            input << "10"s << '\n'
                << "pop"s << '\n'                
                << "pop"s << '\n'
                << "push 4"s << '\n'
                << "push -5"s << '\n'
                << "push 7"s << '\n'
                << "pop"s << '\n'
                << "pop"s << '\n'
                << "get_max"s << '\n'
                << "pop"s << '\n'
                << "get_max"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::G_StackMaxEffective(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "error"s << '\n'
                << "error"s << '\n'
                << "4"s << '\n'
                << "None"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "10"s << '\n'
                << "get_max"s << '\n'
                << "push -6"s << '\n'
                << "pop"s << '\n'
                << "pop"s << '\n'
                << "get_max"s << '\n'
                << "push 2"s << '\n'
                << "get_max"s << '\n'   
                << "pop"s << '\n'
                << "push -2"s << '\n'
                << "push -6"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::G_StackMaxEffective(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "None"s << '\n'
                << "error"s << '\n'
                << "None"s << '\n'
                << "2"s << '\n';
            assert(output.str() == res.str());
        }
    }
}
