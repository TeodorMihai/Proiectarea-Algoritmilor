#include<cstdio>

#define VAR 617
#define M 1211
#define N 1211
#define ASCII 277

int min1(int x, int y) {

	if(x > y)
		return y;
	
	return x;
}

int max1(int x, int y) {

	if(x < y)
		return y;
	
	return x;
}


int aparitii[ASCII][M];

int main(int argc, char const *argv[])
{

	FILE* in=fopen("evaluare.in","r");
	FILE* out=fopen("evaluare.out","w");

	int nrvar, n, m;int i, j; int nr;
	fscanf(in, "%d %d", &nrvar, &n);

	//cate aparitii are ascii in coloana M
	
	//dinamica = minimul cu care pot obtine din vectorii pana la N, vectorul pana la M
	//vectorul pe care vrem sa il "potrivim"
	int B[N][M], V[M];

	for(i=1;i<=nrvar;i++)
		for(j=1;j<=n;j++) 
		{
			fscanf(in,"%d",&nr);
			aparitii[nr][j]++;//suntem pe coloana j
		}
	fscanf(in, "%d",&m);

	for(i=1;i<=m;i++)
	{
		fscanf(in, "%d", &V[i]);
	}
	
	//initializam, cazurile de baza

	for(i=0;i<=max1(n, m);i++)
	{	
		B[i][0]=i;//pentru ca trebuie practic sa inseram fiecare numar in al doilea vector,
					//care la inceput e gol, simetric la stergere
		B[0][i]=i;
	}

	
	
	for(i=1;i<=n;i++)
		for(j=1;j<=m;++j)//nu mai tratez cazurile de baza, le-am tratat deja, cele cu indexarea de la 0
		{
			int cost;
			if(aparitii[V[j]][i]) //daca elementul pe care vrem sa-l bagam acum(V[j])
			{					//se afla pe linia i a sirului, atunci putem folosi
								//sirul pana la j din sirul pana la i, folosind sirul pana la j - 1
								//construit din sirul pana la i - 1 + caracterul de pe poz i, respectiv j
				cost = B[i - 1][j - 1];

			} else 	{			//altfel nu putem si asta e practic costul de schimbare a caracterului de p
								//pe pozitia j cu un caracter de pe pozitia i
				cost = B[i - 1][j - 1] + 1;
			}

			//putem insa forma sirul (i, j) din sirul(i, j - 1) (avand un cost de transformare a unuia
			//in altul +  inserand caracterul pe pozitia j,1 e costul de inserare
			//la fel si la stergere
			cost = min1(B[i][j - 1] + 1, min1(cost, B[i - 1][j] + 1) );
			B[i][j] = cost;
		}	

	fprintf(out, "%d\n",B[n][m]);

	return 0;
}