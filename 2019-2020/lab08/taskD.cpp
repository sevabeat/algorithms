#include <iostream>
#include <vector>
#include <fstream>
 
using namespace std;

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

 
ifstream fin("components.in");
ofstream fout("components.out");
 
#define NL '\n';
 
typedef vector< vector<int> > GRAPH;
 
void dfs(GRAPH& G, vector<int>& comps, int vertex, int comp){
    if(comps[vertex] > 0) return;
    comps[vertex] = comp;
    for(int i = 0; i < G[vertex].size(); i++){
        dfs(G, comps, G[vertex][i], comp);
    }
}
 
int main() {
    int n, m;
    fin >> n >> m;
 
    GRAPH G(n);
    vector<int> comps(n, 0);
 
    int a, b;
    for(int i = 0; i < m; i++){
        fin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int nowComp = 0;
    for(int i = 0; i < n; i++){
        if(comps[i] == 0){
            nowComp++;
            dfs(G, comps, i, nowComp);
        }
    }
     
    fout << nowComp << NL;
    for(int i = 0; i < n; i++){
        fout << comps[i] << " ";
    }
 
    return 0;
}