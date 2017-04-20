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

/**
Algoritmul lui Tarjan pentru determinarea componentelor tare conexe
Complexitate: O( N + M )
unde
	N - nr de noduri
	M - nr de muchii

Useful API:

Vector cu vecinii nodului.
graph.get_edges(node)

Vector cu componentele tare conexe ale grafului.
graph.ctc

Stiva cu nodurile din componenta tare conexa curenta.
graph.stack

Variabila booleana - true daca nodul se afla pe stiva
node->in_stack

Timpul de descoperire al unui nod.
node->discovery_time

In functie de timpul de descoperire, intoarce true daca nodul a mai fost vizitat.
node->was_visited()

Cel mai mic timp de descoperire al unui nod accesibil din nodul curent.
node->lowlink

Indexul componentei conexe din care face parte nodul.
node->ctc_index
**/

void dfs_ctc(Graph& g, Node* node) {

	/**	TODO: Initializeaza timpul de descoperire si lowlink */

	/** TODO: Adauga nodul in stiva */

	/** TODO: Parcurgere DF pentru fiecare vecin nevizitat */

	/** TODO: Salveaza componenta tare conexa curenta */
}

/**
 * Identifica componentele tare conexe din graful primit ca parametru
 */
void StronglyConnectedComponents(Graph& g) {
	g.reset(); // reseteaza starea variabilelor auxiliare din graf

	/** TODO: Apeleaza dfs_ctc pentru fiecare nod nevizitat */

	g.print_ctc(); // afiseaza componentele tare conexe
	return;
}

Graph* compress_graph(Graph& input_graph);

/*
 * TODO: Calculeaza numarul maxim de jucatori daca s-ar adauga o legatura artificiala
 * Complexitate solutie: O( N + M )
 * N - numarul de noduri din graful comprimat
 * M - numarul de muchii
 */
void bonus(Graph& input_graph) {

	/**
	 * HINT: In urma compactarii grafului original rezulta un graf orientat,
	 * fara cicluri, pe care il vom numi in mod sugestiv, Cluster (mai multe
	 * noduri grupate in acelasi loc)
	 */
	Graph* cluster = compress_graph(input_graph);

	// TODO afiseaza numarul de noduri maxim obtinut in urma adaugarii
	// unei legaturi artificiale.
}

/**
 * Construim un nou graf, unind elementele care alcatuiau o componenta tare conexa
 * intr-un singur nod.
 */
Graph* compress_graph(Graph& input_graph) {

	uint countCTC = input_graph.ctc.size();
	if (countCTC == 0) {
		StronglyConnectedComponents(input_graph);
		countCTC = input_graph.ctc.size();
	}

	/** Alocam un nod nou pentru fiecare componenta tare conexa din graful original. **/
	Graph* cluster = new Graph();
	for (uint i = 0; i < countCTC; ++i) {
		cluster->insert_node(new Node(i));
	}

	std::vector<Node*>& all_clusters = cluster->get_nodes();
	for (uint i = 0, sz = input_graph.ctc.size(); i < sz; ++i) {

		// nodurile care alcatuiesc componenta conexa curenta
		std::vector<Node*>& inner_nodes = input_graph.ctc[i];

        // folosim un set pentru a ne asigura ca nu avem muchii duplicate
		std::set<int> connections;

		// pentru fiecare nod..
		for (uint j = 0; j < inner_nodes.size(); ++j) {
			std::vector<Node*>& edges = input_graph.get_edges(*inner_nodes[j]);

			// pentru fiecare muchie..
			for (uint k = 0; k < edges.size(); ++k) {
				uint idx_ctc = edges[k]->ctc_index;

				if (idx_ctc != i
						&& connections.find(idx_ctc) == connections.end()) {
					cluster->insert_edge(all_clusters[i], all_clusters[idx_ctc]);
					connections.insert(idx_ctc);
				}
			}
		}

		all_clusters[i]->count_nodes = inner_nodes.size();
	}

	std::cout << "Graful comprimat: ";
	std::cout << *cluster << "\n";

	return cluster;
}


int main(int argc, char* argv[]) {

	if (freopen("test01.in", "r", stdin) == NULL)
		return 1;
	if (freopen("test01.out", "w", stdout) == NULL)
		return 1;

	int nr_teste;
	std::cin >> nr_teste;

	for (int i = 1; i <= nr_teste; ++i) {
		std::cout << "TEST " << i << "\n";
		Graph g1(DIRECTED);
		std::cin >> g1;
		StronglyConnectedComponents(g1);
		//bonus(g1);
	}

	return 0;
}
