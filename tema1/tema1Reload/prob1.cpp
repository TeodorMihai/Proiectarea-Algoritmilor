#include<stdio.h>
#include<string.h>
#include<algorithm>

#define ASCII 300

int main(int argc, char const *argv[])
{
	
	FILE* in=fopen("joc.in","r");
	FILE* out=fopen("joc.out","w");

	int i,j;

	char s[355]; //un cuvant
	int n;//nr de cuvinte

	fscanf(in, "%d", &n);
	fgets(s, 350, in);

	for(i=1;i<=n;i++)
	{	
		int moves=0;
		fgets(s, 350, in);
		int lung=strlen(s);
		lung--;


		int aparitii[ASCII];

		for(j=0;j<ASCII;j++)//numar aparitiile
			aparitii[j]=0;
		for(j=0;j<lung;j++)
			aparitii[s[j]]++;

		int impare=0;

		for(j=0;j<ASCII;j++)
			if(aparitii[j]%2==1)
				impare++;
		if(impare>1) 
		{
			fprintf(out, "-1\n");
			continue;
		}

		if(impare==1) 
		{
			if(lung%2==0) 
			{
				fprintf(out, "-1\n");
				continue;
			}
		}

		//daca ajung aici insemna ca e ok pot construi un palindrom

		for(j=0;j<lung-j;++j)
		{
			int swaps=0;

			if(aparitii[s[j]]%2==0) 
			{
				//caut perechea lui
				int k;
				for(k=lung-j-1;k>=0;k--) 
				{
					if(s[k]==s[j])
						break;
				}

				int pune=lung-j-1;
				//vrem sa aducem caracterul de pe pozitia k pe pozitia pune
				int demutat = pune - k;
				while(demutat) 
				{
					//schimb s[k] cu s[k+1]
					//caracterul meu e acum pe pozitia k+1, adica k dupa ce incrementez
					//pe k, asta inseamna ca atunci cane pe pozia pune(k==pune), ma opresc
					demutat--;
					std::swap(s[k], s[k + 1]);
					k++;
					swaps++;
				}
			} else {//insemna ca e impar si trebuie sa incerc sa-l caut in sesnul opus

				int k;
				int pune=j;
				char c=s[lung-j-1];//caracterul pe care vrem de fapt sa-l potrivim, cautam cu ce sa potrivim

				for(k=j;k<=lung-j-1;k++)
				{
					if(s[k]==c)
						break;
				}

				//asemanator cu cazul anterior;
				int demutat = k - pune;
				while(demutat) 
				{
					std::swap(s[k], s[k - 1]);
					demutat--;
					k--;
					swaps++;
				}
			}

			moves = moves + swaps;//cate interschimabri am facut pentru caracterul curent
	
		}

		fprintf(out, "%d\n", moves);
	}
	return 0;
}