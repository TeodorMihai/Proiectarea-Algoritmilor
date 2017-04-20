/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 *
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

#include "Graph.h"

Graph::Graph() :
		_type(DIRECTED) {

}

Graph::Graph(GraphType type) :
		_type(type) {

}

Graph::~Graph() {
	for (uint i = 0, sz = node_count(); i < sz; ++i) {
		delete nodes[i];
	}
}

uint Graph::node_count() const {
	return nodes.size();
}

void Graph::insert_node(Node* node) {
	nodes.push_back(node);
	edges.push_back(std::vector<Node*>());
	social_network[node->get_name()] = nodes[nodes.size() - 1];
}

void Graph::insert_edge(Node* node1, Node* node2) {
	check_node(*node1);
	edges[node1->get_id()].push_back(node2);
}

std::vector<Node*>& Graph::get_nodes() {
	return nodes;
}

std::vector<Node*>& Graph::get_edges(Node& node) {
	check_node(node);
	return edges[node.get_id()];
}

void Graph::reset() {
	for (uint i = 0, sz = nodes.size(); i < sz; ++i) {
		nodes[i]->discovery_time = Node::UNSET;
		nodes[i]->lowlink = Node::UNSET;
	}

	while (!stack.empty())
		stack.pop();
	ctc.clear();

	articulation_points.clear();
	critical_edges.clear();

	time = 0;
}

/**
 * (Sanity) check if node was correctly initialized
 */
void Graph::check_node(Node& node) const {
	uint _id = node.get_id();
	if (_id > node_count() || _id < 0) {
		std::stringstream ss;
		ss >> _id;
		throw InvalidQuery("Invalid node id: " + ss.str());
	}
}

void Graph::print_ctc() const {
	std::cout << "Strongly Connected Components:\n";

	for (uint i = 0, sz1 = ctc.size(); i < sz1; ++i) {
		for (uint j = 0, sz2 = ctc[i].size(); j < sz2; ++j) {
			std::cout << *ctc[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
}

std::ostream& operator<<(std::ostream& out, Graph& graph) {

	std::cout << "Print Graph :\n";

	for (uint i = 0; i < graph.nodes.size(); ++i) {
		std::cout << "Edges for node " << *graph.nodes[i] << " -> ";
		for (uint j = 0, sz = graph.edges[i].size(); j < sz; ++j) {
			std::cout << *graph.edges[i][j] << " , ";
		}
		std::cout << "\n";
	}

	return out;
}

/*
 Input Format:
 N M
 Node1 Node2 Node3.. NodeN  -- list with every node
 Nodei Nodej				-- list of edges
 ...

 where
 N = Number of Nodes
 M = Number of Edges
 */

std::istream& operator>>(std::istream& in, Graph& graph) {
	uint _nodes, _edges;
	in >> _nodes >> _edges;

	std::string name1, name2;
	for (uint i = 0; i < _nodes; ++i) {
		in >> name1;
		Node *new_node = new Node(name1, i);
		graph.insert_node(new_node);
	}

	for (uint i = 0; i < _edges; ++i) {
		in >> name1 >> name2;
		graph.insert_edge(graph.social_network[name1],
				graph.social_network[name2]);

		if (graph._type == UNDIRECTED) {
			graph.insert_edge(graph.social_network[name2],
					graph.social_network[name1]);
		}
	}

	return in;
}
