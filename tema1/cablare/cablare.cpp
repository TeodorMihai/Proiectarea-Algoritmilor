#include<algorithm>
#include<fstream>
#include<vector>
#include<iostream>

using namespace std;


#define N 102
#define inf 12345678

void scoate_cabluri(int st, int dr, vector< pair<int, int> >& sol, int retine[N][N]) {

	if(st >= dr) return ;


	if(retine[st][dr] == -2)
		return ;//nu am nimic

	if(retine[st][dr] == -1) { //insemna ca am dus cablu 
		sol.push_back(make_pair(st, dr));//bag cablu
		scoate_cabluri(st + 1, dr - 1, sol, retine);//scot cablurile pe intervalul ramas
	}


	//daca nu e nici -1, nici -2, insemna ca ma spart intervalul in 2, retine[st][dr] imi zice
	//unde l-am spart
	scoate_cabluri(st, retine[st][dr], sol, retine); 
	scoate_cabluri(retine[st][dr] + 1, dr, sol, retine);
}

bool cmp(pair<int, int> a , pair<int, int> b) {
	a.first < b.first;
}

int main() {
	
	ifstream fin("cablaj.in");
	ofstream fout("cablaj.out");

	int dp[N][N];//dp[i][j] = costul mnim de calbalre pe intervalul inchis[i, j]
				//cat ma cost sa cablez intervalul incepand cu pinul cu indexul i
				//si terminand cu pinul cu indexul j
	int h[N][N];//inaltimea corespunztoare costului minim pe un interval

	int retine[N][N];//retine[i][j] = -1. daca am cablu de la i la j
					 //retine[i][j] = -2 daca nu am nimic
					//retine[i][j] = x > 0, indexul x reprezinta indexul unde se face o spargere
	
	int i, j, d; int n; char s[N];

	fin >> n;
	n = n * 2 ;

	fin >> s + 1;
 	//de la [1..n] am sirul

 	for(i = 0; i<= n; i++)
 		for(j = 0; j <= n; j++)
 			retine[i][j] = -2;

 	//initial toate intervalele au lungimea infinit, in afara de cele de lungime 1
	for(i = 1;i <= n ; ++i)
		for(j = 1; j <= n; ++j) {
			dp[i][j] = inf; h[i][j] = inf;

			if(j == i + 1 && s[i] != s[j]) {

				h[i][j] = 1;
				dp[i][j] = 3;
				retine[i][j] = -1;
			}
		}

	for(d = 2 ; d < n ; d++) {//calculam toate intervavele de distanta d:
							//ex: [ i , i + d], [i + 1, i + 1 + d] etc
							  //le calculez mai intai pe alea de lungime mica, 
							 //apoi din astea obtin unele de lungime mai mare
		for(i = 1; i <= n; i++) { //iau fiacare interval de lungime d in parte
			//acum analizez practic intervalul : [i , i + d]

			if(i + d > n) continue;//iese afara

			//fie duc cablu pe tot intervalul(de la i la i + d) fie sparg in doua
			//duc cablu de la i  la i + d  si calculez costul
			if(dp[i][i + d] > dp[i + 1][i + d - 1] + (h[i + 1][i + d - 1] + 1) * 2 + d && s[i] != s[i + d]) {
				//(h[i + 1][i + d - 1] + 1) * 2 + d e costul efectiv al cablului, dp[i + 1][i + d - 1] e restul costului
				//deja calculat pentru ca e un interval mai mic

				dp[i][i + d] = dp[i + 1][i + d - 1] + (h[i + 1][i + d - 1] + 1) * 2 + d;
				h[i][i + d] = h[i + 1][i + d - 1] + 1;//am duc cablu peste intervalul [i + 1, i + d - 1], deci actualizezi
													//inaltimea corespunzator
				retine[i][i + d] = -1;//duc cablu deci pun -1, asta e conventia
			}

			for(j = i ; j < i + d; j++) { //punctul in care vrem sa il spargem in doua
				//costul minim pe intervalal[i ,  i + d] poate fi format din costul minim de pe [ i , j] + [ j + 1,i + d]
				//incerc cu fiecare j posibil si il aleg pe cel care imi da costul minim
				if(dp[i][i + d] > dp[i][j] + dp[j + 1][i + d]) {

					dp[i][i + d] = dp[i][j] + dp[j + 1][i + d];
					h[i][i + d] = max(h[i][j] , h[j + 1][i + d]);
					retine[i][i + d] = j;
				}
			}

		}
	}

	fout << dp[1][n] << '\n'; 
	vector< pair<int, int> > sol;

	scoate_cabluri(1, n, sol, retine);

	sort(sol.begin(), sol.end());// cmp);

	for(unsigned i = 0 ; i < sol.size(); ++i)
		fout << sol[i].first << ' ' << sol[i].second << '\n'; 

	return 0;
}