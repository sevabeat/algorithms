#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

char getOpposite(char bracket){
    if(bracket == '[') return ']';
    if(bracket == '(') return ')';
    if(bracket == ']') return '[';
    return '(';

}

int main() {
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");

    stack<char> brackets;

    string str;
    while(fin >> str){
        while(!brackets.empty()) brackets.pop();
        for(int i = 0; i < str.size(); i++){
            if(!brackets.empty() && (str[i] == ')' || str[i] == ']')){
                if(brackets.top() == getOpposite(str[i])){
                    brackets.pop();
                }else break;
            }else{
                brackets.push(str[i]);
            }
        }
        if(brackets.empty()){
            fout << "YES" << endl;
        }else{
            fout << "NO" << endl;
        }
    }


    return 0;
}