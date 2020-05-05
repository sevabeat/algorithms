#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

struct Arrow{
    int to;
    int dist;
    Arrow(int to, int dist): to(to), dist(dist){};
};
typedef std::vector< std::vector<Arrow> > GRAPH;
typedef std::vector<char> USED;
typedef std::vector<long long> DIST;
typedef std::set< std::pair <int, long long> > QUEUE;

const long long INF = 2e18;


void Dijkstra (GRAPH& G, DIST& dist, QUEUE& q, int vertex) {
    dist[vertex] = 0;
    q.insert(std::make_pair(vertex, 0));
    while (!q.empty()) {
        vertex = q.begin()->first;
        q.erase(q.begin());
        for (int j = 0; j < G[vertex].size(); j++) {
            Arrow n_v = G[vertex][j];
            if (dist[n_v.to] > dist[vertex] + n_v.dist) {
                q.erase(std::make_pair(n_v.to, dist[n_v.to]));
                dist[n_v.to] = dist[vertex] + n_v.dist;
                q.insert(std::make_pair(n_v.to, dist[n_v.to]));
            }
        }
    }
}


int main () {
    std::ifstream fin("pathbgep.in");
    std::ofstream fout("pathbgep.out");

    int n, m;

    fin >> n >> m;

    GRAPH G(n);

    int from, to, dist;
    for (int i = 0; i < m; i++) {
        fin >> from >> to >> dist;

        G[from - 1].push_back(Arrow(to - 1, dist));
        G[to - 1].push_back(Arrow(from - 1, dist));
    }
    USED used(n, false);
    DIST distance(n, INF);
    QUEUE q;


    Dijkstra(G, distance, q, 0);

    for (int i = 0; i < n; i++) {
        fout << distance[i] << " ";
    }

    return 0;
}