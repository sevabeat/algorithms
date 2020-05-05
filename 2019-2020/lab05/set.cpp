#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <list>
using namespace std;


class MySet{
    private:
         list<int> values[(int)(1e6 + 4)];

         int hash(int key){
             return abs(key % (int)(1e6 + 3));
         }
    public:
        void insert(int value) {
             if(!exist(value)){
                 values[hash(value)].push_back(value);
             }
        }
        void deleteValue(int value) {
             int hashKey = hash(value);
             for(auto it = values[hashKey].begin(); it != values[hashKey].end(); it++){
                 if(*it == value){
                     values[hashKey].erase(it);
                     break;
                 }
             }
        }
        bool exist(int value) {
            int hashKey = hash(value);
            for (auto it = values[hashKey].begin(); it != values[hashKey].end(); it++) {
                if (*it == value) {
                    return true;
                }
            }
            return false;
        }
};



int main()
{
    ifstream fin("set.in");
    ofstream fout("set.out");

    MySet* Set = new MySet;
    string command;
    int value;
    while(fin >> command){
        fin >> value;
        if(command == "insert"){
            Set->insert(value);
        }else if(command == "delete"){
            Set->deleteValue(value);
        }else if(command == "exists"){
            fout << (Set->exist(value) ? "true" : "false") << endl;
        }
    }
}