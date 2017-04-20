#include <bits/stdc++.h>

using namespace std;

bool check[2000];

struct tema {

  int deadline;
  int points;

  tema( int deadline, int points ) : deadline(deadline)
                                   , points(points) {}

  bool operator < ( const tema & other ) const {
    return points > other.points ||
           ( points == other.points && deadline < other.deadline );
  }

};

int solve( std::vector<tema> & teme ) {

  
  sort(teme.begin(), teme.end());//sortez dupa puncte

  int total = 0;

  for(int i = 0 ; i < teme.size(); ++i) {

      int x = teme[i].deadline;
      while(x >= 0 && check[x] == 1)  --x;

      if(x == 0) continue;


        total += teme[i].points;
        check[x] = 1;
     }

  return total;
}

int main() {

  int n;

  FILE * fin = fopen("planificare.in", "r");
  FILE * fout = fopen("planificare.out", "w");

  std::vector<tema> teme;

  assert ( fscanf( fin, "%d", & n ) == 1 );


  for ( int i = 1 ; i <= n; ++ i ) {

    int deadline;
    int points;

    assert ( fscanf( fin, "%d%d", & deadline, & points ) == 2 );
    teme.push_back( tema(deadline, points));

  }

  fprintf( fout, "%d\n", solve( teme ) );

  return 0;
}
