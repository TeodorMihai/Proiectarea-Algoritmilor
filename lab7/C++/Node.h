/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 *
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

#ifndef NODE_H
#define NODE_H

#include "Utils.h"

class Node {

	std::string _name;
	uint _id;

public:

	Node(std::string name, uint id);
	Node(uint id);

	/**
	 * Variable holds the moment in time a node was discovered
	 * during the DFS traversal (the idx from the pseudo-code).
	 * For an unvisited node, the value defaults to UNSET.
	 */
	int discovery_time;

	/**
	 * Default discovery time for an unvisited node.
	 */
	static const int UNSET = -1;

	/**
	 * Returns true if the node was visited, false otherwise.
	 */
	bool was_visited() const;

	/**
	 * The smallest discovery time for a node that is accessible from the
	 * current node.
	 */
	int lowlink;

	/**
	 * Variable holds true if the node is currently stored on the
	 * stack during Tarjan's algorithm.
	 */
	bool in_stack;

	/**
	 * Bonus: The index of the strongly connected component.
	 */
	int ctc_index;

	/**
	 * Bonus: The number of nodes in a cluster
	 */
	int count_nodes;

	const std::string& get_name() const;
	const uint get_id() const;

	/** Convenience overload of the IO operators for pretty printing/reading a node */
	friend std::istream& operator>>(std::istream& in, Node& node);
	friend std::ostream& operator<<(std::ostream& out, Node& node);
	friend std::ostream& operator<<(std::ostream& out, Node* node);
};

#endif
