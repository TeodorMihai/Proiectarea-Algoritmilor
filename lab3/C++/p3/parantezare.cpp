#include <stdio.h>
#include <vector>
#include <string.h>
#define LMax 100010

int Len;
char exp[LMax];

int num_words;
size_t words[LMax];

int v[LMax];
//0 = false;
//1 == true;
//2 = and
//3 = or
//4 = xor;

int k;

int d[1000][1000][2];
//1 pt false
//0 pentru true

char * nth_word( char * exp, size_t n ) {
  return exp + words[n];
}

int solv(int st, int dr, int p)  {

    if(d[st][dr][p] != -1)
      return d[st][dr][p];

    if(st > dr)
      return 0;

    if(st == dr) {

      if(v[st] == 1 && p == 1)
        return 1;

      if(v[st] == 0 && p == 0)
        return 1;

      return 0;
    }


    //calculam si pentru p = 0, si pentru p = 1;
    d[st][dr][1] = d[st][dr][0] = 0;  

    for(int mij = st + 1; mij <= dr - 1; ++mij) {

      if(v[mij] == 0 || v[mij] == 1) continue; //adica daca e true sau false

      switch(v[mij]) {

        case 2: d[st][dr][1] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 1);  //and
                d[st][dr][0] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 1);
                d[st][dr][0] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 0);
                d[st][dr][0] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 0); //and
                break;

        case 3: 
                d[st][dr][1] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 0); //or
                d[st][dr][1] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 1);
                d[st][dr][1] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 1);
                d[st][dr][0] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 0);
                break;
        case 4:  
                d[st][dr][1] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 0); //xor
                d[st][dr][1] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 1);
                d[st][dr][0] += solv(st, mij - 1, 1) * solv(mij + 1, dr, 1);
                d[st][dr][0] += solv(st, mij - 1, 0) * solv(mij + 1, dr, 0);

                break;
        default: d[st][dr][0] = 0; d[st][dr][1] = 0; break;
      } 

    }

}

int solve(int v[], int n) {

  return solv(1, n, 1);
}


int get_next(char* exp) {


  while(k < Len && exp[k] == ' ')
    ++k;

  if(k == Len)
    return -1;

  int ret = 0;

  if(exp[k] == 't')
    ret = 1;

  if(exp[k] == 'f')
      ret = 0;

  if(exp[k] == 'o')
    ret =  3;

  if(exp[k] == 'a')
    ret =  2;

  if(exp[k] == 'x')
    ret = 4;

  while(k < Len && ( 'a' <= exp[k] && exp[k] <= 'z') ) ++k;

  return ret;
}


int main() {

  FILE * fin = fopen("parantezare.in", "r");
  FILE * fout = fopen("parantezare.out", "w");

  fgets(exp, LMax, fin);

  Len = strlen(exp);

  int index = 1;
  
  int cnt = 0;
  
  while(k < Len) {
    v[++cnt] =  get_next(exp);
    ++k;
  } 
  
  fprintf( fout, "%d\n", cnt );

  for(int i = 1; i <= cnt; ++i)
      fprintf(fout ,  "%d ", v[i]);


  for(int i = 1; i <= cnt; ++i)
    for(int j = 1; j <= cnt; ++j)
      d[i][j][0] = d[i][j][1] = -1;

  fprintf( fout, "\n%d", solve(v ,cnt) );

  fclose(fin);
  fclose(fout);

  return 0;
}
