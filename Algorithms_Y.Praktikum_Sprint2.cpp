#include "Algorithms_Y.Praktikum_Sprint2.h"

namespace s2_problems {
    using namespace std::literals;

    std::vector<std::vector<int>> FillMatrix(std::istream& input) {
        int cols, rows;
        input >> rows >> cols;

        if (cols == 0 && rows == 0) {
            return { {} };
        }

        std::vector<std::vector<int>> matrix(rows);
        int i = 0;
        while (i < rows) {
            int j = 0;
            while (j < cols) {
                int num;
                input >> num;
                matrix[i].push_back(num);
                ++j;
            }
            ++i;
        }

        return matrix;
    }

    std::vector<std::vector<int>> TransposeMatrix(const std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> transposed_matrix(matrix[0].size());
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                transposed_matrix[j].push_back(matrix[i][j]);
            }
        }

        return transposed_matrix;
    }
    
    void A_Monitoring(std::istream& input, std::ostream& output) {
        std::vector<std::vector<int>> matrix = std::move(FillMatrix(input));
        if (matrix.size() == 0) {
            return;
        }
        std::vector<std::vector<int>> transposed_matrix = std::move(TransposeMatrix(matrix));

        output << transposed_matrix;
    }
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
    void H_BracketSequence(std::istream& input, std::ostream& output) {
        std::string str;
        input >> str;

        std::stack<char> stack;

        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
                stack.push(str[i]);
            }
            else if (!stack.empty() && (str[i] == stack.top() + 2 || str[i] == stack.top() + 1)) {
                stack.pop();
            }
            else {
                output << "False"s;
                return;
            }
        }
        if (stack.empty()) {
            output << "True"s;
        }
        else {
            output << "False"s;
        }
    }
    /*-------------------------------------------------------------------------*/
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
    /*-------------------------------------------------------------------------*/
    void I_LimitedQueue(std::istream& input, std::ostream& output) {
        int req_num;
        input >> req_num;

        int queue_size;
        input >> queue_size;

        MyQueueSized queue(queue_size);

        while (req_num != 0) {
            std::string req;
            input >> req;
            if (req == "push"s) {
                int num;
                input >> num;
                if (!queue.Push(num)) {
                    output << "error"s << '\n';
                }
            }
            else if (req == "pop"s) {
                output << queue.Pop() << '\n';
            }
            else if (req == "peek"s) {
                output << queue.Peek() << '\n';
            }
            else if (req == "size"s) {
                output << queue.Size() << '\n';
            }
            --req_num;
        }
    }
    /*-------------------------------------------------------------------------*/
    void J_ListedQueue(std::istream& input, std::ostream& output) {
        int req_num;
        input >> req_num;

        MyQueueOnList queue;

        while (req_num != 0) {
            std::string req;
            input >> req;
            if (req == "get"s) {
                std::optional<int> tmp = queue.Get();
                if (!tmp) {
                    output << "error"s << '\n';
                }
                else {
                    output << tmp.value() << '\n';
                }
            }
            else if (req == "put"s) {
                int num;
                input >> num;

                queue.Put(num);
            }
            else if (req == "size"s) {
                output << queue.Size() << '\n';
            }
            --req_num;
        }
    }
    /*-------------------------------------------------------------------------*/
    int RecFibo(int n) {
        if (n == 1 || n == 0) {
            return 1;
        }
        return RecFibo(n - 1) + RecFibo(n - 2);
    }

    void K_RecursionFibonacci(std::istream& input, std::ostream& output) {
        int num;
        input >> num;
        int res = RecFibo(num);
        output << res;
    }
    /*-------------------------------------------------------------------------*/
    int RecFiboAbs(int n, int k) {
        int next, first, second;
        if (n == 0 || n == 1) {
            return 1;
        }
        next = 0;
        first = 1;
        second = 1;
        while (n > 1) {
            next = (first + second) % static_cast<int>(std::pow(10, k));
            first = second;
            second = next;
            --n;
        }

        return next;
    }

    void L_RecursionFibonacciAbs(std::istream& input, std::ostream& output) {
        int num;
        size_t k;
        input >> num >> k;
        int res = RecFiboAbs(num, k);
        std::string res_str = std::to_string(res);

        if (k < res_str.size()) {
            output << res_str.substr(res_str.size() - k);
        }
        else {
            output << res_str;
        }
    }
}

