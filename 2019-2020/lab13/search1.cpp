#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*

😎
SEVASTIAN TRUTNEV
M3101

*/

int main() {
    std::ifstream fin("search1.in");
    std::ofstream fout("search1.out");

    std::string str1, str2;
    fin >> str1 >> str2;

    std::vector<int> result;
    int size = str2.size() - str1.size();
    for(int i = 0; i <= size; i++){
        if(str2.substr(i, str1.size()) == str1){
            result.push_back(i + 1);
        }
    }
    fout << result.size() << std::endl;
    for(int i = 0; i < result.size(); i++){
        fout << result[i] << " ";
    }

}