package tema1prob2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

public class Main2 {
	
	public static final int NR_VAR = 602;
	public static final int N = 1243;
	public static final int ASCII_MAX = 260;
	
	public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
		
		int i; int j;
		
		Scanner scan = new Scanner(new File("evaluare.in"));
		PrintWriter writer = new PrintWriter("evaluare.out", "US-ASCII");
		//scan.useDelimiter(Pattern.compile(" "));
		
		int nr_var = scan.nextInt();
		
		//System.out.print(nr_var);
		
		int n = scan.nextInt();
		
		//System.out.println(n);
		
		int[][] mat = new int[NR_VAR][N];
		int[][] has =  new int[N][ASCII_MAX];
		
		for(i = 0 ; i < N; i++)
			for(j = 0 ; j < ASCII_MAX;j++)
				has[i][j] = 0;
		
		for(i = 1; i <= nr_var ;i++) {
			for(j = 1; j <= n ;j++) {
			
				mat[i][j] = scan.nextInt();
				//System.out.print(mat[i][j] + " ");
				has[j][mat[i][j]] = 1;
			}
			
			System.out.println();
		}
				
		int m = scan.nextInt();
		
		//System.out.println(m );
		
		int toMatch[] = new int[N];
		
		for(i = 1; i <= m; i++) {
		
			toMatch[i] = scan.nextInt();
			//System.out.print(toMatch[i] + " ");
		}
		
		//setez conditiile initiale ale dinamicii
		
		int[][] minCost = new int[N][N];
		
		//minCost x y = costul de transformare a sirului pana la x in sirul pana la y
		
		
		for(i = 0 ; i <= n ; i++)
			minCost[0][i] = i; 
		
		for(i = 0 ; i <= m ; i++)
			minCost[i][0] = i;
		
		for(i = 1; i <= n;i++)
			for(j = 1; j <= m ;j++) {
				
				int match = 0;
				//in coloeana i din matricea exista elemtul pe care vrem sa-l adaugam acum 
				if(has[i][toMatch[j]] == 1)
					match = 0;//exista
				else 
					match = 1; //nu exista
				
				minCost[i][j] = minCost[i - 1][j - 1] + match;
				minCost[i][j] = Math.min(minCost[i][j], minCost[i - 1][j] + 1);//stergem
				minCost[i][j] = Math.min(minCost[i][j], minCost[i][j - 1] + 1);//inseram
			
			}
		
		writer.println(minCost[n][m]);//sa transform practic sirul al doilea de lungime m in primul sir(toata matricea aia 
		// o tratez ca pe un sir de lungime n
		writer.close();

	}

}
