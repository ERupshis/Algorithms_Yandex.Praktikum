#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

namespace s6_problems {
	using namespace std::literals;

	struct Edge {
		int from = -1;
		int to = -1;
	};

	std::vector<Edge> FillEdgesList(std::istream& input) { 
		int m; // m - count of edges
		input >> m;

		std::vector<Edge> res;
		res.reserve(m);
		for (int i = 0; i < m; ++i) {
			int f, t;
			input >> f >> t;
			res.push_back({ f, t });
		}

		return res;
	}

	void A_BuildAdjacencyList(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n 
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));

		std::vector<std::vector<int>> adj_list(n);
		for (Edge elem : in) {
			adj_list[elem.from - 1].push_back(elem.to);
		}

		for (std::vector<int>& vert_list : adj_list) {
			std::sort(vert_list.begin(), vert_list.end());
			output << vert_list.size();
			for (int elem : vert_list) {
				output << ' ' << elem;
			}
			output << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_ConvertEdgesListToAdjacencyMatrix(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n <= 100)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));

		std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n));
		for (Edge elem : in) {
			adj_matrix[elem.from - 1][elem.to - 1] = 1;
		}

		for (std::vector<int>& vert_coord : adj_matrix) {
			bool f = false;
			for (int elem : vert_coord) {
				if (f) {
					output << ' ';
				}
				else {
					f = true;
				}
				output << elem;
			}
			output << '\n';
		}
	}
	/*-------------------------------------------------------------------------*/
	using matrix = std::vector<std::vector<int>>;

	std::ostream& operator<< (std::ostream& out, std::vector<int> vec) {
		bool f = false;
		for (int elem : vec) {
			if (f) {
				out << ' ';
			}
			else {
				f = true;
			}
			out << elem;
		}
		out << '\n';
		return out;
	}

	matrix GetAdjacencyList(int n, std::vector<Edge>& input) { // not oriented
		matrix adj_list(n);				
		for (Edge elem : input) {
			adj_list[elem.from - 1].push_back(elem.to);
			adj_list[elem.to - 1].push_back(elem.from);
		}

		for (std::vector<int>& vert_list : adj_list) {
			std::sort(vert_list.begin(), vert_list.end());			
		}
		return adj_list;
	}

	/*
	// recursion way
	void DFS(const matrix& adj_list, std::vector<char>& vert_color, int vert_idx, std::vector<int>& res) {
		vert_color[vert_idx] = 'g';
		res.push_back(vert_idx + 1);
		for (int i = 0; i < adj_list[vert_idx].size(); ++i) {
			if (vert_color[adj_list[vert_idx][i] - 1] == 'w') {
				DFS(adj_list, vert_color, adj_list[vert_idx][i] - 1, res);
			}
		}
		vert_color[vert_idx] = 'b';
	}
	*/

	//cycle
	void DFS(const matrix& adj_list, std::vector<char>& vert_color, int vert_idx, std::vector<int>& res) {
		std::stack<int> stack;
		stack.push(vert_idx);
		while (!stack.empty()) {
			int v = stack.top();
			stack.pop();
			if (vert_color[v] == 'w') {
				vert_color[v] = 'g';
				res.push_back(v + 1);
				stack.push(v);

				for (int i = adj_list[v].size() - 1; i >= 0; --i) {
					if (vert_color[adj_list[v][i] - 1] == 'w') {
						stack.push(adj_list[v][i] - 1);
					}
				}
			}
			else if (vert_color[v] == 'g') {
				vert_color[v] = 'b';				
			}
		}		
	}

	void MainDFS(const matrix& adj_list, std::vector<char>& vert_color, int start_idx, std::vector<int>& res) {
		DFS(adj_list, vert_color, start_idx - 1, res);
	}

	void C_DFS(std::istream& input, std::ostream& output) {
		int n, start;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in));

		input >> start;
		std::vector<char> vert_color(n, 'w'); // white, black, grey

		std::vector<int> res;
		MainDFS(adj_list, vert_color, start, res);

		output << res;
	}

	// adjacency matrix
	//recursion way
	/*
	matrix GetAdjacencyMatrix(int n, std::vector<Edge>& input) {
		matrix adj_matrix(n, std::vector<int>(n));
		for (Edge elem : input) {
			adj_matrix[elem.from - 1][elem.to - 1] = 1;
			adj_matrix[elem.to - 1][elem.from - 1] = 1;
		}
		return adj_matrix;
	} 
	
	void DFS(const matrix& adj_matrix, std::vector<char>& vert_color, int vert_idx, std::vector<int>& res) {
		vert_color[vert_idx] = 'g';

		res.push_back(vert_idx + 1);
		for (int i = 0; i < adj_matrix[vert_idx].size(); ++i) {
			if (adj_matrix[vert_idx][i] == 1 && vert_color[i] == 'w') {
				DFS(adj_matrix, vert_color, i, res);
			}
		}
		vert_color[vert_idx] = 'b';
	}


	void MainDFS(const matrix& adj_matrix, std::vector<char>& vert_color, int start_idx, std::vector<int>& res) {
		DFS(adj_matrix, vert_color, start_idx - 1, res);		
		//for (int i = 0; i < adj_matrix.size(); ++i) {
		//	if (vert_color[i] == 'w') {
		//		DFS(adj_matrix, vert_color, i, res);
		//	}
		//}
		
	}
	
	void C_DFS(std::istream& input, std::ostream& output) {
		int n, start;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_matrix(GetAdjacencyMatrix(n, in));

		input >> start;
		std::vector<char> vert_color(n, 'w'); // white, black, grey

		std::vector<int> res;

		MainDFS(adj_matrix, vert_color, start, res);

		output << res;
	}
	*/
}


namespace s6_tests {
	using namespace std::literals;
	using namespace s6_problems;

	void A_BuildAdjacencyList() {
		{
			std::stringstream input;
			input << "5 3"s << '\n'
				<< "1 3"s << '\n'
				<< "2 3"s << '\n'
				<< "5 2"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::A_BuildAdjacencyList(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 3"s << '\n'
				<< "1 3"s << '\n'
				<< "0"s << '\n'
				<< "0"s << '\n'
				<< "1 2"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void B_ConvertEdgesListToAdjacencyMatrix() {
		{
			std::stringstream input;
			input << "5 3"s << '\n'
				<< "1 3"s << '\n'
				<< "2 3"s << '\n'
				<< "5 2"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::B_ConvertEdgesListToAdjacencyMatrix(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 0 1 0 0"s << '\n'
				<< "0 0 1 0 0"s << '\n'
				<< "0 0 0 0 0"s << '\n'
				<< "0 0 0 0 0"s << '\n'
				<< "0 1 0 0 0"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void C_DFS() {
		{
			std::stringstream input;
			input << "4 4"s << '\n'
				<< "3 2"s << '\n'
				<< "4 3"s << '\n'
				<< "1 4"s << '\n'
				<< "1 2"s << '\n'
				<< "3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::C_DFS(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 2 1 4"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 1"s << '\n'
				<< "1 2"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::C_DFS(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 1"s << '\n'
				<< "2 3"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::C_DFS(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
	}
}