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

#define MAX_SIZE (int)(1e5 + 3)

class MyMap{
    private:
        list< pair<string, string> >* values = new list< pair<string, string> >[MAX_SIZE];
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
        void put(string key, string value){
            int HashKey = hash(key);
            auto it = find_if(values[HashKey].begin(),
                              values[HashKey].end(),
                              [&](pair<string, string> a){ return a.first == key; } );

            if(it == values[HashKey].end()){
                values[HashKey].push_back(make_pair(key, value));
            }else{
                it->second = value;
            }

        }
        void remove(string key){
            int HashKey = hash(key);
            auto it = find_if(values[HashKey].begin(),
                              values[HashKey].end(),
                              [&](pair<string, string> a){ return a.first == key; } );
            if(it != values[HashKey].end()){
                values[HashKey].erase(it);
            }
        }
        string get(string key){
            int HashKey = hash(key);
            auto it = find_if(values[HashKey].begin(),
                              values[HashKey].end(),
                              [&](pair<string, string> a){ return a.first == key; } );
            if(it != values[HashKey].end()){
                return it->second;
            }else{
                return "none";
            }

        }
};


int main()
{
    ifstream fin("map.in");
    ofstream fout("map.out");

    MyMap* Map = new MyMap;

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
        }
    }
}