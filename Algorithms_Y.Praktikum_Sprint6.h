#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
#include <cassert>
#include <unordered_map>

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

	matrix GetAdjacencyList(int n, std::vector<Edge>& input, bool oriented = false) { // not oriented
		matrix adj_list(n);
		for (Edge elem : input) {
			adj_list[elem.from - 1].push_back(elem.to);
			if (!oriented) {
				adj_list[elem.to - 1].push_back(elem.from);
			}
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
	/*-------------------------------------------------------------------------*/
	std::queue<int> D_BFS(const matrix& adj_list, int idx) {
		std::vector<char> color(adj_list.size(), 'w'); // white, black, grey	
		std::queue<int> planned;
		std::queue<int> res;
		planned.push(idx);
		color[idx] = 'g';
		while (planned.size() > 0) {
			int u = planned.front();
			planned.pop();

			for (int i = 0; i < adj_list[u].size(); ++i) {
				if (color[adj_list[u][i] - 1] == 'w') {
					color[adj_list[u][i] - 1] = 'g';
					planned.push(adj_list[u][i] - 1);
				}
			}
			color[u] = 'b';
			res.push(u + 1); // fill return
		}
		return res;
	}

	std::queue<int> D_MainBFS(const matrix& adj_list, int idx) {
		return D_BFS(adj_list, idx - 1);
	}


	void D_BFS(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in));
		int start_idx;
		input >> start_idx;

		std::queue<int> res(D_MainBFS(adj_list, start_idx));

		bool f = false;
		while (res.size() > 0) {
			if (f) {
				output << ' ';
			}
			else {
				f = true;
			}
			output << res.front();
			res.pop();
		}
		output << '\n';
	}

	void E_DFS(const matrix& adj_list, std::vector<int>& vert_color, int idx, int& component_count) {
		std::stack<int> stack;
		stack.push(idx);

		while (stack.size() != 0) {
			int v = stack.top();
			stack.pop();
			if (vert_color[v] == -1) {
				vert_color[v] = 0;
				stack.push(v);
				for (int i = 0; i < adj_list[v].size(); ++i) {
					if (vert_color[adj_list[v][i] - 1] == -1) {
						stack.push(adj_list[v][i] - 1);
					}
				}
			}
			else if (vert_color[v] == 0) {
				vert_color[v] = component_count;
			}
		}
		++component_count;
	}

	int E_MainDFS(const matrix& adj_list, std::vector<int>& vert_color) {
		int component_count = 1;
		for (int i = 0; i < adj_list.size(); ++i) {
			if (vert_color[i] == -1) {
				E_DFS(adj_list, vert_color, i, component_count);
			}
		}

		return component_count - 1;
	}

	void E_ConnectivityComponents(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in));

		std::vector<int> vert_color(n, -1); // white, black, grey				
		int component_count = E_MainDFS(adj_list, vert_color);

		std::vector<std::vector<int>> res(component_count);

		for (int i = 0; i < vert_color.size(); ++i) {
			res[vert_color[i] - 1].push_back(i + 1);
		}

		output << component_count << '\n';
		for (int i = 0; i < res.size(); ++i) {
			output << res[i];
		}

	}
	/*-------------------------------------------------------------------------*/
	int G_BFS(const matrix& adj_list, int idx) {
		std::vector<char> color(adj_list.size(), 'w'); // white, black, grey	
		std::queue<int> planned;
		std::vector<int> distance(adj_list.size(), 0);
		int max_dist = 0;
		planned.push(idx);
		color[idx] = 'g';
		while (planned.size() > 0) {
			int u = planned.front();
			planned.pop();

			for (int i = 0; i < adj_list[u].size(); ++i) {
				int v = adj_list[u][i] - 1;
				if (color[v] == 'w') {
					color[v] = 'g';
					planned.push(v);
					distance[v] = distance[u] + 1;
					if (distance[v] > max_dist) {
						max_dist = distance[v];
					}
				}
			}
			color[u] = 'b';

		}
		return max_dist;
	}

	int G_MainBFS(const matrix& adj_list, int idx) {
		return G_BFS(adj_list, idx - 1);
	}

	void G_MaxDist(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in));
		int start_idx;
		input >> start_idx;

		output << G_MainBFS(adj_list, start_idx) << '\n';
	}
	/*-------------------------------------------------------------------------*/
	struct Time {
		int entry = -1;
		int leave = -1;
	};

	std::ostream& operator << (std::ostream& out, Time& time) {
		out << time.entry << ' ' << time.leave << '\n';
		return out;
	}

	// recursion way
	void H_DFSRec(const matrix& adj_list, std::vector<char>& vert_color, std::vector<Time>& vert_visit_time, int& time, int vert_idx, std::vector<int>& res) {
		vert_visit_time[vert_idx].entry = time;
		time++;
		vert_color[vert_idx] = 'g';
		res.push_back(vert_idx + 1);
		for (int i = 0; i < adj_list[vert_idx].size(); ++i) {
			if (vert_color[adj_list[vert_idx][i] - 1] == 'w') {
				H_DFSRec(adj_list, vert_color, vert_visit_time, time, adj_list[vert_idx][i] - 1, res);
			}
		}
		vert_color[vert_idx] = 'b';
		vert_visit_time[vert_idx].leave = time;
		time++;
	}

	void H_DFS(const matrix& adj_list, std::vector<char>& vert_color, std::vector<Time>& vert_visit_time, int& time, int vert_idx, std::vector<int>& res) {
		std::stack<int> stack;
		stack.push(vert_idx);
		while (!stack.empty()) {
			int v = stack.top();
			stack.pop();
			if (vert_color[v] == 'w') {
				vert_visit_time[v].entry = time;
				++time;
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
				vert_visit_time[v].leave = time;
				++time;
				vert_color[v] = 'b';
			}
		}
	}

	void H_MainDFS(const matrix& adj_list, std::vector<char>& vert_color, std::vector<Time>& vert_visit_time, int start_idx, std::vector<int>& res) {
		int time = 0;
		H_DFS(adj_list, vert_color, vert_visit_time, time, start_idx - 1, res); // cycle
		//H_DFSRec(adj_list, vert_color, vert_visit_time, time, start_idx - 1, res); // recursion
	}

	void H_TimeToExit(std::istream& input, std::ostream& output) {
		int n, start;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in, true));

		std::vector<char> vert_color(n, 'w'); // white, black, grey
		std::vector<Time> vert_visit_time(n);

		std::vector<int> res;
		H_MainDFS(adj_list, vert_color, vert_visit_time, 1, res);


		for (Time time : vert_visit_time) {
			output << time;
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_DFS(const matrix& adj_list, std::vector<char>& vert_color, int vert_idx, std::stack<int>& res) {
		std::stack<int> stack;
		stack.push(vert_idx);
		while (!stack.empty()) {
			int v = stack.top();
			stack.pop();
			if (vert_color[v] == 'w') {
				vert_color[v] = 'g';
				stack.push(v);
				for (int i = 0; i < adj_list[v].size(); ++i) {
					if (vert_color[adj_list[v][i] - 1] == 'w') {
						stack.push(adj_list[v][i] - 1);
					}
				}
			}
			else if (vert_color[v] == 'g') {
				res.push(v + 1);
				vert_color[v] = 'b';
			}
		}
	}

	void J_MainDFS(const matrix& adj_list, std::vector<char>& vert_color, std::stack<int>& res) {
		for (int i = vert_color.size() - 1; i >= 0; --i) {
			if (vert_color[i] == 'w') {
				J_DFS(adj_list, vert_color, i, res); // cycle
			}
		}
	}

	void J_TopologySort(std::istream& input, std::ostream& output) {
		int n;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n;
		std::vector<Edge> in(FillEdgesList(input));
		matrix adj_list(GetAdjacencyList(n, in, true));

		std::vector<char> vert_color(n, 'w'); // white, black, grey		
		std::stack<int> res;
		J_MainDFS(adj_list, vert_color, res);

		bool f = false;
		while (res.size() > 0) {
			if (f) {
				output << ' ';
			}
			else {
				f = true;
			}
			output << res.top();
			res.pop();
		}
		output << '\n';
	}
	/*-------------------------------------------------------------------------*/
	class Graph {
	public:
		Graph(int n, bool oriented = false)
			:adj_list_(std::vector<std::vector<int>>(n)), oriented_(oriented)
		{
		}

		void AddEdge(int from, int to, int weight) {
			if (edges_.count({ from, to }) || edges_.count({ to, from })) {
				return;
			}
			adj_list_[from].push_back(to);
			edges_[{from, to}] = weight;
			if (!oriented_) {
				adj_list_[to].push_back(from);
				edges_[{to, from}] = weight;
			}
		}

		void SortAdjLists() {
			for (int i = 0; i < adj_list_.size(); ++i) {
				std::sort(adj_list_[i].begin(), adj_list_[i].end());
			}
		}

		const std::vector<int>& operator[](int idx) const {
			return adj_list_[idx];
		}

		int operator[](Edge edge) const {
			return edges_.at(edge);
		}

	private:
		struct Edge {
			Edge(int from, int to) {
				start = from;
				end = to;
			}
			Edge(s6_problems::Edge other) {
				start = other.from;
				end = other.to;
			}

			bool operator==(const Edge& other) const {
				return start == other.start && end == other.end;
			}

			int start = -1;
			int end = -1;
		};

		struct EdgeHasher {
			size_t operator() (const Edge& edge) const {
				return int_hash(edge.start) + 37 * int_hash(edge.end);
			}
			std::hash<int> int_hash;
		};

		bool oriented_ = false;
		std::unordered_map<Edge, int, EdgeHasher> edges_{};
		std::vector<std::vector<int>> adj_list_{};
	};

	void UpdMinNeighbDist(const Graph& graph, std::vector<int>& dist, std::vector<int>& prev, int idx) {
		for (int i = 0; i < graph[idx].size(); ++i) {
			dist[graph[idx][i]] = dist[idx] + graph[{idx, graph[idx][i]}];
			prev[graph[idx][i]] = idx;
		}
	}

	int GetMinDistNotVisited(std::vector<bool>& visited, std::vector<int>& dist) {
		int cur_min = INT32_MAX;
		int cur_min_idx = -1;
		for (int i = 1; i < visited.size(); ++i) {
			if (!visited[i] && dist[i] < cur_min) {
				cur_min = dist[i];
				cur_min_idx = i;
			}
		}
		return cur_min_idx;
	}

	void Relax(std::vector<int>& dist, std::vector<int>& prev, int u, int v, int weight) {
		if (dist[v] > dist[u] + weight) {
			dist[v] = dist[u] + weight;
			prev[v] = u;
		}
	}

	std::vector<int> Dijkstra(const Graph& graph, int idx, int n) {
		std::vector<bool> visited(n + 1, 0);
		std::vector<int> dist(n + 1, INT32_MAX);
		std::vector<int> prev(n + 1, -1);

		dist[idx] = 0;
		UpdMinNeighbDist(graph, dist, prev, idx);
		while (true) {
			int u = GetMinDistNotVisited(visited, dist);

			if (u == -1) {
				break;
			}

			visited[u] = true;
			for (int i = 0; i < graph[u].size(); ++i) {
				int v = graph[u][i];
				Relax(dist, prev, u, v, graph[{u, v}]);
			}
		}
		for (int i = 0; i < dist.size(); ++i) {
			if (dist[i] == INT32_MAX) {
				dist[i] = -1;
			}
		}
		return dist;
	}

	void K_Sightseeings(std::istream& input, std::ostream& output) {
		int n, m;  // n - count of vertecies (1 <= n <= 100'000)
		input >> n >> m;
		Graph graph(n + 1);
		for (int i = 0; i < m; ++i) {
			int f, t, w;
			input >> f >> t >> w;
			graph.AddEdge(f, t, w);
		}
		graph.SortAdjLists();

		std::vector<std::vector<int>> res(n + 1, std::vector<int>(n + 1));

		for (int i = 1; i <= n; ++i) {
			res[i] = Dijkstra(graph, i, n);
		}

		for (int i = 1; i < res.size(); ++i) {
			bool f = false;
			for (int j = 1; j < res[i].size(); ++j) {
				if (f) {
					output << ' ';
				}
				else {
					f = true;
				}
				output << res[i][j];
			}
			output << '\n';
		}
	}
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
	/*-------------------------------------------------------------------------*/
	void D_BFS() {
		{
			std::stringstream input;
			input << "4 4"s << '\n'
				<< "1 2"s << '\n'
				<< "2 3"s << '\n'
				<< "3 4"s << '\n'
				<< "1 4"s << '\n'
				<< "3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::D_BFS(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3 2 4 1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 1"s << '\n'
				<< "2 1"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::D_BFS(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2"s << '\n';
			assert(output.str() == res.str());
		}
	}

	/*-------------------------------------------------------------------------*/
	void E_ConnectivityComponents() {
		{
			std::stringstream input;
			input << "6 3"s << '\n'
				<< "1 2"s << '\n'
				<< "6 5"s << '\n'
				<< "2 3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::E_ConnectivityComponents(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n'
				<< "1 2 3"s << '\n'
				<< "4"s << '\n'
				<< "5 6"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 0"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::E_ConnectivityComponents(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2"s << '\n'
				<< "1"s << '\n'
				<< "2"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4 3"s << '\n'
				<< "2 3"s << '\n'
				<< "2 1"s << '\n'
				<< "4 3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::E_ConnectivityComponents(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n'
				<< "1 2 3 4"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void G_MaxDist() {
		{
			std::stringstream input;
			input << "5 4"s << '\n'
				<< "2 1"s << '\n'
				<< "4 5"s << '\n'
				<< "4 3"s << '\n'
				<< "3 2"s << '\n'
				<< "2"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::G_MaxDist(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 3"s << '\n'
				<< "3 1"s << '\n'
				<< "1 2"s << '\n'
				<< "2 3"s << '\n'
				<< "1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::G_MaxDist(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6 8"s << '\n'
				<< "6 1"s << '\n'
				<< "1 3"s << '\n'
				<< "5 1"s << '\n'
				<< "3 5"s << '\n'
				<< "3 4"s << '\n'
				<< "6 5"s << '\n'
				<< "5 2"s << '\n'
				<< "6 2"s << '\n'
				<< "4"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::G_MaxDist(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n';
			assert(output.str() == res.str());
		}

	}
	/*-------------------------------------------------------------------------*/
	void H_TimeToExit() {
		{
			std::stringstream input;
			input << "6 8"s << '\n'
				<< "2 6"s << '\n'
				<< "1 6"s << '\n'
				<< "3 1"s << '\n'
				<< "2 5"s << '\n'
				<< "4 3"s << '\n'
				<< "3 2"s << '\n'
				<< "1 2"s << '\n'
				<< "1 4"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::H_TimeToExit(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 11"s << '\n'
				<< "1 6"s << '\n'
				<< "8 9"s << '\n'
				<< "7 10"s << '\n'
				<< "2 3"s << '\n'
				<< "4 5"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 2"s << '\n'
				<< "1 2"s << '\n'
				<< "2 3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::H_TimeToExit(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 5"s << '\n'
				<< "1 4"s << '\n'
				<< "2 3"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void J_TopologySort() {
		{
			std::stringstream input;
			input << "5 3"s << '\n'
				<< "3 2"s << '\n'
				<< "3 4"s << '\n'
				<< "2 5"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::J_TopologySort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 3 2 4 5"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6 3"s << '\n'
				<< "6 4"s << '\n'
				<< "4 1"s << '\n'
				<< "5 1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::J_TopologySort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "2 3 5 6 4 1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4 0"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::J_TopologySort(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2 3 4"s << '\n';
			assert(output.str() == res.str());
		}
	}
	/*-------------------------------------------------------------------------*/
	void K_Sightseeings() {
		{
			std::stringstream input;
			input << "4 4"s << '\n'
				<< "1 2 1"s << '\n'
				<< "2 3 3"s << '\n'
				<< "3 4 5"s << '\n'
				<< "1 4 2"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::K_Sightseeings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1 4 2"s << '\n'
				<< "1 0 3 3"s << '\n'
				<< "4 3 0 5"s << '\n'
				<< "2 3 5 0"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 2"s << '\n'
				<< "1 2 1"s << '\n'
				<< "1 2 2"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::K_Sightseeings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 1 -1"s << '\n'
				<< "1 0 -1"s << '\n'
				<< "-1 -1 0"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "2 0"s;
			std::ostringstream output(std::ios_base::ate);
			s6_problems::K_Sightseeings(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "0 -1"s << '\n'
				<< "-1 0"s << '\n';
			assert(output.str() == res.str());
		}
	}
}