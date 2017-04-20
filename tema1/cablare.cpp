#include <bits/stdc++.h>

using namespace std;

ifstream fin("cablaj.in");
ofstream fout("cablaj.out");

const int INF = 0x3f3f3f3f;
const int NMAX = 52;

int n;
char pins[NMAX * 2];
int sol[NMAX * 2]; //retin pperechea pentru fiecare pin
int sum[NMAX * 2]; //ca sa verific in O(1) daca se poate cabla un pic cu altul

vector<pair<int, int> > s;

struct Cablu {

	int height;
	int cost;

	Cablu() : height(0) , cost(0) {}

	Cablu(int height, int cost) : height(height), cost(cost) { }
};

Cablu d[NMAX * 2][NMAX * 2];//d[i][j] = costul minim pe care il pot obtine in intervalul [i, j]

bool isValid(int x, int y) {

	if(x >= y) return true;

	return y - x + 1 == 2 * (sum[y] - sum[x - 1]) ;
}

bool canCable(int x, int y) { //daca pot duc cablue de la x la y

	if(x >= y) return false;

	if(pins[x] == pins[y]) return false;//trebuie sa fie pinii diferiti

	return isValid(x, y);
}

Cablu cablare(int x, int y) {

	if(x >= y) return Cablu(0, 0);
	
	if(d[x][y].cost != 0)
		return d[x][y];

	if(y - x == 1 && pins[x] != pins[y]) { //pinii sunt unul langa altul
		d[x][y] = Cablu(1, 3);
		sol[x] = y;	//pinul x este prins la pinul y
		return d[x][y];
	}

	d[x][y].cost = INF;
	//duc cablu de la x la y
	if( canCable(x , y ) ) {
		Cablu res = cablare(x + 1, y - 1);
		d[x][y] = Cablu(res.height + 1, res.cost + (res.height + 1) * 2 + (y - x) );
		//formula costului unui cablu
		sol[x] = y;
	}
	

	//incerc sa duc un cablu de la x la i
	for(int i = x + 1; i + 1 < y ; ++i) { 

		if(isValid(i + 1, y ) == false)
			continue;
	
		if(canCable(x , i) == false)
			continue;

		Cablu res1 = cablare(x + 1 , i - 1);//duc cablu de la x la i
		Cablu res2 = cablare(i + 1 ,y);//costul din dreapta, nu duc cablu(poate duc dar nu acum)

		int cost =  res1.cost + res2.cost + (i - x) + (res1.height + 1) * 2;
		//formula de cost
		int height = max(res1.height + 1, res2.height) ;//am dus cablu, deci maresc inaltimea

		if(d[x][y].cost > cost) {
			//daca cablu dus de la x la i e mai bun ca ce aveam pana acum actualizez
			d[x][y] = Cablu(height, cost);
			sol[x] = i;	 
		}
	}

	return d[x][y];
}

void getSol(int x, int y) {//obtin un vector cu solutiile

	if(x >= y) return ;
	s.push_back(make_pair(x, sol[x]));

	getSol(x + 1, sol[x] - 1);
	if(sol[x] < y)
		getSol(sol[x] + 1, y);

}

int main() {

	fin >> n ;

	fin >> pins ;

	for(int i = 0 ; i < strlen(pins); ++i)
		sum[i] = sum[i - 1] + (pins[i] - '0');
		//sume partiale, sa verific in O(1) cand pot duce cablu

	
	Cablu res = cablare(0, n * 2 - 1);//calculez costul minim prin memoizare

	fout << res.cost << '\n'; 

	getSol(0, n * 2 - 1);
	sort(s.begin(), s.end());

	for(vector< pair<int, int> >::iterator it = s.begin(); it != s.end(); ++it)
		fout << (*it).first + 1 << ' ' << (*it).second + 1<< '\n'; 
		//+1 pentru ca eu indexasem de la 0

	return 0;
}