#include <bits/stdc++.h>

using namespace std;

ifstream fin("kim.in");
ofstream fout("kim.out");

#define pp pair<int,int>

const int NMAX = 200009;
const int MMAX = 200009;
const int QMAX = 300009;
const int INF = 0x3f3f3f3f;
const int LGMAX = 20;

struct Edge {

	int x; int y; int d;

	Edge() : x(0) , y(0) , d(0) { }
	Edge(int _x , int _y , int _d) : x(_x) , y(_y), d(_d) { }
	bool operator <(const Edge& edge) const {
		return this->d < edge.d;
	}

}; 

int n; int m; int q;

vector<pp> tree[NMAX];

int fath[NMAX]; int h[NMAX];

int ord[NMAX * 2];

int fst[NMAX];int height[NMAX * 2];

int rmq[MMAX * 2][LGMAX]; int lgg[MMAX * 2];

Edge edges[MMAX];
Edge edgeQuery[NMAX];

vector<int> stramos[NMAX]; //stramos[node][i] = al 2 ^ i stramos incepand de la node , in ordinea
						   //parcurgerii dfs

vector<int> ed[NMAX]; //ed[node][i] = muchia maxima de pe drumul de la node spre radacina, cuprinzand
					  //2 ^ i muchii in sus(spre radacina) incpand de la node

int take[NMAX];
int st[NMAX]; 
int stEdges[NMAX];

int heightNode[NMAX];

int64_t minCost;

void read() {

	fin >> n >> m >> q;

	for(int i = 1; i <= m ; ++i) {

		int x; int y; int d;
		fin >> x >> y >> d;
		edges[i] = Edge(x, y, d);
		edgeQuery[i] = Edge(x, y, d);
	}
}

int root(int x) {
	
	if(fath[x] == x)
		return x;

	return (fath[x] = root(fath[x]));
}

void makeUnion(int x, int y) {

	if(h[x] < h[y])
		fath[x] = y;
	else if(h[x] > h[y])
		fath[y] = x;
	else {
		fath[y] = x;
		h[x]++;
	}
}
void minSpanningTree() {

	for(int i = 1; i <= n; ++i)
		fath[i] = i, h[i] = 1;
	//fiecare element formeaza o multime de unul signur, inaltimea arborelui
	//fiecarei multimi este 1

	for(int i = 1; i <= m ; ++i) {

		int x = edges[i].x;
		int y = edges[i].y;
		int d = edges[i].d;

		if(root(x) != root(y)) {

			makeUnion(root(x), root(y));
			minCost += 1ll * edges[i].d;
			take[i] = 1;
			tree[x].push_back({y, d});
			tree[y].push_back({x, d});
		}
	}
}

void constructDinamic(int* st, int* stEdges) {

	if(st[0] == 1)//nu am ce retine pentru radacina
		return ;
	//stEdges[0] = st[0] - 1//nr muchii = nr noduri - 1
	int x = st[st[0]];

	/*
	cout << x << "  ";

	for(int i = 1; i <= stEdges[0]; ++i)
		cout << stEdges[i] << ' ' ;
	cout << '\n'; 
	*/

	ed[x].push_back(stEdges[stEdges[0]]);
	stramos[x].push_back(st[st[0] - 1]);

	for(int i = 1 ; (1 << i) <= stEdges[0]; ++i) {
		
		int ancestor = st[st[0] - (1 << (i - 1))];

		int val = max(ed[x][i - 1], ed[ancestor][i - 1]);
		ed[x].push_back(val);
	}

	for(int i = 1 ; (1 << i) < st[0]; ++i) {

		int val = stramos[stramos[x][i - 1]][i - 1];
		stramos[x].push_back(val);
	}
}


