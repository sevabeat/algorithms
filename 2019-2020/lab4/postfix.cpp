#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int calculate(int a, int b, int x) {
    if(x == '*') return a * b;
    if(x == '+') return a + b;
    return a - b;
}

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");

    stack<int> operations;

    char x;
    int a, b;

    while(fin >> x){
        if(x == '*' || x == '-' || x == '+'){
            a = operations.top();
            operations.pop();
            b = operations.top();
            operations.pop();
            operations.push(calculate(b, a, x));
        }else{
            fin.unget();
            fin >> a;
            operations.push(a);
        }
    }
    fout << operations.top();

    return 0;
}