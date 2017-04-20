package tema1prob1;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;
import java.util.regex.Pattern;

import javax.sound.sampled.Line;

public class Main1 {
		
	static Integer n; //nr de stringuri
	static String s; //stringul de facut paldinrom
	
	
	private static boolean validare(char[] line, int[] times, int len) {

		int i, nrImpare = 0;
		
		//140 e maximul char
		for(i = 0 ; i < 140; i++) {
			
			if(times[i] % 2 == 1)
				nrImpare = nrImpare + 1;
		}
		
		if(nrImpare > 1) return false;
		
		if(nrImpare == 1) { //un singur caracter apara de un nr imapr de ori
			if(len % 2 == 1) //lungimea impara
				return true; 
			else 
				return false; //daca lungimea e para acel singur caracter nu are unde sa se puna
			
		} else if(len % 2 == 1) //nu avea niciun caracter care apare de un nr impar de ori, dar lungimea impara => false
			return false;
		
		return true;
	}
	
	private static int getSwaps(char[] line, int len) {
		
		int nr = 0;
		int j, i;
		int[] times = new int[150];
		
		for(i = 0 ; i < 140; ++i)
			times[i] = 0;
		
		//retin frecventa de aparitie a ficarui caracter
		for(i = 0 ; i < len; i++) {
			
			times[line[i]] = times[line[i]] + 1;
		}
		//verific ca se poate construi un palindrom 
		if(validare(line, times, len) == false) {
			
			return -1;
		}
		
		int last = len;
		
		for(i = 0 ; i < last; i++) {
			
			char c = line[i];
			
			if(times[c] % 2 == 0) {
				
				for(j = last ; j >= 0 ; --j)
					if(line[j] == c) //am gasit perechea
						break;
				
				//acum in j avem pozitia caracterului pe care vrem sa-l mutam
				//pe pozitia unde
				
				int unde = len - i - 1;//unde vreau sa-l pun
				
				while( j != unde) {
					
					Character aux = line[j];
					line[j] = line[j + 1];
					line[j + 1] = aux;
					j++;
					nr++;
				}
				
				last--;
						
			} else { //caracter cu un numar impar de aparaitii, il evitam mutand din cealalta parte
				
				//il caut din spre inceput spre final
				
				int unde = len - i - 1;
				c = line[unde];
				
				for( j = i ; j < last ; j++)
					if(c == line[j])//l-am gasit
						break;
				//acum fac swap-uri de la pozitia de la care l-am gasit pana la pozitia unde voiam sa.l aduc, la fel ca mai sus
				while( j != i) {
					
					Character aux = line[j];
					line[j] = line[j - 1];
					line[j - 1] = aux;
					j--;
					nr++;
				}
				
				last--;
			}
				
		}
		
		return nr;
		
	}
	
	
	public static void main(String[] args)  {
		
		int i , j;
		Scanner scan = null;
		try {
			scan = new Scanner(new File("joc.in"));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		PrintWriter writer = null;
		try {
			writer = new PrintWriter("joc.out", "US-ASCII");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		scan.useDelimiter(Pattern.compile("\n"));
		
		String nr = scan.nextLine();
		n = Integer.parseInt(nr);
		char[] s = new char[355];
		
		for(i = 1; i <= n ; ++i) {
			
		    String logicalLine = scan.next();
		    int len = logicalLine.length();
		    
		    
		    for(j = 0 ; j < len ; j++)
		    	s[j] = logicalLine.charAt(j);
		    
		    //System.out.println(getSwaps(s, len));
		    writer.println(getSwaps(s, len));
		    
		}
		writer.close();
	}

}