void dfs(int node, int par, int c) {

	st[++st[0]] = node;

	constructDinamic(st, stEdges);

	ord[++ord[0]] = node;

	fst[node] = ord[0];
	height[ord[0]] = height[fst[par]] + 1;
	heightNode[node] = heightNode[par] + 1;

	for(pp x : tree[node])
		if(x.first != par) {

			stEdges[++stEdges[0]] = x.second;

			dfs(x.first, node, x.second);

			--stEdges[0];

			ord[++ord[0]] = node;
			height[ord[0]] = height[fst[par]] + 1;
		}

	--st[0];
}

void makeRmq() {

	//rmq[i][j] = minimul dintre [i, i +  2 ^ j - 1]
	lgg[0] = 0;
	lgg[1] = 0;

	for(int i = 2; i <= ord[0] ; ++i)
		lgg[i] = lgg[i/2] + 1;
	//lgg[i] = x, ai x ^ 2 <= i, x maxim

	for(int i = 1; i <= ord[0] ; ++i)
		rmq[i][0] = i;

	for(int lg = 1; 1 + (1 << lg) <= ord[0] ; ++lg)
		for(int i = 1; i <= ord[0]; ++i) {

			if( i + (1 << lg) > ord[0]) continue;
			rmq[i][lg] = rmq[i][lg - 1];

			if(height[rmq[i][lg]] > height[rmq[i + (1 << ( lg - 1 ) )][lg - 1]])
				rmq[i][lg] = rmq[i + (1 << (lg - 1))][lg - 1];

		}
}

int findLCA(int x, int y) {

	int fstX = fst[x];
	int fstY = fst[y];

	if(fstX > fstY)
		swap(fstX, fstY);

	int dif = fstY - fstX + 1;
	int logg = lgg[dif];
	int lca = rmq[fstX][logg];

	if(height[lca] > height[ rmq[fstY - (1 << logg) + 1][logg] ])
		lca = rmq[fstY - (1 << logg) + 1][logg];

	return ord[lca];
}

int query(int x, int h) {

	int mucMax = 0;

	while(h > 0) {

		mucMax = max(ed[x][lgg[h]], mucMax);
		x = stramos[x][lgg[h]];
		h -= (1 << lgg[h]);
	}

	return mucMax;
}

int solveQuery(int ind) {

	int x = edgeQuery[ind].x;
	int y = edgeQuery[ind].y;

	int lca = findLCA(x, y);
	

	int hlca = heightNode[lca];
	int hx = heightNode[x];
	int hy = heightNode[y];
	//cout << hlca <<  ' ' << hx << ' ' << hy << '\n'; 
	int maxEdgeCycle = query(x, hx - hlca);//muchia maxima de la x, hx - hlca nivele in sus
	maxEdgeCycle = max(maxEdgeCycle, query(y , hy - hlca));
	
	return maxEdgeCycle;

}

void constructLCA() {

	dfs(1, 0, -INF);
	makeRmq();

	fout << minCost << '\n'; 
	for(int i = 1; i <= q; ++i) {

		int index; 
		fin >> index;
		
		fout << minCost -  (int64_t) solveQuery(index) + (int64_t) edgeQuery[index].d << '\n'; 
	}

	//cout << solveQuery(1) << '\n'; 



}

void print() {

	for(int i = 1; i <= ord[0]; ++i)
		cout << ord[i] << ' ' ;
	cout << '\n'; 

	for(int i = 1; i <= ord[0]; ++i)
		cout << height[i] << ' ' ;
	
	cout << '\n';
}


void solve() {

	sort(edges + 1, edges + 1 + m);
	
	minSpanningTree();
	constructLCA();
	//cout << findLCA(3, 1) << '\n';

/*
	for(int i = 1; i <= q; ++i) {

		int ind;
		fin >> ind;

		if(take[ind] == 1) {
			cout << minCost << '\n'; 
			continue;
		}

		query(edges[i].x , edges[i].y, edges[i].d);
	}

*/
	//print();
}

int main() {

	read();
	solve();
	return 0;
}