#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int binSearch(vector<int>& nums, int wanted, bool isLeft){
    int left = -1;
    int right = nums.size();

    while(left < right - 1){
        int mid = (left + right) / 2;
        if((isLeft && nums[mid] < wanted) || (!isLeft && nums[mid] <= wanted)){
            left = mid;
        }else{
            right = mid;
        }
    }
    if(isLeft && nums[right] == wanted){
        return right + 1;
    }else if(!isLeft && nums[left] == wanted){
        return left + 1;
    }
    return -1;
}

int main() {
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");

    int n, q, query;
    fin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        fin >> nums[i];
    }
    fin >> q;
    for(int i = 0; i < q; i++){
        fin >> query;
        fout << binSearch(nums, query, true) << " " << binSearch(nums, query, false) << endl;
    }
    return 0;
}