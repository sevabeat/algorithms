#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/


ifstream fin("pathbge1.in");
ofstream fout("pathbge1.out");

#define NL '\n';
typedef vector< vector<int> > GRAPH;

int main() {
    int n, m;
    fin >> n >> m;

    GRAPH G(n);

    int a, b;
    for(int i = 0; i < m; i++){
        fin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<int> Distance(n, 0);
    vector<bool> visited(n, false);
    queue<int> BFS;

    BFS.push(0);
    visited[0] = true;
    int vertex;
    while(!BFS.empty()){
        vertex = BFS.front();
        BFS.pop();
        for(int i = 0; i < G[vertex].size(); i++){
            if(!visited[G[vertex][i]]){
                Distance[G[vertex][i]] = Distance[vertex] + 1;
                visited[G[vertex][i]] = true;
                BFS.push(G[vertex][i]);
            }
        }
    }
    for(int i = 0; i < n; i++){
        fout << Distance[i] << " ";
    }
    return 0;
}

