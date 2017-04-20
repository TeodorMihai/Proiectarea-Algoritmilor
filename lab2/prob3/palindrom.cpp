#include <bits/stdc++.h>

using namespace std;

ifstream fin("palindrom.in");
ofstream fout("palindrom.out");

int c[100]; int L; int total;

int nr1 ; int nr2; int mij1 = 0; int mij2= 0;

int pt = 1;

int getIn(int x) {

	int t = 0;

	while(x ) {

		t = t * 10 + x % 10;
		x /= 10;
		pt *= 10;
	}

	return t;
}


int main() {

	fin >>  L;

	for(int i = 0 ;i <= 9; ++i) {
		fin >> c[i];
		total += c[i];
	}




	int len = total - L;//cat are al doilea

	int have = 1; int ok = 1; int cnt = 0;

	if(len % 2 == 1)
		for(int i = 0 ; i <= 9; ++i)
			if(c[i] % 2 == 1) {
				c[i] -= 1;
				mij1 = i;
				break;
				//len--;
			}

	if(L % 2 == 1)
		for(int i = 0 ; i <= 9; ++i)
			if(c[i] % 2 == 1) {
				c[i] -= 1;
				mij2 = i;
				//L--;
				break;
			}
	
	for(int i = 1; i <= len - L; ++i) {

		while(c[have] <= 1)
			have++;
		
		nr1 = nr1 * 10 + have;
		c[have] -= 2;
		cnt++;
		

		if(ok) {
			have = 0;
			ok = 0;
		}
	}

	//if(len/ 2 == cnt )
	//	nr1 = nr1 * 10 + mij1;

	for(int i = 0 ; i <= 9; ++i)
		cout << c[i] << ' ' ;

	have  = 0;
	nr2 = 0;

	for(int i = 1; i <= L / 2; ++i) {

		while(c[have] <= 1)
			have++;
		cout << have  << '\n'; 



		nr2 = nr2 * 10 + have;
		c[have] -= 2;

		if(cnt < (L/2 - i) ) {
			while(c[have] <= 1)
				have++;
			nr1 = nr1 * 10 + have;
		}



	}
	

	
	if(L % 2 == 1)
		nr2 = nr2 * 10 + mij2;

	pt = 1;
		int invnr2 = getIn(nr2);

		cout << nr2 * pt + invnr2 << '\n'; 


	pt = 1;

	int inv1 = getIn(nr1);


		nr1 = nr1 * 10 + mij1 ;

	cout << nr1 * pt + inv1 << '\n'; 

			

	return 0;
}