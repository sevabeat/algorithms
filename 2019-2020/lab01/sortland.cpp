// Example program
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct Sitizen{
    int id;
    double money;
};

class Heap {

    int heap_size;
public:
    vector<Sitizen> a;
    Heap(vector<Sitizen> b){
        a = b;
        heap_size = b.size();
    }
    int siftDown(int i){
        while(2 * i + 1 < heap_size){
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int tmp_child = left_child;

            if(right_child < heap_size && a[right_child].money < a[left_child].money){
                tmp_child = right_child;
            }
            if(a[i].money <= a[tmp_child].money) break;

            Sitizen tmp = a[i];
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
    int hsort(){
        build();

        int n = a.size();
        for(int i = 0; i < n - 1; i++){
            Sitizen tmp = a[0];
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
    ifstream fin("sortland.in");
    ofstream fout("sortland.out");

    int n;
    fin >> n;
    vector<Sitizen> f(n);
    Sitizen s;
    for(int i = 0; i < n; i++){
        fin >> s.money;
        s.id = i + 1;
        f[i] = s;
    }
    Heap p(f);
    p.hsort();

    fout << p.a[n - 1].id << " " << p.a[n / 2].id  << " " << p.a[0].id << endl;

}