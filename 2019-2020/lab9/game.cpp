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


void dfs(TYPE_GRAPH& Graph, std::vector<char>& visited, std::vector<char>& positionType, int vertex){
    visited[vertex] = 1;
    for(int child : Graph[vertex]){
        if(visited[child] == 0){
            dfs(Graph, visited, positionType, child);
        }
        if(positionType[child] == 0){
            positionType[vertex] = 1;
        }
    }
}

int main() {
    std::freopen("game.in", "r", stdin);
    std::freopen("game.out", "w", stdout);
    int n, m, s;
    std::cin >> n >> m >> s;
    TYPE_GRAPH Graph(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
    }

    std::vector<char> visited(n, 0);
    std::vector<char> positionType(n, 0);

    for(int vertex = 0; vertex < n; vertex++){
        if(visited[vertex] == 0){
            dfs(Graph, visited, positionType, vertex);
        }
    }

    std::cout << (positionType[s - 1] == 1 ? "First player wins" : "Second player wins") << std::endl;


    return 0;
}
