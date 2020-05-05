#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("stack.in");
    ofstream fout("stack.out");

    int n;
    vector<int> MyStack;
    fin >> n;
    char operation;
    int num;
    for(int i = 0; i < n; i++){
        fin >> operation;
        if(operation == '+'){
            fin >> num;
            MyStack.push_back(num);
        }else{
            fout << *(MyStack.end() - 1) << endl;
            MyStack.erase(MyStack.end() - 1);

        }
    }

    return 0;
}