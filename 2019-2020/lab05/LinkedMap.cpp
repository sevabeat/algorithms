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

#define MAX_SIZE (int)(2e5 + 3)

struct MyLinkedMapItem{
    string key;
    string value;
    MyLinkedMapItem* prev;
    MyLinkedMapItem* next;
};

class MyLinkedMap{
    private:
        list<MyLinkedMapItem>* values = new list<MyLinkedMapItem>[MAX_SIZE];
        int hash(string& key){
            unsigned long long HashKey = 0;
            unsigned long long pn = 1;
            for(int i = 0; i < key.size(); i++){
                HashKey += (tolower(key[i]) - 'a' + 1) * pn;
                HashKey %= ULLONG_MAX;
                pn *= 31;
                pn %= ULLONG_MAX;
            }
            HashKey %= MAX_SIZE;
            return (int)HashKey;
        }
    public:
        MyLinkedMapItem* last = 0;
        void put(string key, string value){
            int HashKey = hash(key);
            for(auto it = values[HashKey].begin(); it != values[HashKey].end(); it++){
                if(it->key == key){
                    it->value = value;
                    return;
                }
            }
            MyLinkedMapItem item;
            item.key = key;
            item.value = value;
            item.prev = last;
            item.next = 0;

            values[HashKey].push_back(item);
            MyLinkedMapItem* newLast = &values[HashKey].back();
            if(last != 0){
                last->next = newLast;
            }
            last = newLast;
        }
        string prev(string key){
            int HashKey = hash(key);
            for(auto it = values[HashKey].begin(); it != values[HashKey].end(); it++){
                if(it->key == key && it->prev != 0){
                    return it->prev->value;
                }
            }
            return "none";
        }
        string next(string key){
            int HashKey = hash(key);
            for(auto it = values[HashKey].begin(); it != values[HashKey].end(); it++){
                if(it->key == key && it->next != 0){
                    return it->next->value;
                }
            }
            return "none";
        }
        string get(string key){
            int HashKey = hash(key);
            for(auto it = values[HashKey].begin(); it != values[HashKey].end(); it++){
                if(it->key == key){
                    return it->value;
                }
            }
            return "none";
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
                    return;
                }
            }
        }
};


int main()
{
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");

    MyLinkedMap* Map = new MyLinkedMap;

    string command, key, value;
    while(fin >> command){
        fin >> key;
        if(command == "put"){
            fin >> value;
            Map->put(key, value);
        }else if(command == "delete"){
            Map->remove(key);
        }else if(command == "get"){
            fout << Map->get(key) << endl;
        }else if(command == "next"){
            fout << Map->next(key) << endl;
        }else if(command == "prev"){
            fout << Map->prev(key) << endl;
        }
    }
}