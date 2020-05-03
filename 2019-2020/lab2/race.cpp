#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct User{
    string name;
    string country;
    int index;
};

class Heap {

    int heap_size;
public:
    vector<User> a;
    Heap(vector<User> b){
        a = b;
        heap_size = b.size();
    }
    int siftDown(int i){
        while(2 * i + 1 < heap_size){
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int tmp_child = left_child;

            if(right_child < heap_size && (a[right_child].country < a[left_child].country || (a[right_child].country == a[left_child].country && a[right_child].index < a[left_child].index))){
                tmp_child = right_child;
            }
            if(a[i].country < a[tmp_child].country) break;
            if(a[i].country == a[tmp_child].country && a[i].index < a[tmp_child].index) break;

            User tmp = a[i];
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
            User tmp = a[0];
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
    ifstream fin("race.in");
    ofstream fout("race.out");
    int n;
    fin >> n;
    vector<User> users(n);

    User u;
    for(int i = 0; i < n; i++){
        fin >> u.country >> u.name;
        u.index = i;
        users[i] = u;
    }
    Heap p(users);
    p.hsort();

    string last = "";
    for(int i = n - 1; i >= 0; i--){
        if(p.a[i].country != last){
            fout << "=== " << p.a[i].country << " ===" << '\n';
            last = p.a[i].country;
        }
        fout << p.a[i].name << '\n';
    }

}