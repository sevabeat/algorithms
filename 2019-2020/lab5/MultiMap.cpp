#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <list>
#include <cctype>
#include <climits>
#include <algorithm>

using namespace std;

struct MyLinkedSetItem{
    string key;
    MyLinkedSetItem* prev;
    MyLinkedSetItem* next;
};

class HashTable{
    public:
        int MAX_SIZE;
        int hash(string& key){
            unsigned long long HashKey = 0;
            unsigned long long pn = 1;
            for(int i = 0; i < key.size(); i++){
                HashKey += (tolower(key[i]) - 'a' + 1) * pn;
                HashKey %= ULLONG_MAX;
                pn *= 31;
                pn %= ULLONG_MAX;
            }
            HashKey %= this->MAX_SIZE;
            return (int)HashKey;
        }
};

class MyLinkedSet : private HashTable{
    private:
        list<MyLinkedSetItem>* values;
        MyLinkedSetItem* last = 0;
        int size = 0;
    public:
        MyLinkedSet(){
            this->MAX_SIZE = 103;
            this->values = new list<MyLinkedSetItem>[this->MAX_SIZE];
        }
        void put(string key){
            int HashKey = hash(key);
            for(auto &it : values[HashKey]){
                if(it.key == key) return;
            }
            MyLinkedSetItem item;
            item.key = key;
            item.prev = last;
            item.next = 0;

            values[HashKey].push_back(item);
            MyLinkedSetItem* newLast = &values[HashKey].back();
            if(last != 0) last->next = newLast;
            last = newLast;
            size++;
        }
        MyLinkedSetItem* getLast(){
            return last;
        }
        void remove(string key){
            int HashKey = hash(key);
            for(auto it = values[HashKey].begin(); it != values[HashKey].end(); it++){
                if(it->key == key){
                    if(it->prev != 0){
                        it->prev->next = it->next;
                    }
                    if(it->next != 0){
                        it->next->prev = it->prev;
                    }
                    if(it->key == last->key){
                        last = it->prev;
                    }
                    values[HashKey].erase(it);
                    size--;
                    return;
                }
            }
        }
        void removeAll(){
            last = 0;
            delete[] this->values;
            values = new list<MyLinkedSetItem>[this->MAX_SIZE];
            size = 0;
        }
        int getSize(){
            return this->size;
        }
};

struct MyMultiMapItem{
    string key;
    MyLinkedSet* values;
};

class MyMultiMap : private HashTable{
private:
    list<MyMultiMapItem>* values;
public:
    MyMultiMap(){
        this->MAX_SIZE = 10007;
        this->values = new list<MyMultiMapItem>[this->MAX_SIZE];
    }
    void put(string key, string value){
        int HashKey = hash(key);
        for(auto &it : values[HashKey]) {
            if (it.key == key){
                it.values->put(value);
                return;
            }
        }
        MyMultiMapItem item;
        item.key = key;
        MyLinkedSet* ValuesSet = new MyLinkedSet;
        ValuesSet->put(value);
        item.values = ValuesSet;
        values[HashKey].push_back(item);
    }
    void remove(string key, string value){
        int HashKey = hash(key);
        for(auto &it : values[HashKey]) {
            if (it.key == key){
                it.values->remove(value);
            }
        }
    }
    void removeAll(string key){
        int HashKey = hash(key);
        for(auto &it : values[HashKey]) {
            if (it.key == key){
                it.values->removeAll();
            }
        }
    }
    pair<int, MyLinkedSetItem*> getLast(string key){
        int HashKey = hash(key);
        for(auto &it : values[HashKey]) {
            if (it.key == key){
                return make_pair(it.values->getSize(), it.values->getLast());
            }
        }
        return make_pair(0, (MyLinkedSetItem*)0);
    }
};

int main()
{
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");

    MyMultiMap* MultiMap = new MyMultiMap;

    string command, key, value;
    while(fin >> command){
        fin >> key;
        if(command == "put"){
            fin >> value;
            MultiMap->put(key, value);
        }else if(command == "delete"){
            fin >> value;
            MultiMap->remove(key, value);
        }else if(command == "deleteall"){
            MultiMap->removeAll(key);
        }else if(command == "get"){
            pair<int, MyLinkedSetItem*> last = MultiMap->getLast(key);
            fout << last.first << " ";
            while(last.second != 0){
                fout << last.second->key << " ";
                last.second = last.second->prev;
            }
            fout << endl;
        }
    }
}