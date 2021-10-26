#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>



namespace s6_exam_problems {
	using namespace std::literals;

	//SEND ID: 55499294	

	//A_Graph - class that represents a graph. It has methods that finds SpanningTree of graph.
	//Graph should be not oriented and with one adjacency component, otherwise it's not possible to create 
	//spanning tree (return of method will be nullopt)
	//Time complexity:
	//   - constructor() - O(V) where's V is a count of verticies;
	//   - AddEdge() - O(1) - add only one oriented / not oriented vertex in graph
	//   - GetMaxSpinningTree() - O(E * logV), where's V - count of vertices, E - count of edges (actually 2*E).
	//   This method check of vertecies in cycle and find biggest edge and add end-vertex of this edge in span. tree.
	//   This operation repeats while all vertecies will not be added in spanning tree. If some vertices where not added 
	//   in span. tree, than this graph has more than one adjacency component.			
	//	 Search of biggest outcome edges - O(logV),where's V - count of vertecies - thanks to priority queue.
	//	 Adding of vertex's outcome edges - O(E * LogV), where's V - count of vertecies. This method go through all edges that 
	//	 outcome form considering vertex O(E) and add adjacency vertex only it was not added in span tree before (LogV - complexity of priority_queue's 'push') 
	//   
	//Space complexity:
	//   - Graph - O(V) + O(2*E). There's no need to keep adjacency info in matrix because  2E less than V^2
	//   - AddEdge() - O(1) of additional space
	//   - AddVertexInSpanningTree() - O(1) of additional space
	//   - GetMaxSpanningTree() - O(V) + O(V) + O(E) where's V - count of vertices (added + not_added unord_sets), 
	//   V - count of vertices in result span. tree,  E - count of considering edges in priority_queue.
	
	class A_Graph {
	public:
		struct Edge {
			int from = -1;
			int to = -1;
			int weight = -1;

			bool operator < (const Edge& other) const {
				return weight < other.weight;
			}
		};

		struct EdgeHasher {
			size_t operator() (const Edge& edge) const {
				return int_hash(edge.from) + 37 * int_hash(edge.to) + 37 * 37 * int_hash(edge.to);
			}
			std::hash<int> int_hash;
		};
	public:
		explicit A_Graph(int n, bool oriented = false)
			:edges_(n + 1), oriented_(oriented) 
		{
			while (n > 0) { // graph is not oriented by default for task
				vertices_.insert(n); // some vertices may be not be in adjacency components (vertecies without incident edges)
				--n;
			}
		}

		void AddEdge(int from, int to, int weight) {
			if (from != to && (edges_[from].count(to) == 0 //zero edge from == to
				|| edges_[from].at(to) < weight)) { // add new edge if edge is not added or rewrite old if new is bigger
				edges_[from][to] = weight;
				if (!oriented_) {
					edges_[to][from] = weight; //not oriented - we need to add opposite direction graph for easier search
				}
			}			
		}		

		std::optional<int> GetMaxSpanningTreeWeight() const {			
			int res = 0;
			std::unordered_set<int> added; // already added in span
			std::unordered_set<int> not_added(vertices_); // should be added
			std::priority_queue<Edge> edges; // edges that go out from span

			int v = *not_added.begin();
			AddVertexInSpanningTree(added, not_added, edges, v);

			while (not_added.size() > 0 && edges.size() > 0) {
				Edge e = edges.top(); // extract max weighted edge
				edges.pop();

				if (not_added.count(e.to)) { //if end vertex of this edges is not added in spaning tree					
					res += e.weight; //add this edge weight to result
					AddVertexInSpanningTree(added, not_added, edges, e.to); // add end vertex and outcome edges
				}
			}

			if (not_added.size() > 0) { // no edges to some vertices
				return std::nullopt;
			}
			else {
				return res;
			}
		}

	private:		
		bool oriented_ = false;
		std::unordered_set<int> vertices_{};
		std::vector<std::unordered_map<int, int>> edges_;

		void AddVertexInSpanningTree(std::unordered_set<int>& added, std::unordered_set<int>& not_added, std::priority_queue<Edge>& edges, int v) const {
			added.insert(not_added.extract(v)); // move vertex		

			for (auto& edge : edges_[v]) { // add edges that outcome form v
				if (not_added.count(edge.first)) { // only if end vertex of edge was not already added in spanning tree
					edges.push({ v, edge.first, edge.second });
				}
			}
		}		
	};

	void AddEdgesInGraph(std::istream& input, A_Graph& graph) {
		int m; // m - count of edges
		input >> m;

		for (int i = 0; i < m; ++i) {
			int f, t, w;
			input >> f >> t >> w;
			graph.AddEdge(f, t, w);
		}
	}		

	void A_ExpensiveNetwork(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		A_Graph graph(n);

		AddEdgesInGraph(input, graph);	

		std::optional<int> max_spanning_tree(graph.GetMaxSpanningTreeWeight());

		if (max_spanning_tree) {			
			output << max_spanning_tree.value() << '\n';
		}
		else {
			output << "Oops! I did it again\n"s;
		}
	}
	/*-------------------------------------------------------------------------*/	

	//SEND ID: 55499524

