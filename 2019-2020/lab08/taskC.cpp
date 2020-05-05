#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/


ifstream fin("input.txt");
ofstream fout("output.txt");

#define NL '\n';

int main() {
    int n, m;
    fin >> n >> m;
    vector< vector<bool> > G(n);
    for(int i = 0; i < n; i++){
        G[i].resize(n);
    }
    int a, b;
    bool hasParallel = false;
    for(int i = 0; i < m; i++){
        fin >> a >> b;
        a--; b--;
        if(G[b][a] || G[a][b]){
            hasParallel = true;
            break;
        }
        G[a][b] = true;
    }
    if(hasParallel){
        fout << "YES" << NL;
    }else{
        fout << "NO" << NL;
    }

    return 0;
}

