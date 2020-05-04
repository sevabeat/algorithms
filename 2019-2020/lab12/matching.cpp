#include <iostream>
#include <fstream>
#include <vector>


/*

😎
SEVASTIAN TRUTNEV
M3101

*/

typedef std::vector<char> VISITED;

typedef std::vector<int> VERTEX_LIST;
typedef std::vector<VERTEX_LIST> GRAPH;


bool dfs(GRAPH& firstLineGraph, VERTEX_LIST& visited, VERTEX_LIST& matching, int vertex) {
    if (visited[vertex]) return false;
    visited[vertex] = true;

    for (int i = 0; i < firstLineGraph[vertex].size(); i++) {
        int to = firstLineGraph[vertex][i];
        if (matching[to] == -1|| dfs(firstLineGraph, visited, matching, matching[to])) {
            matching[to] = vertex;
            return true;
        }
    }
    return false;
}

int FindMatchingCount(GRAPH& firstLineGraph, int secondLineSize){
    VERTEX_LIST matching(secondLineSize, -1);
    VISITED used(firstLineGraph.size(), false);

    for(int i = 0; i < firstLineGraph.size(); i++){
        for(int j = 0; j < firstLineGraph[i].size(); j++){
            if(matching[firstLineGraph[i][j]] < 0){
                matching[firstLineGraph[i][j]] = i;
                used[i] = true;
                break;
            }
        }
    }
    VERTEX_LIST visited;
    for(int i = 0; i < firstLineGraph.size(); i++){
        if(!used[i]){
            visited.assign(firstLineGraph.size(), false);
            dfs(firstLineGraph, visited, matching, i);
        }
    }
    int count = 0;
    for(int i = 0; i < secondLineSize; i++){
        if(matching[i] > -1){
            count++;
        }
    }
    return count;
}

int main(){
    std::ifstream fin("matching.in");
    std::ofstream fout("matching.out");

    int n, m, k;
    fin >> n >> m >> k;
    GRAPH firstLineGraph(n, VERTEX_LIST());

    int from, to;
    for(int i = 0; i < k; i++){
        fin >> from >> to;
        firstLineGraph[from - 1].push_back(to - 1);
    }
    fout << FindMatchingCount(firstLineGraph, m);
    fin.close();
    fout.close();
}