	//Class B_Graph - class that represents graph. Interface allows to initialize graph by list
	//of edges and check cycles inside. Edges may be only oriented because checking of cycles in not oriented graph is useless.
	//According task Graph has to find duplicates of routes between two cities (B roads and R roads). In this way, one of road type can be 
	//considered as an opposite direction edges. Thanks to this, we just can check cycles in graph. Cycle will point on route dublicating 
	//Storage of graph is performed as an adjacency lists. There's no need to keep edges as an adjacency matrix because
	// every vertex has pow of outputs ~0.5*N (N - count of vertecies) on average.
	// Time complexity: 
	//   - constructor() - O(1) 
	//   - AddEdge() - O(1) only one edge will be added at once. Therefore adding of all edges will take O(M), M - count of all edges
	//   - IsAcyclic() - method that check cycles in graph. complexity is O(V + E), where's V - count of vertices and E - count of edges in graph
	//   This methods checks all vertecies and if color of vertex is white (w) than it should be checked and all adjacency vertices (equal to pow of output of vertex) of 
	//   this vertex should added in queue for checking (if it hadn't been checked before).
	//
	// Space complexity: 
	//   - Graph: O(E) - where's E - count of edges. 
	//   - constructor() - O(1) of additional memory
	//   - AddEdge() - O(1) of additional memory
	//   - DFS_Cycles() - O(V) of additional memory (V - count of verticies). It's used for storage of aux. information - highlighting of verticies and 
	//   for stack of verticies to check
	

	class B_Graph {
	public:		
		enum class EdgeType {
			B,
			R
		};
		explicit B_Graph(int n)
			:adj_lists_(n + 1)
		{			
		}

		void AddEdge(int from, int to, EdgeType type) {			
			if (type == EdgeType::B) { // front direction edge
				adj_lists_[from].push_back(to);				
			}
			else { // opposite direction edge
				adj_lists_[to].push_back(from);
			}
		}

		bool IsAcyclic() { // check cycles in graph
			return DFS_Cycles();
		}

	private:				
		std::vector<std::vector<int>> adj_lists_;	

		enum class Color {
			WHITE,
			GRAY,
			BLACK
		};

		bool DFS_Cycles() {
			int n = adj_lists_.size() - 1; // num of vertecies
			std::vector<Color> color(n + 1, Color::WHITE); // mark all vertecies as white - not visited
			std::stack<int> stack;

			for (int i = 1; i < n; ++i) { // we have to check all vertices because  all verticies may not be reachable by B edges from first edge.
				if (color[i] == Color::WHITE) {
					stack.push(i); // stack of verticies to check
					while (stack.size() > 0) {
						int v = stack.top();
						stack.pop();

						if (color[v] == Color::WHITE) { // check if vertex was not handled before
							color[v] = Color::GRAY;
							stack.push(v);
							
							for (int j = 0; j < adj_lists_[v].size(); ++j) { // check all edges that incident to 'v' vertex
								int u = adj_lists_[v][j];
								if (color[u] == Color::WHITE) { // add adjacency vertex for checking
									stack.push(u);
								}
								else if (color[u] == Color::GRAY) { // cycle is found. No need to check farther
									return false;
								}
							}
						}
						else { // move out handled vertex. It has gray (g) color
							color[v] = Color::BLACK;
						}
					}
				}
			}
			return true;
		}
	};

	void FillGraph(B_Graph& graph, std::istream& input, int n) {
		int j = 1;
		while (j < n) {
			std::string tmp;
			std::getline(input, tmp);
			for (int i = 0; i < tmp.size(); ++i) {
				if (tmp[i] == 'B') {
					graph.AddEdge(j, j + 1 + i, B_Graph::EdgeType::B);
				}
				else {
					graph.AddEdge(j, j + 1 + i, B_Graph::EdgeType::R);
				}
			}
			++j;
		}
	}
	
	void B_RailRoads(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		input.get();
		B_Graph graph(n);
		FillGraph(graph, input, n);		

		if (graph.IsAcyclic()) {
			output << "YES"s << '\n';
		}
		else {
			output << "NO"s << '\n';
		}		
	}
}

namespace s6_exam_tests {
	using namespace std::literals;
	using namespace s6_exam_problems;

	void A_ExpensiveNetwork() {
		{
			std::stringstream input;
			input << "2 0"s;
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::A_ExpensiveNetwork(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "Oops! I did it again"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4 4"s << '\n'
				<< "1 2 5"s << '\n'
				<< "1 3 6"s << '\n'
				<< "2 4 8"s << '\n'
				<< "3 4 3"s;
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::A_ExpensiveNetwork(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "19"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "3 3"s << '\n'
				<< "1 2 1"s << '\n'
				<< "1 2 2"s << '\n'
				<< "2 3 1"s;
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::A_ExpensiveNetwork(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "3"s << '\n';
			assert(output.str() == res.str());
		}		
	}
	/*-------------------------------------------------------------------------*/
	void B_RailRoads() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "BR"s << '\n'
				<< "B"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "RRR"s << '\n'
				<< "RR"s << '\n'
				<< "R"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "BBB"s << '\n'
				<< "RB"s << '\n'
				<< "B"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "4"s << '\n'
				<< "BBB"s << '\n'
				<< "BB"s << '\n'
				<< "B"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "YES"s << '\n';
			assert(output.str() == res.str());
		}
		
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "RB"s << '\n'
				<< "R"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "5"s << '\n'
				<< "RRRB"s << '\n'
				<< "BRR"s << '\n'
				<< "BR"s << '\n'
				<< "R"s << '\n';
			std::ostringstream output(std::ios_base::ate);
			s6_exam_problems::B_RailRoads(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "NO"s << '\n';
			assert(output.str() == res.str());
		}			
	}
}