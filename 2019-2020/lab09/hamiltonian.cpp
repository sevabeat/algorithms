#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

typedef std::vector< std::vector<int> > TYPE_GRAPH;


void dfs(TYPE_GRAPH& Graph, std::vector<char>& visited, std::stack<int>& way, int vertex){
    visited[vertex] = 1;
    for(int child : Graph[vertex]){
        if(visited[child] == 0){
            dfs(Graph, visited, way, child);
        }
    }
    way.push(vertex);
}

int main() {
    std::freopen("hamiltonian.in", "r", stdin);
    std::freopen("hamiltonian.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    TYPE_GRAPH Graph(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
    }

    std::vector<char> visited(n, 0);
    std::stack<int> way;

    for(int vertex = 0; vertex < n; vertex++){
        if(visited[vertex] == 0){
            dfs(Graph, visited, way, vertex);
        }
    }
    bool isHamilton = false;
    int now, last;
    if(!way.empty()){
        isHamilton = true;
        last = way.top();
        way.pop();
    }
    while(isHamilton && !way.empty()){
        now = way.top();
        way.pop();
        isHamilton = false;
        for(int child : Graph[last]){
            if(child == now){
                isHamilton = true;
                break;
            }
        }
        last = now;
    }
    std::cout << (isHamilton ? "YES" : "NO") << std::endl;
    return 0;
}
