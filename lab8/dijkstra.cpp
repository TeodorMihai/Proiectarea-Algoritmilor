#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
 
 
using namespace std;
 
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
 
#define pair pair<int, int>
 
const int NMAX = 50000;
const int MMAX = 250000;
const int INF = 0x7fffffff;
 
int n; int m;
 
vector< vector< pair > > g(NMAX + 1, vector< pair >(0) );
 
vector<int> dist(NMAX + 1, INF);
 
void read() {
 
    fin >> n >> m;
 
    for(int i = 1; i <= m ;++i) {
         
        int x; int y; int cost;
        fin >> x >> y >> cost;
        g[x].push_back({y, cost});
    }
}
 
void dijkstra(int source, int dest, vector< vector< pair> >& g) {
 
    priority_queue<pair, vector<pair>, greater<pair> > pq;
 
    dist[source] = 0;
    pq.push({0, source});
 
    while(pq.empty() == false) {
 
        int node = pq.top().second;
        int dst = pq.top().first;   
         
        pq.pop();
 
        if(dist[node] < dst) continue;
 
        for(pair x : g[node]) {
 
            if(dist[node] + x.second < dist[x.first]) {
 
                dist[x.first] = dist[node] + x.second;
                pq.push({dist[x.first], x.first});
            }
        }
    }
}
 
int main() {
 
    read();
 
    /*Complexitate:
    Fiecare muchie poate inbunatati costul => fac push de M ori => M log N
    La fiecare iteratie mai scap de un nod => pop de N ori => N log N
    Nlog N + M log N = MlogN simplificat
    Cu fibonacci heap: M + NlogN, nu te costa pushul, iei mai mult din pop
    */
 
    dijkstra(1, n, g);
 
    for(int i = 2; i <= n ; ++i)
         dist[i] == INF ? fout << 0 << " " : fout <<  dist[i] << " ";
 
    return 0;
}