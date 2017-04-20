import java.io.File;
import java.util.Scanner;
/**
 * Proiectarea Algoritmilor
 * Lab 3:  Programare Dinamica
 * Task 2: Aranjarea cartilor intr-o biblioteca
 *
 * @author adinu
 * @email  mandrei.dinu@gmail.com
 *
 */
public class Books {

	/* number of closets in the room */
	private int closetsNum;

	/* holds the num of books for each closet */
	private int[] books;

	private String inputFilename;

	// TODO
	private int maxBooksAfterArrange;

	private static final int NOT_SET = -666;

	Books(String inputFilename) {
		this.inputFilename = inputFilename;
		// automatically reads input data at creation time
		readData();
		maxBooksAfterArrange = Books.NOT_SET;
	}

	private void readData() {
		Scanner sc = null;

		try {
			sc = new Scanner(new File(inputFilename));

			closetsNum = sc.nextInt();
			books = new int[closetsNum];
			for (int c = 0; c < closetsNum; c++) {
				books[c] = sc.nextInt();
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

	/**
	 * Computes the maximum number of books that can be obtained
	 * after rearranging the closets into the new library.
	 */
	private void computeMaxBooks() {
		//TODO
	}

	public int getMaxBooksAfterArrange() {
		if (maxBooksAfterArrange == NOT_SET) {
			computeMaxBooks();
		}
		return maxBooksAfterArrange;
	}

	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("With initial array of books into closets: [");
		for (int i = 0; i < closetsNum - 1; i++) {
			sb.append(books[i] + ", ");
		}
		sb.append(books[closetsNum - 1] + "]\n");
		sb.append(" The result is: " + getMaxBooksAfterArrange() + "\n");

		return sb.toString();
	}

	public static void main(String[] argv) {
		String[] filenames = { "carti1.in" };
		Books[] problemSet = new Books[filenames.length];
		for (int set = 0; set < filenames.length; set++) {
			problemSet[set] = new Books(filenames[set]);
			System.out.println(problemSet[set]);
		}
	}

}
