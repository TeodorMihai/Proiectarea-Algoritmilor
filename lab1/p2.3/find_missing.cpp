#include <bits/stdc++.h>
#include "vector_io.h"

using namespace std;
int part(int st, int dr, vector<int>& v) {

	if(st >= dr) return st;

	int p = dr;

	int ind = st - 1;

	//partitonare, pana la dr, fara el
	for(int i = st ; i <= dr - 1; ++i) {
		if(v[i] < v[dr]) {
			swap(v[++ind], v[i]);
		}
	}

	swap(v[p], v[ind + 1]);

	//p - ule  pe pozitia finala care trebuie acum

	if(v[p] != p) //probleme la stanga
		part(1, p - 1, v);
	else 
		part(p + 1, dr, v);


} 

int find_missing(std::vector<int> v)
{	

    return part(0, v.size(), v);
}

int main(void)
{
    std::ifstream f("date.in");
    std::vector<int> v1, v2;
    f >> v1;
    f >> v2;
    std::cout << find_missing(v1) << std::endl;
    std::cout << find_missing(v2) << std::endl;
    f.close();
}
