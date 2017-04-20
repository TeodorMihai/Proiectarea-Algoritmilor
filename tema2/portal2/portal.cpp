#include <bits/stdc++.h>

using namespace std;

ifstream fin("portal.in");
ofstream fout("portal.out");


const int NMAX = 100009;
const int MMAX = 100009;

int n; int m;

vector<int> g[NMAX];

int cnt;

int viz[NMAX];

bool hasCycle = false;

void read() {

	fin >> n >> m ;

	for(int i = 1; i <= m; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

}

void dfs(int node, int father) {

	viz[node] = 1;

	for(int x : g[node]) {
		if(viz[x] == 1 && x != father) 
			hasCycle = true;
		
		if(viz[x] == 0)
			dfs(x, node);
	}

}

void solve() {

	memset(viz, 0, sizeof(viz));

	for(int i = 1; i <= n; ++i)
		if(viz[i] == 0) {
			hasCycle = false;
			dfs(i, 0);
			if(hasCycle == false)	
				cnt++;
		}

	fout << cnt << '\n'; 
}

int main() {

	read();

	solve();

	return 0;
}