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

int main() {
    int n, m;
    fin >> n >> m;
    vector<vector<bool>> G(n);
    for(int i = 0; i < n; i++){
        G[i].resize(n);
    }
    int a, b;
    for(int i = 0; i < m; i++){
        fin >> a >> b;
        G[a - 1][b - 1] = true;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fout << G[i][j] << " ";
        }
        fout << endl;
    }
    return 0;
}

