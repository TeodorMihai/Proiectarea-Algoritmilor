#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

struct material {

  float weight;
  float value;

  material ( float weight, float value ) : weight(weight)
                                         , value(value) {}

  // functie de comparare folosita la sortare
  bool operator < ( const material & other ) const {
    return value / weight < other.value / other.weight;
  }

};


float solve ( float max_weight, std::vector<material> & materiale) {

  // TODO

}

int main() {

  int n;
  float max_weight;
  std::vector<material> materiale;
  
  FILE * fin = fopen("knapsack.in", "r");
  FILE * fout = fopen("knapsack.out", "w");

  assert( fscanf( fin, "%d%f", &n, & max_weight ) == 2);

  for ( int i = 1; i <= n; ++ i ) {
    float weight;
    float value;

    assert( fscanf( fin, "%f%f", & weight, & value ) == 2 );
    materiale.push_back(material(weight, value));

  }

  fprintf( fout, "%f\n", solve( max_weight, materiale ) );

  fclose(fin);
  fclose(fout);

  return 0;
}
