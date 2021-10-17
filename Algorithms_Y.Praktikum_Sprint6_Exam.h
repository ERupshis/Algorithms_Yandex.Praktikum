#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <optional>



namespace s6_exam_problems {
	using namespace std::literals;

	//SEND ID: ???
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



	class Graph {
	public:
		explicit Graph(int n, bool oriented = false)
			:edges_(n + 1), oriented_(oriented) 
		{
			while (n > 0) {
				vertices_.insert(n);
				--n;
			}
		}

		void AddEdge(int from, int to, int weight) {
			if (from != to //zero edge from == to
				&& (edges_[from].count(to) == 0 || edges_[from].at(to) < weight)) { // add new edge if edge is not added or rewrite old if new is bigger
				edges_[from][to] = weight;
				if (!oriented_) {
					edges_[to][from] = weight; //not  oriented - we need to add opposite direction graph for easier search
				}
			}			
		}

		std::unordered_set<int> GetVertices() const {
			return vertices_;
		}

		const std::unordered_map<int, int>& GetEdgesFromVert(int v) const {
			return  edges_[v];
		}

	private:		
		bool oriented_ = false;
		std::unordered_set<int> vertices_{};
		std::vector<std::unordered_map<int, int>> edges_;
	};

	void AddEdgesInGraph(std::istream& input, Graph& graph) {
		int m; // m - count of edges
		input >> m;

		for (int i = 0; i < m; ++i) {
			int f, t, w;
			input >> f >> t >> w;
			graph.AddEdge(f, t, w);
		}
	}

	void AddVertexInSpanningTree(Graph& graph, std::unordered_set<int>& added, std::unordered_set<int>& not_added, std::priority_queue<Edge>& edges, int v) {
		added.insert(not_added.extract(v)); // move 		

		for (auto& edge : graph.GetEdgesFromVert(v)) { // add edges that outcome form v
			if (not_added.count(edge.first)) { // only if end vertex of edge was not already added in spanning tree
				edges.push({ v, edge.first, edge.second });
			}
		}
	}

	std::optional<std::vector<Edge>> FindMaxSpanningTree(Graph& graph) {
		std::vector<Edge> res;
		std::unordered_set<int> added; // already added in span
		std::unordered_set<int> not_added(graph.GetVertices()); // should be added
		std::priority_queue<Edge> edges; // edges that go out from span
				
		int v = *not_added.begin();
		AddVertexInSpanningTree(graph, added, not_added, edges, v);

		while (not_added.size() > 0 && edges.size() > 0) {
			Edge e = edges.top(); // extract max weighted edge
			edges.pop();

			if (not_added.count(e.to)) { //if end vertex of this edges is not added in spaning tree
				res.push_back(e); //add this edge
				AddVertexInSpanningTree(graph, added, not_added, edges, e.to); // add end vertex and outcome edges
			}
		}

		if (not_added.size() > 0) { // no edges to some vertices
			return std::nullopt;
		}
		else {
			return res;
		}
	}	

	void A_ExpensiveNetwork(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		Graph graph(n);

		AddEdgesInGraph(input, graph);	

		std::optional<std::vector<Edge>> max_spanning_tree(FindMaxSpanningTree(graph));

		if (max_spanning_tree) {
			int spanning_tree_length = 0;
			for (const auto& elem : *max_spanning_tree) {
				spanning_tree_length += elem.weight;
			}
			output << spanning_tree_length << '\n';
		}
		else {
			output << "Oops! I did it again\n"s;
		}
	}
	/*-------------------------------------------------------------------------*/
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

}