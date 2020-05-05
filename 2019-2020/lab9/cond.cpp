#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

typedef std::vector< std::vector<int> > TYPE_GRAPH;


void dfs1(TYPE_GRAPH& Graph, std::vector<char>& visited, std::vector<int>& order, int vertex){
    visited[vertex] = 1;
    for(int child : Graph[vertex]){
        if(visited[child] == 0){
            dfs1(Graph, visited, order, child);
        }
    }
    order.push_back(vertex);
}

void dfs2(TYPE_GRAPH& Graph, std::vector<int>& comps, int vertex, int nowComp){
    comps[vertex] = nowComp;
    for(int child : Graph[vertex]){
        if(comps[child] == 0){
            dfs2(Graph, comps, child, nowComp);
        }
    }
}
int main() {
    std::freopen("cond.in", "r", stdin);
    std::freopen("cond.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    TYPE_GRAPH Graph(n);
    TYPE_GRAPH Graph_r(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
        Graph_r[to - 1].push_back(from - 1);
    }

    std::vector<char> visited(n, 0);
    std::vector<int> order;
    std::vector<int> comps(n, 0);

    for(int vertex = 0; vertex < n; vertex++){
        if(visited[vertex] == 0){
            dfs1(Graph, visited, order, vertex);
        }
    }
    int comp = 0;
    for(int i = order.size() - 1; i >= 0; i--){
        if(comps[order[i]] == 0){
            comp++;
            dfs2(Graph_r, comps, order[i], comp);
        }
    }
    std::cout << comp << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << comps[i] << " ";
    }
    return 0;
}
