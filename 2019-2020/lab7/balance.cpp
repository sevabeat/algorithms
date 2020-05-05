#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>

using namespace std;

int dfs(vector<pair<int, int>>& Tree, vector<int>& Balance, int vertex, int height){
    if(vertex < 0) return height;
    int leftH = dfs(Tree, Balance, Tree[vertex].first, height + 1);
    int rightH = dfs(Tree, Balance, Tree[vertex].second, height + 1);
    Balance[vertex] = rightH - leftH;
    return max(leftH, rightH);
}

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n;
    fin >> n;
    vector<pair<int, int>> Tree(n);
    vector<int> Balance(n);
    int K;
    for(int i = 0; i < n; i++){
        fin >> K >> Tree[i].first >> Tree[i].second;
        Tree[i].first--;
        Tree[i].second--;
    }
    dfs(Tree, Balance, 0, 0);

    for(int i = 0; i < n; i++){
        fout << Balance[i] << endl;
    }

    return 0;
}