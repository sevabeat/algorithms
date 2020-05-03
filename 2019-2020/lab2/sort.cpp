#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Heap {

    int heap_size;
public:
    vector<int> a;
    Heap(vector<int> b){
        a = b;
        heap_size = b.size();
    }
    int set(){
        cout << a.size();
        return 0;
    }
    int siftDown(int i){
        while(2 * i + 1 < heap_size){
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int tmp_child = left_child;

            if(right_child < heap_size && a[right_child] < a[left_child]){
                tmp_child = right_child;
            }
            if(a[i] <= a[tmp_child]) break;

            int tmp = a[i];
            a[i] = a[tmp_child];
            a[tmp_child] = tmp;

            i = tmp_child;
        }
        return 0;
    }
    int build(){
        for(int i = heap_size / 2; i >= 0; i--){
            siftDown(i);
        }
        return 0;
    }
    int c(){
        for(int i = 0; i < a.size(); i++){
            cout << a[i] << " ";
        }
        return 0;
    }
    int hsort(){
        build();

        int n = a.size();
        cout << n << endl;
        for(int i = 0; i < n - 1; i++){
            int tmp = a[0];
            a[0] = a[n - i - 1];
            a[n - i - 1] = tmp;
            heap_size--;
            siftDown(0);
        }
        return 0;
    }
};

int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int n;
    fin >> n;

    vector<int> f(n);
    for(int i = 0; i < n; i++){
        fin >> f[i];
    }
    Heap p(f);
    p.hsort();

    for(int i = p.a.size() - 1; i >= 0; i--){
        fout << p.a[i] << " ";
    }

}