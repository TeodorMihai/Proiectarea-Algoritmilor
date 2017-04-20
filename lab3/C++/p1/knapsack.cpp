//TODO

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000;

ifstream fin("date.in");
ofstream fout("date.out");

int h[NMAX];//h[i] = valoarea maxima pe care pot sa am cu greutatea g
int last[NMAX]; //last[i]ultimul eleemnt bagat in rucsac, ca sa obtin cel mai bun cost cu greutatea i
int v[100];
int g[100];

int main() {

	int T;
	int n;

	set<int> x[NMAX];

	fin >> n >> T;

	for(int i = 1; i <= n ; ++i)
		fin >> g[i] >> v[i];

	//h[0] = 0;

	for(int i = 1; i <= n ; ++i) {



		for(int j = T - g[i]; j >= 0; --j) {
			
			if(h[j + g[i]] < h[j] + v[i]) {
				h[j + g[i]] = h[j] + v[i];

				for(int p : x[j])
					x[j + g[i]].insert(p);

				x[j + g[i]].insert(i);
			}
		}

		for(int j = T; j >= 0 ; --j)
			cout << h[j] << ' ';
		cout << '\n'; 
	}	

	int maxim = 0;

	for(int i = T; i >= 0 ; --i)
		maxim = max(maxim, h[i]);

	for(int i = T; i >= 0; --i)
		if(h[i] == maxim) {
			fout << maxim << '\n'; 
			
			for(int k : x[maxim])
				fout << k << ' ';
			break;
		}


	return 0;
}
