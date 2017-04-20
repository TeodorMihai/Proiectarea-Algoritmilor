#include <bits/stdc++.h>

using namespace std;

#define DELETE 1
#define INSERT 1
#define SUBSTITUTE 1

ifstream fin("evaluare.in");
ofstream fout("evaluare.out");

const int VMAX = 602;
const int NMAX = 1220;
const int VALMAX = 260;

int b[NMAX];

//d[i][j] = costul minim de a broda solfegiul [1...j] la toate partiturile de lungime [1...i]
int v; int n; int m;

int thereis[NMAX][VALMAX];

void read() {

	fin >> v >> n;
	
	int x;

	for(int i = 1; i <= v; ++i) 
		for(int j = 1; j <= n; ++j) {
			
			fin >> x;
			thereis[j][x] = 1; 
		}

	fin >> m;

	for(int i = 1; i <= m; ++i)
		fin >> b[i];

	fin.close();
}

void solve() {

	int d[NMAX][NMAX];

	d[0][0] = 0;

	for(int i = 1 ; i <= m ; ++i)
		d[0][i] = i; //le stergem e toate

	for(int i = 1; i <= n; ++i)
		d[i][0] = i; //le inseram pe toate

	//putem modifica doar b => 
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			
			int costInsDel = min(d[i - 1][j] + 1, d[i][j - 1] + 1);

			if(thereis[i][b[j]])
				d[i][j] = min(d[i - 1][j - 1], costInsDel);
			else 
				d[i][j] = min(d[i - 1][j - 1] + 1, costInsDel);
		}

	fout << d[n][m] << '\n'; 
}

int main() {

	ios::sync_with_stdio(false);

	read();

	solve();

	return 0;
}