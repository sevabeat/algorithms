#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

class Heap {
public:
    int heap_size;
    vector<int> &array;
    explicit Heap(vector<int>& b) : array(b){
        this->array = b;
        heap_size = b.size();
    }
    int siftDown(int i){
        while(2 * i + 1 < heap_size){
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int tmp_child = left_child;

            if(right_child < heap_size && array[right_child] > array[left_child]){
                tmp_child = right_child;
            }
            if(array[i] >= array[tmp_child]) break;

            int tmp = array[i];
            array[i] = array[tmp_child];
            array[tmp_child] = tmp;

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
};

void HeapSort(vector<int>& array){
    Heap* heap = new Heap(array);

    heap->build();
    int n = heap->heap_size;
    for(int i = 0; i < n - 1; i++){
        swap(heap->array[0], heap->array[n - i - 1]);
        heap->heap_size--;
        heap->siftDown(0);
    }

}

int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int n;
    fin >> n;

    vector<int> array(n);
    for(int i = 0; i < n; i++){
        fin >> array[i];
    }
    HeapSort(array);
    for(int i = 0; i < n; i++){
        fout << array[i] << " ";
    }
}