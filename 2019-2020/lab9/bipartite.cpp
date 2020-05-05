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


bool dfs(TYPE_GRAPH& Graph, std::vector<char>& colors, int vertex, char color){
    colors[vertex] = color;
    for(int child : Graph[vertex]){
        if(colors[child] == 0){
            if(!dfs(Graph, colors, child, (char)(3 - color))){
                return false;
            }
        }else if(colors[child] == color){
            return false;
        }
    }
    return true;
}

int main() {
    std::freopen("bipartite.in", "r", stdin);
    std::freopen("bipartite.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    TYPE_GRAPH Graph(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
        Graph[to - 1].push_back(from - 1);
    }
    std::vector<char> colors(n, 0);

    bool isBipartite = true;
    for(int vertex = 0; vertex < n; vertex++){
        if(colors[vertex] == 0){
            if(!dfs(Graph, colors, vertex, (char)1)){
                isBipartite = false;
                break;
            }
        }
    }
    std::cout << (isBipartite ? "YES" : "NO") << std::endl;
    return 0;
}

