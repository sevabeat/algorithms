#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>
#include <climits>
#include <queue>
using namespace std;

#define NL '\n'

struct SimpleBSTNode{
    int key;
    SimpleBSTNode* left;
    SimpleBSTNode* right;
};

class SimpleBST{
    private:
        SimpleBSTNode* root = nullptr;

        SimpleBSTNode* CreateSimpleBSTNode(int key){
            auto node = new SimpleBSTNode;
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;

            return node;
        }
        SimpleBSTNode* insertNode(SimpleBSTNode* now, SimpleBSTNode* newNode){
            if(now == nullptr) return newNode;
            if(newNode->key < now->key){
                now->left = insertNode(now->left, newNode);
            }else if(newNode->key > now->key){
                now->right = insertNode(now->right, newNode);
            }
            return now;
        }
        pair<SimpleBSTNode*, SimpleBSTNode**> find(int key){
            SimpleBSTNode** last = &this->root;
            SimpleBSTNode* now = this->root;
            while(now != nullptr){
                if(now->key == key) return make_pair(now, last);
                if(now->key > key){
                    last = &now->left;
                    now = now->left;
                }else{
                    last = &now->right;
                    now = now->right;
                }
            }
            return make_pair(nullptr, nullptr);
        }

    public:
        void insert(int key){
            SimpleBSTNode* newNode = this->CreateSimpleBSTNode(key);
            this->root = insertNode(this->root, newNode);
        }
        bool exist(int key){
            return find(key).first != nullptr;
        }
        SimpleBSTNode* next(int key){
            SimpleBSTNode* now = this->root;
            SimpleBSTNode* finded = nullptr;
            while(now != nullptr){
                if(now->key > key){
                    finded = now;
                    now = now->left;
                }else{
                    now = now->right;
                }
            }
            return finded;
        }
        SimpleBSTNode* prev(int key){
            SimpleBSTNode* now = this->root;
            SimpleBSTNode* finded = nullptr;
            while(now != nullptr){
                if(now->key < key){
                    finded = now;
                    now = now->right;
                }else{
                    now = now->left;
                }
            }
            return finded;
        }
        void remove(int key){
            pair<SimpleBSTNode*, SimpleBSTNode**> nodePair = this->find(key);
            SimpleBSTNode* node = nodePair.first;
            SimpleBSTNode** hanger = nodePair.second;
            if(node != nullptr){
                if(node->left == nullptr && node->right == nullptr){
                    *hanger = nullptr;
                    delete node;
                }else if(node->left == nullptr || node->right == nullptr){
                    *hanger = node->left != nullptr ? node->left : node->right;
                    delete node;
                }else{
                    SimpleBSTNode** LastLeftNodeHanger = &node->right;
                    SimpleBSTNode* LastLeftNode = node->right;
                    while(LastLeftNode->left != nullptr){
                        LastLeftNodeHanger = &LastLeftNode->left;
                        LastLeftNode = LastLeftNode->left;
                    }
                    if(LastLeftNode->right != nullptr){
                        *LastLeftNodeHanger = LastLeftNode->right;
                    }else{
                        *LastLeftNodeHanger = nullptr;
                    }
                    node->key = LastLeftNode->key;
                    delete LastLeftNode;
                }
            }
        }
};

int main()
{
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");

    auto BST = new SimpleBST;
    string command;
    int key;
    while(fin >> command >> key){
        if(command == "insert"){
            BST->insert(key);
        }else if(command == "delete"){
            BST->remove(key);
        }else if(command == "exists"){
            fout << (BST->exist(key) ? "true" : "false") << NL;
        }else if(command == "next"){
            SimpleBSTNode* node = BST->next(key);
            if(node == nullptr){
                fout << "none" << NL;
            }else{
                fout << node->key << NL;
            }
        }else if(command == "prev"){
            SimpleBSTNode* node = BST->prev(key);
            if(node == nullptr){
                fout << "none" << NL;
            }else{
                fout << node->key << NL;
            }
        }
    }

}