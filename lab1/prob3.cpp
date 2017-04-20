#include <bits/stdc++.h>
//O(N log N)
using namespace std;

ifstream fin("ssm.in");
ofstream fout("ssm.out");

#define pp pair<int, int> 

const int NMAX = 6000009;

int v[NMAX]; int n;

struct subsecventa {

	int bst; int st; int dr;
	subsecventa() {}
	subsecventa(int _bst,int _st, int _dr) : bst(_bst) , st(_st), dr(_dr) { }
} ;


subsecventa findSubs(int st, int dr, int& sum, pair<int, int>& pre, pair<int, int>& post) {


	if(st == dr) {
		if( v[st] < 0 ) {
			pre = make_pair(0, st - 1);
			post = make_pair(0, dr + 1);
		} else  {
			post = make_pair(v[st], st);
			pre = make_pair(v[st], st);
		}

		sum = v[st];
		if(sum < 0)
			return subsecventa(0, st, dr);
		return subsecventa( sum , st, dr );
	}

	int mid = st + (dr - st) / 2;

	int sum1; int sum2 ; pp pre1; pp pre2; pp post1; pp post2;

	subsecventa bst1 = findSubs(st, mid, sum1, pre1, post1);
	subsecventa bst2 = findSubs(mid + 1, dr, sum2, pre2, post2);

	sum = sum1 + sum2;

	if(sum1 + pre2.first < pre1.first)
		pre = pre1;
	else 
		pre = make_pair(sum1 + pre2.first, pre2.second);


	if(post1.first + sum2 < post2.first)
		post = post2;
	else 
		post = make_pair(post1.first + sum2, post1.second);

	subsecventa sol = bst1;

	if(sol.bst < bst2.bst)
		sol = bst2;

	if(sol.bst < pre2.first + post1.first)
		sol = subsecventa(pre2.first + post1.first , post1.second, pre2.second);
	
	return sol;
}

int main() {

	int a; pp b, c;
	fin >> n;	int maxi = 1;

	for(int i = 1; i <= n; ++i) {
		fin >> v[i];
		if(v[i] > v[maxi])
			maxi = i;
	}

	subsecventa sol = findSubs(1, n, a ,b, c);
	if(v[maxi] < 0)
		fout << v[maxi] << ' ' << maxi << ' ' << maxi << '\n';
	else 
		fout << sol.bst << ' ' << sol.st << ' ' << sol.dr << '\n'; 

	return 0;
}