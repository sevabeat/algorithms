#include <iostream>
#include <fstream>
#include <vector>

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

const int INF = 1e9;


struct EDGE{
    int from;
    int to;
    int dist;
    EDGE(int from, int to, int dist) : from(from), to(to), dist(dist){};
};

typedef std::vector<int> DIST;
typedef std::vector<EDGE> EDGES;
typedef std::vector <std::vector <int> > MATRIX;

void findDist(DIST& dist, EDGES& edges, int vertex) {

    dist[vertex] = 0;

    for (int i = 0; i < dist.size() - 1; i++) {
        for(int j = 0; j < edges.size(); j++) {
            dist[edges[j].to] = std::min (dist[edges[j].to], dist[edges[j].from] + edges[j].dist);
        }
    }
}


int main() {
    std::ifstream fin("pathsg.in");
    std::ofstream fout("pathsg.out");

    int n, m;
    fin >> n >> m;

    EDGES edges;

    int from, to, dist;
    for (int i = 0; i < m; i++) {
        fin >> from >> to >> dist;
        edges.push_back(EDGE(from - 1, to - 1, dist));
    }
    DIST distance(n, INF);
    MATRIX matrix(n, std::vector <int> (n));
    for (int i = 0; i < n; i++) {
        findDist(distance, edges, i);
        for (int j = 0; j < n; j++) {
            matrix[i][j] = distance[j];
        }
        distance.assign(n, INF);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << matrix[i][j] << " ";
        }
        fout << std::endl;
    }

    return 0;
}