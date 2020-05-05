#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>
#include <queue>

using namespace std;

ifstream fin("rotation.in");
ofstream fout("rotation.out");

struct Node{
    int key;
    int left;
    int right;
};

class AVLTree{
    private:
        vector<Node> tree;
        vector<int> height;
        int dfs(int vertex, int height){
            if(vertex < 0) return 0;
            this->height[vertex] = max(
                    dfs(this->tree[vertex].left, height),
                    dfs(this->tree[vertex].right, height)) + 1;
            return this->height[vertex];
        }
        void fixHeight(int vertex){
            this->height[vertex] = max(
                    this->getHeight(this->tree[vertex].left),
                    this->getHeight(this->tree[vertex].right)) + 1;
        }
    public:
        int getHeight(int vertex){
            if(vertex < 0) return 0;
            return this->height[vertex];
        }
        void pushNode(Node* node) {
            this->tree.push_back(*node);
            this->height.push_back(0);
        }
        void calcHeight(){
            dfs(0, 0);
        }
        int rotateLeft(int vertex){
            int b = this->tree[vertex].right;
            this->tree[vertex].right = this->tree[b].left;
            this->tree[b].left = vertex;
            this->fixHeight(vertex);
            this->fixHeight(b);

            return b;
        }
        int rotateRight(int vertex){
            int b = this->tree[vertex].left;

            this->tree[vertex].left = this->tree[b].right;
            this->tree[b].right = vertex;
            this->fixHeight(vertex);
            this->fixHeight(b);
            return b;
        }
        int bigRotateLeft(int vertex){
            this->tree[vertex].right = this->rotateRight(this->tree[vertex].right);
            return this->rotateLeft(vertex);
        }
        int rotate(int vertex){
            int right = this->tree[vertex].right;

            int childLeftH = this->getHeight(this->tree[right].left);
            int childRightH = this->getHeight(this->tree[right].right);

            if(childRightH - childLeftH < 0){
                return this->bigRotateLeft(vertex);
            }
            return this->rotateLeft(vertex);

        }
        void printTree(int root){
            fout << this->tree.size() << endl;
            queue<int> q;
            q.push(root);
            int line = 1;
            while(!q.empty()){
                int vertex = q.front();
                q.pop();
                int l = 0, r = 0;
                if(this->tree[vertex].left >= 0){
                    q.push(this->tree[vertex].left);
                    l = ++line;
                }
                if(this->tree[vertex].right >= 0){
                    q.push(this->tree[vertex].right);
                    r = ++line;
                }

                fout << this->tree[vertex].key << " " << (l) << " " << (r) << endl;
            }
        }
};

int main() {
    int n;
    fin >> n;
    Node newNode;
    auto AVL = new AVLTree();
    for(int i = 0; i < n; i++){
        fin >> newNode.key >> newNode.left >> newNode.right;
        newNode.left--;
        newNode.right--;
        AVL->pushNode(&newNode);
    }
    AVL->calcHeight();
    int newRoot = AVL->rotate(0);
    AVL->printTree(newRoot);
    return 0;
}