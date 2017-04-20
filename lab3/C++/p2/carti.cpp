#include <bits/stdc++.h>

using namespace std;


#define NMax 110

// TODO: adaugare vector/matrice pentru Dinamica

 int d[NMax] ;

int solve( const std::vector<int> & carti ) {


    //d[i] = nr de carti luate maxim, inclusiv cu cartea i;

    d[1] = carti[1];
    
    int maxim = 0;

    for(int i = 2; i <= carti.size() ; ++i) {

        d[i] = maxim + carti[i];

        if(maxim < d[i - 1])
            maxim = d[i - 1];
    }

    return max(d[carti.size()], d[carti.size() - 1]);
}



int main() {

    int N = 0;
    std::vector<int> carti;

    FILE * fin = fopen("carti.in", "r");
    FILE * fout = fopen("carti.out", "w");

    fscanf( fin, "%d", &N );
    carti.resize(N);

    for ( int i = 1; i <= N; ++ i )
        fscanf( fin, "%d\n", &carti[i] );

    fprintf( fout, "%d\n", solve(carti) );

    fclose(fin);
    fclose(fout);

    return 0;
}
