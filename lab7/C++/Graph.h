/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 *
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

#ifndef GRAPH_H
#define GRAPH_H

#include"Utils.h"
#include"Node.h"

enum GraphType {
	DIRECTED, UNDIRECTED
};

class Graph {

	/** Directed / Undirected **/
	GraphType _type;

	std::vector<Node*> nodes;
	std::vector<std::vector<Node*> > edges;
	std::map<std::string, Node*> social_network;

	/** check if node was correctly initialized **/
	void check_node(Node& node) const;

public:

	Graph();
	Graph(GraphType type);
	virtual ~Graph();

	/** Return number of nodes in the graph. **/
	uint node_count() const;

	/** Adds the argument node to the graph. **/
	void insert_node(Node* node);

	/** Creates a link between the two specified argument nodes. **/
	void insert_edge(Node* node1, Node* node2);

	/** Returns a vector with all the nodes in the graph. **/
	std::vector<Node*>& get_nodes();

	/** Returns a vector with all the neighbours of a given node. **/
	std::vector<Node*>& get_edges(Node& node);

	/** Removes all temporary information related to the state of the graph
	 *  during traversals (for example it sets every node as being unvisited)
	 */
	void reset();

	int time;

	/** Part I: Structuri auxiliare pentru determinarea componentelor tare conexe **/
	std::stack<Node*> stack;
	std::vector<std::vector<Node*> > ctc;

	void print_ctc() const;

	/** Part II: Structuri auxiliare pentru muchii & noduri critice. **/
	std::stack<std::pair<int, int> > edges_stack;
	std::vector<Node*> articulation_points;
	std::vector<std::pair<Node*, Node*> > critical_edges;

	/** Convenience overload of the IO operators for pretty printing/reading a graph */
	friend std::istream& operator>>(std::istream& in, Graph& node);
	friend std::ostream& operator<<(std::ostream& out, Graph& node);
};

#endif
