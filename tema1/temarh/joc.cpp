#include <bits/stdc++.h>

using namespace std;

ifstream fin("joc.in");
ofstream fout("joc.out");

const int NMAX = 1000;
const int MMAX = 350;
const int ALPHABET = 150;

int n; int m;

char v[MMAX + 1];



int getRightMost(char x, int start) {

	for(int i = start; i >= 0; --i)
		if(x == v[i])
			return i;
	return -1;
}

int getLeftMost(char x, int start) {


	for(int i = start; i < m; ++i)
		if(x == v[i])
			return i;
	return -1;
}

void solve() {

	int odd = 0;
	int cnt = 0;

	char oddChar = 0;

	int freq[ALPHABET];

	for(int i = 0 ; i < ALPHABET; ++i)
		freq[i] = 0;

	for(int i = 0 ; i < m ; ++i) 
		freq[v[i]]++;	

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

			//do inverse right -> left

			int ind = getLeftMost( v[right], left);

			for( ; ind != left ; ind--, cnt++) 
				swap(v[ind], v[ind - 1]);

			v[right] -= 2;

		}  else {

				int ind = getRightMost(v[left], right );

				for( ; ind != right ; ind++, cnt++) 
					swap(v[ind], v[ind + 1]);
				
				freq[v[i]] -= 2;
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

