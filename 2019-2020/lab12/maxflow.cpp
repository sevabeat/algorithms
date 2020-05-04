#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>


typedef std::vector<char> VISITED;
typedef std::queue<int> BFS_QUEUE;
typedef std::vector<int> VERTEX_LIST;
typedef std::vector<VERTEX_LIST> NETWORK;

bool FindWay(NETWORK& network, VERTEX_LIST& way, int from, int to){
    BFS_QUEUE bfs_queue;
    VISITED visited(network.size(), false);

    bfs_queue.push(from);
    visited[from] = true;

    way.assign(network.size(), -1);
    while(!bfs_queue.empty()){
        int current_vertex = bfs_queue.front();
        bfs_queue.pop();

        for(int vertex = 0; vertex < network.size(); vertex++){
            if(network[current_vertex][vertex] > 0 && !visited[vertex]){
                visited[vertex] = true;
                bfs_queue.push(vertex);
                way[vertex] = current_vertex;
                if(vertex == to) return true;
            }
        }
    }
    return way[to] >= 0;
}
int MaxFlow(NETWORK& network, int start, int finish){
    VERTEX_LIST way;
    int maxFlow = 0;
    while(FindWay(network, way, start, finish)){
        int flow = INT_MAX;
        for(int to = finish; to != start && to >= 0; to = way[to]){
            flow = std::min(network[way[to]][to], flow);
        }
        for(int to = finish; to != start && to >= 0; to = way[to]){
            network[way[to]][to] -= flow;
            network[to][way[to]] += flow;
        }
        maxFlow += flow;
    }
    return maxFlow;
}

int main(){
    std::ifstream fin("maxflow.in");
    std::ofstream fout("maxflow.out");

    int n, m;
    fin >> n >> m;

    NETWORK network(n, VERTEX_LIST(n, 0));

    int from, to;
    for(int i = 0; i < m; i++){
        fin >> from >> to;
        fin >> network[from - 1][to - 1];
    }
    fin.close();

    fout << MaxFlow(network, 0, n - 1);

    fout.close();
}