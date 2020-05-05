#include <iostream>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <cmath>

using namespace std;

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int findKtn(int* array, int left, int right, int k) {
    int it1 = left;
    int it2 = right;
    int mid = array[(left + right) / 2];
    do {
        while(array[it1] < mid) {
            it1++;
        }

        while(array[it2] > mid) {
            it2--;
        }

        if (it1 <= it2) {
            swap(&array[it1], &array[it2]);
            it1++;
            it2--;
        }
    } while (it1 <= it2);

    if(it2 > left && it2 >= k){
        findKtn(array, left, it2, k);
    }
    if(it1 < right && it2 <= k){
        findKtn(array, it1, right, k);
    }
    return array[k];
}


int main()
{
    ifstream fin("kth.in");
    ofstream fout("kth.out");
    
    int n, k;
    fin >> n >> k;
    int* nums = (int*)malloc(sizeof(int) * n);
    int A, B, C;

    fin >> A >> B >> C;
    fin >> nums[0] >> nums[1];
    for(int i = 2; i < n; i++){
        nums[i] = A * nums[i - 2] + B * nums[i - 1] + C;
    }
    cout << findKtn(nums, 0, n - 1, k - 1);
}