#include <bits/stdc++.h>

using namespace std;

#define NMax 1010

int N, M, start_line, start_col;
int Mat[NMax][NMax];
//0 ok
//1 obstacol
//2 iesire


  FILE * fin = fopen("labirint.in", "r");
  FILE * fout = fopen("labirint.out", "w");

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int dist[NMax][NMax];

void getSol(int x, int y) {

  if(dist[x][y] == 0) {
    fprintf(fout, "%d %d\n", x , y );
    return ;
  }

  for(int k = 0 ; k < 4; ++k) {

    int px = x + dx[k];
    int py = y + dy[k];
    if(px == 0 || py == 0 || px == N + 1|| py == N + 1) continue;

    if(dist[px][py] == dist[x][y] - 1) {
      getSol(px, py);
      fprintf(fout, "%d %d\n", x, y);

      return ;
    }
  }
}

pair<int, int> solve() {

  queue< pair<int, int> > q;

  q.push({start_line, start_col});

  while(!q.empty()) {

      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      for(int k = 0 ; k < 4; ++k) {

        int px = x + dx[k];
        int py = y + dy[k];

        if(px == 0 || px == N + 1 || py == 0 || py == N + 1)
          continue;

        if(Mat[px][py] == 1)  continue; //blocat

        if(dist[px][py] != -1)  continue;

        if(Mat[px][py] == 0) {    //liber

          q.push({px, py});
          dist[px][py] = dist[x][y] + 1;
        }

        if(Mat[px][py] == 2) {

          dist[px][py] = dist[x][y] + 1;
          return make_pair(px, py);

        }

      }
  }   

  return pair<int, int> (-1, -1);

}

int main() {

  assert(fin != NULL);
  assert(fout != NULL);

  assert(fscanf( fin, "%d%d%d%d", &N, &M, &start_line, &start_col ) == 4);

  for ( int i = 1; i <= N; ++ i )
    for ( int j = 1; j <= N; ++ j ) {
      assert(fscanf( fin, "%d\n", & Mat[i][j]) == 1);
      dist[i][j] = -1;
    }

  dist[start_line][start_col] = 0;

  pair<int, int> p = solve();
  fprintf(fout, "%d\n", dist[p.first][p.second]);
  getSol(p.first, p.second);
  return 0;
}
