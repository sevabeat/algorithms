#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>
#include <climits>
using namespace std;

struct Node{
    int key;
    int left;
    int right;
};
bool isBST(vector<Node>& G, int vertex, int min, int max){
    if(vertex < 0) return true;
    if(G[vertex].key <= min || G[vertex].key >= max) return false;
    return isBST(G, G[vertex].left, min, G[vertex].key) && isBST(G, G[vertex].right, G[vertex].key, max);
}

int main()
{
    ifstream fin("check.in");
    ofstream fout("check.out");
    int n;
    fin >> n;
    vector<Node> G;
    Node vertex;
    int K, L, R;
    for(int i = 0; i < n; i++){
        fin >> vertex.key >> vertex.left >> vertex.right;
        vertex.left--;
        vertex.right--;
        G.push_back(vertex);
    }
    if(n > 2) {
        fout << (isBST(G, 0, INT_MIN, INT_MAX) ? "YES" : "NO");
    }else{
        fout << "YES";
    }
}