#include <bits/stdc++.h>

using namespace std;

ifstream fin("rucsac.in");
ofstream fout("rucsac.out");


int t; int n;

struct Material{

	int val; int w;
} ;

Material v[100];



bool comp(Material a, Material b) {

	return ((double )a.val / a.w) > ((double)b.val / b.w);
}

int main() {

	fin >> n >> t;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i].val >> v[i].w;

	sort(v + 1, v + 1 + n, comp); 

	for(int i = 1; i <= n ; ++i) {

		fout << v[i].w << ' ' << v[i].val << '\n'; 
	}

	double total = 0;

	for(int i = 1 ; i <= n ; ++i) {

		if(t >= v[i].w) {
			total += v[i].val;
			t -= v[i].w;

		} else {

			total += ((double)  t / v[i].w) * v[i].val; 
			break;
		}
	}



	fout << total << '\n'; 




	return 0;
}