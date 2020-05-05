#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

int main() {
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");
    int n, m, k;
    fin >> n >> m >> k;
    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        fin >> words[i];
    }
    map<char, vector<string>> storage;
    for (int stage = 1; stage <= k; stage++) {
        for (int i = 0; i < n; i++) {
            storage[words[i][m - stage]].push_back(words[i]);
        }
        words.clear();
        for (auto &it : storage) {
            for (int i = 0; i < it.second.size(); i++) {
                words.push_back(it.second[i]);
            }
        }
        storage.clear();
    }
    for (int i = 0; i < n; i++) {
        fout << words[i] << '\n';
    }
    return 0;
}