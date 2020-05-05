#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>
using namespace std;

int dfs(vector< pair<int, int> >& G, int vertex, int height){
    if(vertex < 0) return height;
    return max(dfs(G, G[vertex].first, height + 1), dfs(G, G[vertex].second, height + 1));
}

int main()
{
    ifstream fin("height.in");
    ofstream fout("height.out");
    int n;
    fin >> n;
    vector< pair<int, int> > G;

    int K, L, R;
    for(int i = 0; i < n; i++){
        fin >> K >> L >> R;
        G.push_back(make_pair(L - 1, R - 1));
    }
    if(n < 2){
    	fout << n;
    }else{
    	fout << dfs(G, 0, 0);
    }
}