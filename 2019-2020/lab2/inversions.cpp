#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

typedef long long ll;

ll merge(int* array, int left, int m, int right){
    int it1 = left;
    int it2 = m;
    ll inv = 0;
    int* result = (int*)malloc(sizeof(int) * (right - left));
    int now = 0;
    while(it1 < m || it2 < right){
        if(it1 < m && it2 < right){
            if(array[it1] <= array[it2]){
                result[now] = array[it1];
                it1++;
            }else{
                result[now] = array[it2];
                it2++;
                inv += m - it1;
            }
        }else if(it1 < m){
            result[now] = array[it1];
            it1++;
        }else{
            result[now] = array[it2];
            it2++;
        }
        now++;
    }
    for(int i = 0; i < now; i++){
        array[left + i] = result[i];
    }
    free(result);
    return inv;
}

int main() {
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    int n;
    fin >> n;
    int* array = (int*) malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++){
        fin >> array[i];
    }

    ll inv = 0;
    for(int i = 1; i < n; i *= 2){
        for(int j = 0; j < n - i; j += i * 2){
            inv += merge(array, j, j + i, min(n, j + i * 2));
        }
    }
    fout << inv;

    fin.close();
    fout.close();

    return 0;
}