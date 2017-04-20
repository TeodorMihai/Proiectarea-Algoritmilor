#include <bits/stdc++.h>

using namespace std;

int v[] = {1, 2, 3, 3, 3, 4,5, 5, 6, 7, 8, 11, 12, 13};

int n = 14;

int lowerB(int x) {//returnewaza primul element egal cu valoarea noastra, -1 altfel;

	int pos = 0; int step;

	for(step = 1; step <= n; step <<= 1);

	for(pos = 0 ; step ; step >>= 1)
		if(pos + step <= n and v[pos + step] < x)
			pos += step;
	return (v[pos + 1] == x) ? pos + 1 : -1;
}

int upperB(int x) {//returnewaza ultimul element egal cu valoarea noastra, -1 altfel;

	int pos = 0; int step;

	for(step = 1; step <= n; step <<= 1);

	for(pos = 0 ; step ; step >>= 1)
		if(pos + step <= n and v[pos + step] <= x)
			pos += step;

	return (v[pos] == x) ? pos : -1;
}

int find(int val, int* v) {

	int lo = lowerB(val);
	int up = upperB(val);

	if(up == -1) return 0;
	else return up - lo + 1;

}

int main() {

	cout << find(3, v) << '\n'; 	
	cout << find(5, v) << '\n';
	cout << find(12, v) << '\n';

	cout << find(9, v) << '\n'; 	
	return 0;
}