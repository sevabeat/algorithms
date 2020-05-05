// Example program
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int n, m;
int matrix[1000][1000];
int dp[1000][1000];


int f(int i, int j, int w){
    if(i < 0 || i > n - 1 || j < 0 || j > m - 1) return 0;

    if(matrix[i][j] + w > dp[i][j] || (i == n - 1 && j == 0)){
        dp[i][j] = matrix[i][j] + w;
        f(i, j + 1, dp[i][j]);
        f(i - 1, j, dp[i][j]);
    }
    return 0;
}

int main()
{
    ifstream fin("turtle.in");
    ofstream fout("turtle.out");

    fin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fin >> matrix[i][j];
            dp[i][j] = -1;
        }
    }
    dp[n - 1][0] = matrix[n - 1][0];
    f(n - 1, 0, 0);


    int mx = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mx = max(mx, dp[i][j]);
        }
    }
    fout << mx;
}