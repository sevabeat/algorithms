#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

struct Arrow{
    int vertex;
    int dist;
    Arrow(int to, int dist): vertex(to), dist(dist){};
};

const long long INF = 2e18;

typedef std::vector< std::vector<Arrow> > GRAPH;
typedef std::vector< long long > DIST;
typedef std::vector< char > USED;
void Dijkstra(GRAPH& G, DIST& dist, USED& used, int vertex){
    dist[vertex] = 0;
    for(int i = 0; i < G.size(); i++){
        vertex = -1;
        for(int j = 0; j < G.size(); j++){
            if(!used[j] && (vertex == -1 || dist[j] < dist[vertex])){
                vertex = j;
            }
        }
        if(dist[vertex] == INF) break;
        used[vertex] = true;
        for(int j = 0; j < G[vertex].size(); j++){
            Arrow to = G[vertex][j];
            dist[to.vertex] = std::min(dist[to.vertex], dist[vertex] + to.dist);
        }
    }
}

int main(){
    std::ifstream fin("pathmgep.in");
    std::ofstream fout("pathmgep.out");
    int n, start, finish;
    fin >> n >> start >> finish;
    GRAPH G(n);
    long long dist;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fin >> dist;
            if(dist > 0){
                G[i].push_back(Arrow(j, dist));
            }
        }
    }
    DIST distance(n, INF);
    USED used(n, false);

    Dijkstra(G, distance, used, start - 1);
    if(distance[finish - 1] != INF){
        fout << distance[finish - 1];
    }else{
        fout << -1;
    }
    return 0;
}