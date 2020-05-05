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
    int n;
    fin >> n;
    vector< vector<bool> > G(n);
    bool buffer;
    for(int i = 0; i < n; i++){
        G[i].resize(n);
        for(int j = 0; j < n; j++){
            fin >> buffer;
            G[i][j] = buffer;
        }
    }
    bool isSimple = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if((G[i][j] && !G[j][i]) || (i == j && G[i][j])){
                isSimple = false;
                break;
            }
        }
    }
    if(isSimple){
        fout << "YES" << NL;
    }else{
        fout << "NO" << NL;
    }

    return 0;
}

