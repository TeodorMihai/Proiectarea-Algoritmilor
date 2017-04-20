#include <stdio.h>
#include <string.h>
#define Nmax 106
 
char s[Nmax];
int use[30];
int t;
 
int solve(){
    int n,i,j,k,nr=0,pmij,z,ok=0,oks,okf,aux;
    memset(s,0,sizeof(s));
      memset(use,0,sizeof(use));
    fgets(s,Nmax,stdin);
      n=strlen(s);
      if(s[n-1]=='\n') n--;
 
      for(i=0;i<n;++i) use[s[i]-'a']++;
      for(i=0;i<=26;++i)
        if( (use[i] & 1) && ok) return -1;
        else if(use[i] & 1) ok=1,pmij=i;
 
      z=n-1; 
      i=0; oks=1; okf=0;
      while( ( oks && i<=n/2) || (okf && i>=n/2) ){
         if(s[z] != s[i])
           if(oks){
            for(j=z; j>i;j--)
               if(s[j]==s[i]){
                nr += z-j;
                  for(k=j+1;k<=z;++k) s[k-1]=s[k];
                  s[z]=s[i];
                   break;
               }
             if(j==i){ // am ajuns la mijloc
                oks=0; okf=1;
                  aux=z; z=i-1; i=aux+1;
             }
           }
           else
             for(j=z;j<i;j++)
               if(s[j]==s[i]){
                nr += j-z;
                  for(k=j;k>z;k--) s[k]=s[k-1];
                  s[z]=s[i];
                  break;
               }
         if(oks)z--,i++; else z++,i--;
      }
      return nr;
}
 
int main(){
    freopen("palind.in","r",stdin);
   freopen("palind.out","w",stdout);
   scanf("%d\n",&t);
 
   for(; t; --t)
    printf("%d\n",solve());
       
   fclose(stdin); fclose(stdout);
   return 0;
}