#include <bits/stdc++.h>

using namespace std;

ifstream fin("joc.in");
ofstream fout("joc.out");

const int NMAX = 1000;
const int MMAX = 350;
const int ALPHABET = 150;

int n; int m;

char v[MMAX + 1];

//retunreaza indexul cel mai din dreapta incepand de la start al caracterului x
int getRightMost(char x, int start) {

	for(int i = start; i >= 0; --i)
		if(x == v[i])
			return i;
	return -1;
}

//retunreaza indexul cel mai din stanga incepand de la start al caracterului x
int getLeftMost(char x, int start) {

	for(int i = start; i < m; ++i)
		if(x == v[i])
			return i;
	return -1;
}

void solve() {

	int odd = 0; //cate caractere impare am
	int cnt = 0;//cate swapuri fac

	char oddChar = 0;//caracterl impar, daca exista

	int freq[ALPHABET];

	//numa frecventa de aparitie a ficarui caracter
	for(int i = 0 ; i < ALPHABET; ++i)
		freq[i] = 0;

	for(int i = 0 ; i < m ; ++i) 
		freq[v[i]]++;	

	//verific daca pot forma palindrom
	for(int i = 0 ; i < ALPHABET; ++i)
		if(freq[i] % 2) {
			odd++;
			oddChar = i;
			if( (odd > 1 && m % 2 == 1) || (odd > 0 && m % 2 == 0) ) {
				fout << -1 << '\n'; 
				return ;
			}
		}	

	for(int i = 0 ; i < m/2; ++i) {

		int right = m - i - 1;
		int left = i;

		if(odd && v[left] == oddChar && freq[v[left]] == 1) {
			//daca intalnesc caracterul impar incerc sa-l potrivesc pe cel simetric lui

			int ind = getLeftMost( v[right], left); //gasesc indicele caracterului
													//pe care vreau sa-l aduc pe pozitia i

			for( ; ind != left ; ind--, cnt++) 		//il interschimb pana ajuge unde vreau
				swap(v[ind], v[ind - 1]);

		}  else {
				//asemanator cu ce am facut mai sus

				int ind = getRightMost(v[left], right );

				for( ; ind != right ; ind++, cnt++) 
					swap(v[ind], v[ind + 1]);
				
				freq[v[i]] -= 2;//scad frecventa lui
			} 	
	}

	fout << cnt << '\n';

}

void read() {

	fin >> n;

	while(n--) {

		fin >> v ;
		m = strlen(v);
		solve();
	}
}

int main() {

	read();

	return 0;
}

