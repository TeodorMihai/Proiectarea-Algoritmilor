#include <bits/stdc++.h>


using namespace std;

struct subject {

  int index;
  string name;
  vector<subject *> before;

  subject(int _index, string _name)
    : index(_index)
    , name(_name) {}

};

vector<subject> subjects;


int ord[100];
int viz[100];
int in[100];


void dfs(int x) {

	viz[x] = 1;

	for(unsigned i = 0 ; i < subjects[x].before.size(); ++i) {

		subject s = *subjects[x].before[i];
		if(viz[s.index] == 0)
			dfs(s.index);
	}

	ord[++ord[0]] = x;
}

int get_index( string & name ) {

  for ( int i = 0; i < (int) subjects.size(); ++ i )
    if ( subjects[i].name == name )
      return i;

  int index = subjects.size();

  subjects.push_back( subject(index, name) );
  return subjects.size() - 1;
}

void add( string &first, string &second ) {

  int index_first = get_index(first);
  int index_second = get_index(second);

  subjects[index_first].before.push_back( &subjects[index_second] );
}

void solve( vector<subject> & subjects, vector<subject> & sol ) {

  	for(unsigned i = 0 ; i < subjects.size() ; i++)
  		if(viz[i] == 0)
  			dfs(i);

  	for(int i = ord[0] ; i > 0; --i)
  		sol.push_back(subjects[ord[i]]);
}

void solveKhan( vector<subject> & subjects, vector<subject> & sol ) {

    for(unsigned i = 0 ; i < subjects.size(); ++i)
      for(auto s : subjects[i].before)
        in[s->index]++;

  int ok = 1;
  int viz[200];

  memset(viz, 0,sizeof(viz));

  while(ok) {
    
    ok = 0;


    for(unsigned i = 0 ; i < subjects.size(); ++i)
      if(in[i] == 0 && viz[i] == 0) {
        viz[i] = 1;
        ok = 1;
        sol.push_back(subjects[i]);

        for(auto s : subjects[i].before)
          in[s->index]--;
      }
  }
  
}


int main() {

  ifstream fin("sort.in");
  ofstream fout("sort.out");

  string line;

  assert(fin.is_open());
  assert(fout.is_open());

  int subjectsNum;
  fin >> subjectsNum;
  subjects.reserve(subjectsNum);
  
  while ( getline( fin, line ) ) {

    size_t pos = line.find("->");

    if ( pos == string::npos )
      continue;


    string first = line.substr(0, pos - 1);
    string second = line.substr(pos + 3);

    add( first, second );

  }

  vector<subject> sol;
  solve( subjects, sol );

  for ( int i = 0; i < (int) sol.size(); ++ i )
    cout << sol[i].name << endl;

  return 0;
}
