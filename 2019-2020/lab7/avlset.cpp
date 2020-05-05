#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>
#include <queue>

using namespace std;

ifstream fin("avlset.in");
ofstream fout("avlset.out");

struct InputNode{
    int key;
    int left;
    int right;
};

struct Node{
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int key): key(key){
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
    private:
        Node* root = nullptr;
        int Size = 0;
        int getHeight(Node* node){
            if(node == nullptr) return 0;
            return node->height;
        }
        void fixHeight(Node* node){
            node->height = max(
                    this->getHeight(node->left),
                    this->getHeight(node->right)) + 1;
        }
        int getBalance(Node* node){
            if(node == nullptr) return 0;
            return this->getHeight(node->right) - this->getHeight(node->left);
        }
        Node* balanceTree(Node* node){
            this->fixHeight(node);
            if(this->getBalance(node) > 1){
                if(this->getBalance(node->right) < 0){
                    node->right = this->rotateRight(node->right);
                }
                return this->rotateLeft(node);
            }
            if(this->getBalance(node) < -1){
                if(this->getBalance(node->left) > 0){
                    node->left = this->rotateLeft(node->left);
                }
                return this->rotateRight(node);
            }
            return node;
        }
        Node* rotate(Node* node, bool isLeft){
            Node* tmp = isLeft ? node->right : node->left;
            if(isLeft){
                node->right = tmp->left;
                tmp->left = node;
            }else{
                node->left = tmp->right;
                tmp->right = node;
            }
            this->fixHeight(node);
            this->fixHeight(tmp);
            return tmp;
        }
        Node* insertDfs(int key, Node* now){
            if(now == nullptr){
                return new Node(key);
            }
            if(key > now->key){
                now->right = insertDfs(key, now->right);

            }else if(key < now->key){
                now->left = insertDfs(key, now->left);
            }
            return this->balanceTree(now);
        }
        Node* findLastRight(Node* now){
            if(now->right == nullptr) return now;
            return findLastRight(now->right);
        }
        Node* removeDfs(int key, Node* now){
            if(now == nullptr) return nullptr;
            if(key > now->key){
                now->right = removeDfs(key, now->right);
            }else if(key < now->key){
                now->left = removeDfs(key, now->left);
            }else{
                if(now->left == nullptr && now->right == nullptr){
                    return nullptr;
                }else if(now->left == nullptr){
                    now = now->right;
                    return this->balanceTree(now);
                }else{
                    Node* finded = findLastRight(now->left);
                    now->key = finded->key;
                    now->left = removeDfs(finded->key, now->left);
                }
            }
            return this->balanceTree(now);
        }
        Node* find(int key, Node* now){
            if(now == nullptr) return nullptr;
            if(key > now->key) return find(key, now->right);
            if(key < now->key) return find(key, now->left);
            return now;
        }
    public:
        Node* rotateLeft(Node* node){
            return this->rotate(node, true);
        }
        Node* rotateRight(Node* node){
            return this->rotate(node, false);
        }
        int insert(int key){
            this->root = this->insertDfs(key, this->root);
            this->Size++;
            return this->getBalance(this->root);
        }
        int remove(int key){
            this->root = this->removeDfs(key, this->root);
            return this->getBalance(this->root);
        }
        bool isExist(int key){
            return this->find(key, this->root) != nullptr;
        }
};

int main() {
    int n;
    auto AVL = new AVLTree();
    fin >> n;
    char command;
    int key;
    for(int i = 0; i < n; i++){
        fin >> command >> key;
        if(command == 'A'){
            fout << AVL->insert(key) << endl;
        }else if(command == 'D'){
            fout << AVL->remove(key) << endl;
        }else if(command == 'C'){
            fout << (AVL->isExist(key) ? "Y": "N") << endl;
        }
    }

    return 0;
}

