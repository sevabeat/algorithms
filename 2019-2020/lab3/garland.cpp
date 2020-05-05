#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>

using namespace std;


pair<double, double> lastAndMinByFirstTwo(double h1, double h2, int n){
    vector<double> nums(n);
    nums[0] = h1;
    nums[1] = h2;
    double mn = h1;
    for(int i = 2; i < n; i++){
        nums[i] = 2 * nums[i - 1] - nums[i - 2] + 2.0;
        mn = min(mn, nums[i]);
    }
    return make_pair(nums[n - 1], mn);
}

int main()
{
    ifstream fin("garland.in");
    ofstream fout("garland.out");

    double A;
    int n;
    fin >> n >> A;

    pair<double, double> x;
    double left = 0;
    double right = A;
    while(right - left > 1e-8){
        double m = (left + right) / 2;
        x = lastAndMinByFirstTwo(A, m, n);
        if(x.second < 0){
            left = m;
        }else{
            right = m;
        }
    }
    fout.precision(2);
    fout << fixed << x.first;
}