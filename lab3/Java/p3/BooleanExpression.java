import java.io.BufferedReader;
import java.io.FileReader;

/**
 * Proiectarea Algoritmilor
 * Lab 3:  Programare Dinamica
 * Task 3: Parantezarea unei expresii booleene
 *
 * @author adinu
 * @email  mandrei.dinu@gmail.com
 *
 */
public class BooleanExpression {

	private String[] symbols;

	private String[] operators;

	private String filename;

	private int numOfSolutions;

	private static final int NOT_SET = -666;

	BooleanExpression(String filename) {
		this.filename = filename;
		numOfSolutions = BooleanExpression.NOT_SET;
		// automatically read input data at creation time
		readData();
	}

	private void readData() {
		BufferedReader br = null;

		try {

			br = new BufferedReader(new FileReader(filename));
			StringBuilder sb = new StringBuilder();
			String line = br.readLine();

			while (line != null) {
				sb.append(line);
				line = br.readLine();
			}
			String[] inputTokens = sb.toString().split(" ");
			int opNum = inputTokens.length / 2;
			int syNum = inputTokens.length / 2 + 1;
			operators = new String[opNum];
			symbols = new String[syNum];
			for (int i = 0; i < inputTokens.length; i++) {
				if (i % 2 == 0) {
					symbols[i / 2] = inputTokens[i];
				} else {
					operators[i / 2] = inputTokens[i];
				}
			}

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null) {
					br.close();
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

	/**
	 * Counts the number of ways in which the boolean expression
	 * can be paranthesized in order to be able to evaluate the entire
	 * expression to 'true'
	 */
	private void computeNumOfCombinations() {
		// TODO
	}

	public int getNumOfCombinations() {
		if (numOfSolutions == BooleanExpression.NOT_SET) {
			computeNumOfCombinations();
		}
		return numOfSolutions;
	}

	@Override
	public String toString() {
		return ("Number of solutions is: " + getNumOfCombinations());
	}

	public static void main(String[] argv) {
		String[] filenames = { "bool1.in", "bool2.in" };
		BooleanExpression[] problemSet =
				new BooleanExpression[filenames.length];

		for (int set = 0; set < filenames.length; set++) {
			problemSet[set] = new BooleanExpression(filenames[set]);
			System.out.println(problemSet[set]);
		}

	}
}
