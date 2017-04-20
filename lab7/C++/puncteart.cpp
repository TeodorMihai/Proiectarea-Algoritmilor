#include <bits/stdc++.h>

using namespace std;

ifstream fin("puncteart.in");
ofstream fout("puncteart.out");

const int NMAX = 50000;

int n; int m;

vector<int> g[NMAX];
set<int> sol;
set< pair<int, int> > edge;

int low[NMAX]; int d[NMAX];
int viz[NMAX];

int desc;


void read() {

	fin >> n >> m;


	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs(int node, int father) {


	d[node] = ++desc;
	low[node] = desc;

	int sons = 0;

	viz[node] = 1;

	for(int x : g[node]) {
		
		if(father == x) continue; //nu ne intereseaza muchia spre tata

		if(viz[x] == 0) {//muchie inainte

			sons++;
			dfs(x, node);
			//am calculat deja low[x]
			if(low[x] >= d[node] && sol.find(node) == sol.end() && father != 0) {//punct de articulatie, nu pot sa ma intorc mai sus
								//se deconteaza arborele cu filui x xi nu exista deja in lista
				sol.insert(node);
			}

			if(low[x] > d[node] && father != 0)
				edge.insert({node, x});

		} else { //muchie inapoi
			//de ce nu merge aici?
			//low[node] = min(low[node], low[x]);

		}
	}

	for(int x : g[node]) {
		if(father == x)
			continue;
		low[node] = min(low[node], low[x]);
	}

	cout << node << ' ' << low[node] << '\n'; 

	if(father == 0 && sons > 1)
		sol.insert(node);
}

void solve() {

	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0) 
			dfs(i, 0);
		
}

void print() {
	cout <<"Puncte de articulatie: " << '\n'; 
	for(int x : sol)
		cout << x << ' ';

	cout << '\n';

	cout << "Muchii critice:\n" ;

	for(auto p : edge) 
		cout << p.first << ' ' << p.second << '\n'; 
	cout << '\n'; 

}

int main () {

	read();
	solve();
	print();
	return 0;
}
