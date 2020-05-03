#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
 
using namespace std;
 
int main()
{
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
    int n;
    fin >> n;
 
    int* array = (int*)malloc(sizeof(int) * n);
 
    for(int i = 0; i < n; i++){
        array[i] = i + 1;
    }
 
    for(int i = 2; i < n; i++){
        int tmp = array[i];
        array[i] = array[i / 2];
        array[i / 2] = tmp;
    }
 
    for(int i = 0; i < n; i++){
        fout << array[i] << " ";
    }
}