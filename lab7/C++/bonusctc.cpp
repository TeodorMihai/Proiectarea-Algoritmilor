#include <bits/stdc++.h>

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int NMAX = 10000;


vector<int> g[NMAX];
vector<int> gt[NMAX];

vector< vector<int> > ctc;
int viz[NMAX];

int ord[NMAX];

int cntCtc;
int n; int m;

int compMaxim;

pair<int, int> muc;
int nod1; int nod2;

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {
	
		int x; int y;
		fin >> x >> y;

		g[x].push_back(y);
		gt[y].push_back(x);
	}

}

void sortTop(int x) {

	viz[x] = 1;

	for(int node : g[x]) 
		if(viz[node] == 0)
			sortTop(node);

	ord[++ord[0]] = x;//retin timpul de finzalizarea practic
}

void dfsDag(int x, vector<int>& el) {
	
	el.push_back(x);

	viz[x] = 1;

	for(int node : gt[x]) 
		if(viz[node] == 0)
			dfsDag(node, el);

}

void solve() {

	memset(viz, 0, sizeof(viz));
	ord[0] = 0;

	for(int i = 1; i <= n ; ++i) {	//fac sortare topologica practic pe DGA-ul pe care il obtin
									//nu pe graful propiu zis
		if(viz[i] == 0)
			sortTop(i);
	}

	memset(viz, 0,  sizeof(viz));

	for(int i = ord[0] ; i > 0 ; --i)
		if(viz[ord[i]] == 0) {
			vector<int> el;

			dfsDag(ord[i], el);


			ctc.push_back(el);
		}

	for(int i = 0 ; i < ctc.size(); ++i)
		if(ctc[i].size() > compMaxim) {
			compMaxim = ctc[i].size();
			muc = make_pair(nod1, nod2);
		}
}

void bonus() {

	vector< vector<int> > copyCtc = ctc;



	for(int i = 0 ; i < copyCtc.size(); ++i) {
		
		nod2 = ctc[i][0];

		for(int j = i + 1; j < copyCtc.size(); ++j) {
			
			nod1 = ctc[j][0];
			g[nod1].push_back(nod2);
			gt[nod2].push_back(nod1);

			ctc.clear();	

			solve();

			g[nod1].pop_back();
			g[nod2].pop_back();
		}
	}

	cout << "Muchia maximala : " << muc.first << ' ' << muc.second << '\n';

}

void printCtc() {

	for(int i = 0 ; i < ctc.size(); ++i) {
		for(int x : ctc[i])
			cout << x << ' ';
		cout << '\n'; 
	}
}

int main() {

	read();
	solve();
	printCtc();

	bonus();

	return 0;
}