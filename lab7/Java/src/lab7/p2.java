/**
 * Proiectarea Algoritmilor, 2016
 * Lab 7: Aplicatii DFS
 *
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 * @author adinu
 * @email  mandrei.dinu@gmail.com
 */

package lab7;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import graph.Graph;
import graph.Node;

public class p2 {

    static void DfsArticulationPoints(Graph g, Node node, int idx, int father) {
        // TODO
    }

    /**
     * Computes and prints at standard output the Articulation Points of the </br>
     * given graph.                                           </br>
     * 
     * Useful API:                                            </br>
     * 
     * List with the articulation points of the graph.        </br>
     * graph.articulationPoints                               </br>
     * 
     * @param g
     */
    static void ArticulationPoints(Graph g) {
        g.reset();

        // TODO
        // HINT: use dfsArticulationPoints after you implement it

        // TODO: uncomment this after you're done
        /*
         * System.out.println("\nPuncte. de articulatie: \n" +
         * g.articulationPoints );
         */
    }

    static void DfsCriticalEdges(Graph g, Node node, int idx, int father) {
        // TODO
    }

    /**
     * Computes and prints at standard output the Critical Edges of the given
     * graph.                              </br>
     * 
     * Useful API:
     * Lista with the critical edges.      </br>
     * graph.criticalEdges                 </br>
     *
     * @param g
     */
    static void CriticalEdges(Graph g) {
        g.reset();

        // TODO
        // Hint: use dfsCriticalEdges after you implement it

        // TODO: uncomment this after you're done
        /* System.out.println("\nMuchii critice: \n" + g.muchiiCritice ); */
    }

    final static String PATH = "./res/test02";

    public static void main(String... args) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(PATH));

        int test_count = scanner.nextInt();
        for (int i = 1; i <= test_count; ++i) {
            System.out.println("TEST " + i + "\n");

            Graph g = new Graph(Graph.GraphType.UNDIRECTED);
            g.readData(scanner);

            System.out.println(g);
            ArticulationPoints(g);
            CriticalEdges(g);
        }

        scanner.close();
    }
}
