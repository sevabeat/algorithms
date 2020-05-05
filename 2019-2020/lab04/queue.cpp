#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("queue.in");
    ofstream fout("queue.out");

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
            fout << *(MyStack.begin()) << endl;
            MyStack.erase(MyStack.begin());

        }
    }

    return 0;
}