namespace s2_tests {
    using namespace std::literals;

    void A_Monitoring() {
        {
            std::stringstream input;
            input << "4"s << '\n'
                << "3"s << '\n'
                << "1 2 3"s << '\n'
                << "0 2 6"s << '\n'
                << "7 4 1"s << '\n'
                << "2 7 0"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::A_Monitoring(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "1 0 7 2"s << '\n'
                << "2 2 4 7"s << '\n'
                << "3 6 1 0"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "9"s << '\n'
                << "5"s << '\n'
                << "-7 -1 0 -4 -9"s << '\n'
                << "5 -1 2 2 9"s << '\n'
                << "3 1 -8 -1 -7"s << '\n'
                << "9 0 8 -8 -1"s << '\n'
                << "2 4 5 2 8"s << '\n'
                << "-7 10 0 -4 -8"s << '\n'
                << "-3 10 -7 10 3"s << '\n'
                << "1 6 -7 -5 9"s << '\n'
                << "-1 9 9 1 9"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::A_Monitoring(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "-7 5 3 9 2 -7 -3 1 -1"s << '\n'
                << "-1 -1 1 0 4 10 10 6 9"s << '\n'
                << "0 2 -8 8 5 0 -7 -7 9"s << '\n'
                << "-4 2 -1 -8 2 -4 10 -5 1"s << '\n'
                << "-9 9 -7 -1 8 -8 3 9 9"s << '\n';
            assert(output.str() == res.str());
        }
    }
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
    /*-------------------------------------------------------------------------*/
    void H_BracketSequence() {
        {
            std::istringstream input("{[()]}"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "True"s);
        }
        {
            std::istringstream input("()"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "True"s);
        }
        {
            std::istringstream input(")("s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "False"s);
        }
        {
            std::istringstream input("()()"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "True"s);
        }
        {
            std::istringstream input("({()()})"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "True"s);
        }
        {
            std::istringstream input("({()(}))"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "False"s);
        }
        {
            std::istringstream input("({}()(])[)"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::H_BracketSequence(input, output);
            assert(output.str() == "False"s);
        }
    }
    /*-------------------------------------------------------------------------*/
    void I_LimitedQueue() {
        {
            s2_problems::MyQueueSized queue(4);
            assert(queue.Peek() == "None"s);
            assert(queue.Pop() == "None"s);
            assert(queue.Push(1));
            assert(queue.Push(2));
            assert(queue.Push(3));
            assert(queue.Push(4));
            assert(!queue.Push(5));
            assert(queue.Size() == 4);
            assert(queue.Peek() == "1"s);
            assert(queue.Pop() == "1"s);
            assert(queue.Size() == 3);
            assert(queue.Peek() == "2"s);
            assert(queue.Pop() == "2"s);
            assert(queue.Size() == 2);
            assert(queue.Peek() == "3"s);
            assert(queue.Pop() == "3"s);
            assert(queue.Size() == 1);
            assert(queue.Peek() == "4"s);
            assert(queue.Pop() == "4"s);
            assert(queue.Size() == 0);

            assert(queue.Push(6));
            assert(queue.Push(7));
            assert(queue.Peek() == "6"s);
            assert(queue.Peek() != "7"s);
            assert(queue.Pop() == "6"s);
            assert(queue.Push(8));
            assert(queue.Peek() == "7"s);
            assert(queue.Size() == 2);
            assert(queue.Pop() == "7"s);
            assert(queue.Pop() == "8"s);
            assert(queue.Size() == 0);
        }
        {
            std::stringstream input;
            input << "8"s << '\n'
                << "2"s << '\n'
                << "peek"s << '\n'
                << "push 5"s << '\n'
                << "push 2"s << '\n'
                << "peek"s << '\n'
                << "size"s << '\n'
                << "size"s << '\n'
                << "push 1"s << '\n'
                << "size"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::I_LimitedQueue(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "None"s << '\n'
                << "5"s << '\n'
                << "2"s << '\n'
                << "2"s << '\n'
                << "error"s << '\n'
                << "2"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "10"s << '\n'
                << "1"s << '\n'
                << "push 1"s << '\n'
                << "size"s << '\n'
                << "push 3"s << '\n'
                << "size"s << '\n'
                << "push 1"s << '\n'
                << "pop"s << '\n'
                << "push 1"s << '\n'
                << "pop"s << '\n'
                << "push 3"s << '\n'
                << "push 3"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::I_LimitedQueue(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "1"s << '\n'
                << "error"s << '\n'
                << "1"s << '\n'
                << "error"s << '\n'
                << "1"s << '\n'
                << "1"s << '\n'
                << "error"s << '\n';
            assert(output.str() == res.str());
        }
    }
    /*-------------------------------------------------------------------------*/
    void J_ListedQueue() {
        {
            std::stringstream input;
            input << "10"s << '\n'
                << "put -34"s << '\n'
                << "put -23"s << '\n'
                << "get"s << '\n'
                << "size"s << '\n'
                << "get"s << '\n'
                << "size"s << '\n'
                << "get"s << '\n'
                << "get"s << '\n'
                << "put 80"s << '\n'
                << "size"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::J_ListedQueue(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "-34"s << '\n'
                << "1"s << '\n'
                << "-23"s << '\n'
                << "0"s << '\n'
                << "error"s << '\n'
                << "error"s << '\n'
                << "1"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "6"s << '\n'
                << "put -66"s << '\n'
                << "put 98"s << '\n'
                << "size"s << '\n'
                << "size"s << '\n'
                << "get"s << '\n'
                << "get"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::J_ListedQueue(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "2"s << '\n'
                << "2"s << '\n'
                << "-66"s << '\n'
                << "98"s << '\n';
            assert(output.str() == res.str());
        }
        {
            std::stringstream input;
            input << "9"s << '\n'
                << "get"s << '\n'
                << "size"s << '\n'
                << "put 74"s << '\n'
                << "get"s << '\n'
                << "size"s << '\n'
                << "put 90"s << '\n'
                << "size"s << '\n'
                << "size"s << '\n'
                << "size"s;
            std::ostringstream output(std::ios_base::ate);
            s2_problems::J_ListedQueue(static_cast<std::iostream&>(input), output);
            std::stringstream res;
            res << "error"s << '\n'
                << "0"s << '\n'
                << "74"s << '\n'
                << "0"s << '\n'
                << "1"s << '\n'
                << "1"s << '\n'
                << "1"s << '\n';
            assert(output.str() == res.str());
        }
    }
    /*-------------------------------------------------------------------------*/
    void K_RecursionFibonacci() {
        {
            std::istringstream input("3"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::K_RecursionFibonacci(input, output);
            assert(output.str() == "3"s);
        }
        {
            std::istringstream input("0"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::K_RecursionFibonacci(input, output);
            assert(output.str() == "1"s);
        }
        {
            std::istringstream input("6"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::K_RecursionFibonacci(input, output);
            assert(output.str() == "13"s);
        }
        {
            std::istringstream input("21"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::K_RecursionFibonacci(input, output);
            assert(output.str() == "17711"s);
        }
    }
    /*-------------------------------------------------------------------------*/
    void L_RecursionFibonacciAbs() {
        {
            std::istringstream input("3 1"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::L_RecursionFibonacciAbs(input, output);
            assert(output.str() == "3"s);
        }
        {
            std::istringstream input("10 1"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::L_RecursionFibonacciAbs(input, output);
            assert(output.str() == "9"s);
        }
        {
            std::istringstream input("98 4"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::L_RecursionFibonacciAbs(input, output);
            assert(output.str() == "9026"s);
        }
        {
            std::istringstream input("1000000 8"s);
            std::ostringstream output(std::ios_base::ate);
            s2_problems::L_RecursionFibonacciAbs(input, output);
            assert(output.str() == "26937501"s);
        }
    }
}