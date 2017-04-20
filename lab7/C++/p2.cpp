/**
 * Proiectarea Algoritmilor, 2016
 * Lab 7: Aplicatii DFS
 *
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 * @author adinu
 * @email  mandrei.dinu@gmail.com
 */

#include "Graph.h"

void dfs_articulation_points(Graph& g, Node* node, int& idx, int father) {
	// TODO
}

/**
 * Computes and prints at standard output the Articulation
 * Points of the given graph
 *
 * Useful API:
 * graph.articulation_points
 *
 * @param g
 */
void compute_articulation_points(Graph& g) {
	g.reset(); // reseteaza variabilele auxiliare

	// TODO
	// Hint: use dfs_articulation_points after you implement it

	// print the vector of articulation points g.puncte_de_articulatie
}

void dfs_critical_edges(Graph& g, Node* node, int& idx, int father) {
	// TODO
}

/**
 * Computes and prints at standard output the Critical Edges
 * of the given graph.
 *
 * Useful API:
 * graph.critical_edges
 *
 * @param g
 */
void compute_critical_edges(Graph& g) {
	g.reset(); // reseteaza variabilele auxiliare

	// TODO

	// Hint: use dfs_critical_edges after you implement it

	// print the vector of critical edges g.muchii_critice
}

int main(int argc, char* argv[]) {

	if (freopen("test02.in", "r", stdin) == NULL)
		return 1;
	if (freopen("test02.out", "w", stdout) == NULL)
		return 1;

	int nr_teste;
	std::cin >> nr_teste;

	for (int i = 1; i <= nr_teste; ++i) {
		std::cout << "TEST " << i << "\n";
		Graph g2(UNDIRECTED);
		std::cin >> g2;
		compute_articulation_points(g2);
		compute_critical_edges(g2);
		std::cout << "################################\n";
	}

	return 0;
}
