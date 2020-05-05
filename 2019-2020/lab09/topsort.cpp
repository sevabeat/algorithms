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


bool dfs(TYPE_GRAPH& Graph, std::vector<char>& visited, std::vector<int>& sort, int vertex){
    visited[vertex] = 1;
    for(int i = 0; i < Graph[vertex].size(); i++){
        if(visited[Graph[vertex][i]] == 0){
            if(!dfs(Graph, visited, sort, Graph[vertex][i])){
                return false;
            }
        }else if(visited[Graph[vertex][i]] == 1){
            return false;
        }
    }
    sort.push_back(vertex);
    visited[vertex] = 2;
    return true;
}

int main() {
    std::freopen("topsort.in", "r", stdin);
    std::freopen("topsort.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    TYPE_GRAPH Graph(n);
    int from, to;
    for(int i = 0; i < m; i++){
        std::cin >> from >> to;
        Graph[from - 1].push_back(to - 1);
    }
    std::vector<char> visited(n, 0);
    std::vector<int> sort;

    bool res = true;
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            res = dfs(Graph, visited, sort, i);
            if(!res) break;
        }
    }

    if(res){
        for(int i = sort.size() - 1; i >= 0; i--){
            std::cout << (sort[i] + 1) << " ";
        }
    }else{
        std::cout << "-1" << std::endl;
    }
    return 0;
}

