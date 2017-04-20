/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 * 
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

#include "Node.h"

Node::Node(uint id) :
		_name(""), _id(id), discovery_time(UNSET), lowlink(UNSET),
		ctc_index(UNSET), count_nodes(UNSET) {
	in_stack = false;
}

Node::Node(std::string name, uint id) :
		_name(name), _id(id), discovery_time(UNSET), lowlink(UNSET),
		ctc_index(UNSET), count_nodes(UNSET) {
	in_stack = false;
}

const uint Node::get_id() const {
	return _id;
}

const std::string& Node::get_name() const {
	return _name;
}

bool Node::was_visited() const {
	return discovery_time != UNSET;
}

std::istream& operator>>(std::istream& in, Node& node) {
	in >> node._name;
	return in;
}

std::ostream& operator<<(std::ostream& out, Node& node) {
	out << "Node : ";
	out << "id: " << node._id;
	return out;
}

std::ostream& operator<<(std::ostream& out, Node* node) {
	out << *node;
	return out;
}
