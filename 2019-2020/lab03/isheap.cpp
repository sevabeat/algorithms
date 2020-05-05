#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");

    int n, c;
    fin >> n;
    vector<int> nums(n);

    for(int i = 0; i < n; i++){
        fin >> nums[i];
    }

    bool isPyramid = true;
    for(int i = 0; i < n; i++){
        c = 2*i + 1;
        for(int j = 0; j < 2; j++){
            c += j;
            if(c < n && nums[i] > nums[c]){
                isPyramid = false;
            }
        }
        if(!isPyramid) break;
    }
    fout << (isPyramid ? "YES" : "NO") << endl;

    return 0;
}