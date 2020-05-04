#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


/*

😎
SEVASTIAN TRUTNEV
M3101

*/

#define NL '\n';

struct Edge{
    int from;
    int to;
    int cap;
    int flow;

    Edge(int from, int to, int cap, int flow)
    : from(from), to(to), cap(cap), flow(flow){}
};


typedef std::vector<char> VISITED;
typedef std::queue <int> BFS_QUEUE;
typedef std::vector<int> VERTEX_LIST;
typedef std::vector<VERTEX_LIST> GRAPH;
typedef std::vector<Edge> EDGES;

bool bfs(GRAPH& graph, EDGES& edges, VERTEX_LIST& levels, int start, int finish){
    levels.assign(levels.size(), 0);
    BFS_QUEUE bfs_queue;

    bfs_queue.push(start);
    levels[start] = 1;

    while (!bfs_queue.empty() && !levels[finish]){
        int current = bfs_queue.front();
        bfs_queue.pop();

        for (auto & to : graph[current]){
            if (edges[to].cap - edges[to].flow > 0){
                if (!levels[edges[to].to]){
                    bfs_queue.push(edges[to].to);
                    levels[edges[to].to] = levels[current] + 1;
                }
            }
        }
    }
    return levels[finish];
}


int dfs(GRAPH& graph, EDGES& edges, VERTEX_LIST& levels, VERTEX_LIST& ptr, int minFlow, int pointer, int finish){
    if (minFlow == 0) return 0;

    if (finish == pointer) return minFlow;

    for (; ptr[pointer] < graph[pointer].size(); ptr[pointer]++){
        Edge& to = edges[graph[pointer][ptr[pointer]]];
        int from = pointer;
        int levels_to = levels[to.to];
        int levels_from = levels[from];
        if (levels_to == levels_from + 1){
            int pushed = dfs(graph, edges, levels, ptr, std::min(minFlow, to.cap - to.flow), to.to, finish);
            if (pushed){
                edges[graph[pointer][ptr[pointer]]].flow += pushed;
                edges[graph[pointer][ptr[pointer]] ^ 1].flow -= pushed;
                return pushed;
            }
        }
    }

    return 0;
}

void add(GRAPH& graph, EDGES& edges, int from, int to, int cap) {
    graph[from].push_back(edges.size());
    edges.emplace_back(Edge(from, to, cap, 0));
    graph[to].push_back(edges.size());
    edges.emplace_back(Edge(to, from, 0, 0));
}

int main() {
    std::ifstream fin("circulation.in");
    std::ofstream fout("circulation.out");
    int n, m;
    fin >> n >> m;
    n += 2;
    GRAPH graph(n, VERTEX_LIST());
    EDGES edges;

    VERTEX_LIST levels(n, 0);
    VERTEX_LIST ptr(n, 0);

    for (int i = 0; i < m; i++) {
        int from, to, lowFlow, highFlow;
        fin >> from >> to >> lowFlow >> highFlow;
        add(graph, edges,0, to, lowFlow);
        add(graph, edges, from, to, highFlow - lowFlow);
        add(graph, edges, from, n - 1, lowFlow);
    }
    while (bfs(graph, edges, levels, 0, n - 1)){
        while(dfs(graph, edges, levels, ptr, INT_MAX, 0, n - 1));
        ptr.assign(n, 0);
    }
    for (int edge : graph[0]) {
        if (edges[edge].flow < edges[edge].cap) {
            fout << "NO" << NL;
            return 0;
        }
    }
    fout << "YES" << NL;
    for (int i = 0; i < edges.size(); i += 6)
        fout << edges[i + 2].flow + edges[i + 4].flow << NL;
    return 0;
}