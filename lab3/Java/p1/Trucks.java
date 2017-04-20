import java.io.File;
import java.util.Scanner;

/**
 * Proiectarea Algoritmilor
 * Lab 3:  Programare Dinamica
 * Task 1: Problema Rucsacului (varianta discreta)
 *
 * @author adinu
 * @email  mandrei.dinu@gmail.com
 *
 */
class Item {

	int weight;
	int profit;

	public Item(int weight, int profit) {
		this.weight = weight;
		this.profit = profit;
	}
}

public class Trucks {

	/* The max weight accepted by the truck to be transported */
	private int maxWeightAccepted;

	/* The total number of items to choose from */
	private int numOfItems;

	private Item[] furniturePiece;

	/* The indices of the furniture pieces selected as solution */
	private int[] selectedItems; // TODO

	private String filename;

	private static final int NOT_SET = -666;

	public Trucks(String filename) {
		this.filename = filename;
		readData();
	}

	private void readData() {
		Scanner sc = null;

		try {
			sc = new Scanner(new File(filename));
			numOfItems = sc.nextInt();
			maxWeightAccepted = sc.nextInt();

			furniturePiece = new Item[numOfItems];
			int x, y;
			for (int i = 0; i < numOfItems; i++) {
				x = sc.nextInt(); y = sc.nextInt();
				furniturePiece[i] = new Item(x, y);
			}

			for (int i = 0; i < numOfItems; i++) {
				System.out.println(furniturePiece[i].weight + " "
									+ furniturePiece[i].profit);
			}

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (sc != null) {
					sc.close();
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

	public void selectItems() {
		// TODO;
	}

	public int getProfitOfSelectedItems() {
		// TODO
		return NOT_SET;
	}

	public Item[] getSelectedItems() {
		//TODO: use indices from selectedItems[]
		return null;
	}

	public void test() {
		System.out.println("Max obtained profit for given items is: "
							+ getProfitOfSelectedItems());
		System.out.println(" Selected items are: ");
		Item[] items = getSelectedItems();
		for (int i = 0; i < items.length; i++) {
			System.out.println("(weight, profit): (" + items[i].weight
					+ ", " + items[i].profit + ")");
		}
	}

	public static void main(String[] argv) {
		String[] filenames = { "knapsack.in" };
		Trucks[] problemSet = new Trucks[filenames.length];

		for (int i = 0; i < problemSet.length; i++) {
			problemSet[i] = new Trucks(filenames[i]);
			problemSet[i].selectItems();
			// TODO: uncomment this
			// problemSet[i].test();
		}

	}
}
