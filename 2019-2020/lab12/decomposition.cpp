#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>


/*

😎
SEVASTIAN TRUTNEV
M3101

*/

#define NL '\n';

struct Edge{
    int to;
    int cap;
    int flow;
    int num;

    Edge(int to, int cap, int flow, int num)
    : to(to), cap(cap), flow(flow), num(num){}
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


int showPaths(GRAPH& graph, EDGES& edges, GRAPH& paths, int pointer, int flowValue, int start, int finish){
    if (pointer == finish){
        paths.emplace_back();
        return flowValue;
    }
    for (auto & to : graph[pointer]){
        if (edges[to].flow > 0){
            int flow = showPaths(graph, edges, paths, edges[to].to,
                                  std::min(flowValue, edges[to].flow), start, finish);
            if (flow){
                paths.back().push_back(edges[to].num);
                if (pointer == start){
                    paths.back().push_back(paths[paths.size() - 1].size());
                    paths.back().push_back(flow);
                    std::reverse(paths.back().begin(), paths.back().end());
                }
                edges[to].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

int main(){
    std::ifstream fin ("decomposition.in");
    std::ofstream fout ("decomposition.out");

    int n, m;
    fin >> n >> m;

    GRAPH graph(n, VERTEX_LIST());
    EDGES edges;

    VERTEX_LIST levels(n, 0);
    VERTEX_LIST ptr(n, 0);

    int from, to, weight;
    for (int i = 0; i < m; i++){
        fin >> from >> to >> weight;
        graph[from - 1].push_back(edges.size());
        edges.push_back(Edge(to - 1, weight, 0, i + 1));
        graph[to - 1].push_back(edges.size());
        edges.push_back(Edge(from - 1, 0, 0, i + 1));
    }

    while (bfs(graph, edges, levels, 0, n - 1)){
        while(dfs(graph, edges, levels, ptr, INT_MAX, 0, n - 1));
        ptr.assign(n, 0);
    }
    GRAPH paths;
    while (showPaths(graph, edges, paths, 0, INT_MAX, 0, n - 1));

    std::cout << paths.size() << NL;

    for(int i = 0; i < paths.size(); i++){
        for(int j = 0; j < paths[i].size(); j++){
            std::cout << paths[i][j] << " ";
        }
        std::cout << NL;
    }

    fin.close();
    fout.close();

    return 0;
}