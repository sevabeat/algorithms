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

struct Result{
    bool hasCycle;
    int from = -1;
    int to = -1;
    Result(bool hasCycle, int from, int to) : hasCycle(hasCycle), from(from), to(to){

    }
    Result(bool hasCycle) : hasCycle(hasCycle){

    }
};

Result dfs(TYPE_GRAPH& Graph, std::vector<char>& visited, std::vector<int>& way, int vertex){
    visited[vertex] = 1;
    for(int i = 0; i < Graph[vertex].size(); i++){
        if(visited[Graph[vertex][i]] == 0){
            way[Graph[vertex][i]] = vertex;
            Result res = dfs(Graph, visited, way, Graph[vertex][i]);
            if(res.hasCycle){
                return res;
            }
        }else if(visited[Graph[vertex][i]] == 1){
            return Result(true, Graph[vertex][i], vertex);
        }
    }
    visited[vertex] = 2;
    return Result(false);
}

int main() {
    std::freopen("cycle.in", "r", stdin);
    std::freopen("cycle.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    TYPE_GRAPH Graph(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
    }
    std::vector<char> visited(n, 0);
    std::vector<int> way(n, -1);

    Result res(false);
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            res = dfs(Graph, visited, way, i);
            if(res.hasCycle) break;
        }
    }
    std::vector<int> cycle;
    if(res.hasCycle){
        std::cout << "YES" << std::endl;
        while(res.to != res.from){
            cycle.push_back(res.to);
            res.to = way[res.to];
        }
        cycle.push_back(res.from);
        std::reverse(cycle.begin(), cycle.end());
        for(int i = 0; i < cycle.size(); i++){
            std::cout << (cycle[i] + 1) << " ";
        }
    }else{
        std::cout << "NO" << std::endl;
    }


    return 0;
}

