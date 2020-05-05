#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

#define NL '\n';

class Heap {
public:
    vector<pair<int, int>> array;

    int siftDown(int i){
        while(2 * i + 1 < array.size()){
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;

            int tmp_child = left_child;

            if(right_child < array.size() && array[right_child] < array[left_child]){
                tmp_child = right_child;
            }
            if(array[i] <= array[tmp_child]) break;

            swap(array[i], array[tmp_child]);

            i = tmp_child;
        }
        return 0;
    }
    void siftUp(int i){
        while(array[i] < array[(i - 1) / 2]){
            swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void push(int num, int index){
        array.emplace_back(num, index);
        siftUp(array.size() - 1);
    }
    bool isEmpty(){
        return array.size() == 0;
    }
    int extractMin(){
        if(!isEmpty()){
            pair<int, int> mn = array[0];
            array[0] = array[array.size() - 1];
            array.erase(array.end() - 1);

            siftDown(0);
            return mn.first;
        }
        return 0;
    }
    void decreaseKey(int key, int value){
        for(int i = 0; i < array.size(); i++){
            if(array[i].second == key){
                array[i].first = value;
                siftUp(i);
                break;
            }
        }
    }
};


int main()
{
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");

    Heap* priorityQueue = new Heap();

    string command;
    int num, key;
    vector<int> nums;

    int cnt = 0;
    while(fin >> command){
        if(command == "push"){
            fin >> num;
            priorityQueue->push(num, cnt);
        }else if(command == "extract-min"){
            if(!priorityQueue->isEmpty()){
                fout << priorityQueue->extractMin() << NL;
            }else{
                fout << "*" << NL;
            }
        }else if(command == "decrease-key"){
            fin >> key >> num;
            priorityQueue->decreaseKey(key - 1, num);
        }
        cnt++;
    }

}