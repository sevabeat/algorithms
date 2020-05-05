#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <fstream>

using namespace std;

typedef unsigned short int ushort;

#define NL '\n'

class QuackInterpreter{
    private:
        queue<ushort> ProgramQueue;
        vector<ushort> Registers;
        ushort getAndRemove(){
            ushort a = this->ProgramQueue.front();
            this->ProgramQueue.pop();
            return a;
        }
    public:
        QuackInterpreter(){
            this->Registers.resize(26);
            for(int i = 0; i < 26; i++){
                this->Registers[i] = 0;
            }
        }
        void run(vector<string>& commands, map<string, int>& marks){

            int i = 0;
            while (i < commands.size()) {
                ushort a, b;
                switch (commands[i][0]) {
                    case '+':{
                        a = this->getAndRemove();
                        b = this->getAndRemove();
                        this->ProgramQueue.push(a + b);
                        i++;
                        break;
                    }
                    case '-': {
                        a = this->getAndRemove();
                        b = this->getAndRemove();
                        this->ProgramQueue.push(a - b);
                        i++;
                        break;
                    }
                    case '*': {
                        a = this->getAndRemove();
                        b = this->getAndRemove();
                        this->ProgramQueue.push(a * b);
                        i++;
                        break;
                    }
                    case '/': {
                        a = this->getAndRemove();
                        b = this->getAndRemove();
                        if(b == 0){
                            this->ProgramQueue.push(0);
                        }else{
                            this->ProgramQueue.push(a / b);
                        }
                        i++;
                        break;
                    }
                    case '%': {
                        a = this->getAndRemove();
                        b = this->getAndRemove();
                        if (b == 0) {
                            a = 0;
                            b = 1;
                        }
                        this->ProgramQueue.push(a % b);
                        i++;
                        break;
                    }
                    case '>': {
                        a = this->getAndRemove();
                        int com = commands[i][1] - 'a';
                        this->Registers[com] = a;
                        i++;
                        break;
                    }
                    case '<': {
                        this->ProgramQueue.push(this->Registers[commands[i][1] - 'a']);
                        i++;
                        break;
                    }
                    case 'P': {
                        if (commands[i].size() == 1) {
                            a = this->getAndRemove();
                            cout << to_string(a) << "\n";
                        }
                        else {
                            cout << to_string(this->Registers[commands[i][1] - 'a']) << NL;
                        }
                        i++;
                        break;
                    }
                    case 'C': {
                        if (commands[i].size() == 1) {
                            a = this->getAndRemove();
                            cout << char(a % 256);
                        }
                        else {
                            cout << char(this->Registers[commands[i][1] - 'a'] % 256);
                        }
                        i++;
                        break;
                    }
                    case ':': {
                        i++;
                        break;
                    }
                    case 'J': {
                        string s = commands[i].substr(1);
                        i = marks[s];
                        break;
                    }
                    case 'Z': {
                        string s = commands[i].substr(2);
                        if (this->Registers[commands[i][1] - 'a'] == 0)
                            i = marks[s];
                        else
                            i++;
                        break;
                    }
                    case 'E': {
                        string s = commands[i].substr(3);
                        if (this->Registers[commands[i][1] - 'a'] == this->Registers[commands[i][2] - 'a'])
                            i = marks[s];
                        else
                            i++;
                        break;
                    }
                    case 'G': {
                        string s = commands[i].substr(3);
                        if (this->Registers[commands[i][1] - 'a'] > this->Registers[commands[i][2] - 'a'])
                            i = marks[s];
                        else
                            i++;
                        break;
                    }
                    case 'Q': {
                        return;
                    }
                    default:
                        a = atoi(commands[i].c_str());
                        this->ProgramQueue.push(a);
                        i++;
                        break;
                }
            }
        }
};


int main() {
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);

    vector<string>commands;
    map<string, int> marks;

    string str;
    while (cin >> str)
        commands.push_back(str);
    for (int i = 0; i < commands.size(); i++) {
        if (commands[i][0] == ':') {
            str = commands[i].substr(1);
            marks[str] = i + 1;
        }
    }
    auto Quack = new QuackInterpreter();
    Quack->run(commands, marks);

    return 0;
}