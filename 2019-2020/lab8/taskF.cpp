#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;


/*

YEISK
SEVASTIAN TRUTNEV
M3101

*/

ifstream fin("input.txt");
ofstream fout("output.txt");

#define NL '\n';
typedef vector< vector<char> > MATRIX;

struct POINT{
    int x;
    int y;
    char direct;
};
POINT* make_point(int x, int y){
    auto* p = new POINT;
    p->x = x;
    p->y = y;
    return p;
}
vector<POINT*> getWays(POINT* p, int n, int m){
    vector<POINT*> ways;
    for(int i = -1; i < 2; i++){
        if(i == 0) continue;
        if(p->x + i >= 0 && p->x + i < n){
            POINT* point = make_point(p->x + i, p->y);
            point->direct = (i == -1 ? 'U' : 'D');
            ways.push_back(point);
        }
        if(p->y + i >= 0 && p->y+ i < m){
            POINT* point = make_point(p->x, p->y + i);
            point->direct = (i == -1 ? 'L' : 'R');
            ways.push_back(point);
        }
    }
    return ways;
}

int main() {
    int n, m;
    fin >> n >> m;
    MATRIX maze(n);
    vector< vector<int> > Dist(n);
    POINT* from;
    POINT* to;

    for(int i = 0; i < n; i++){
        maze[i].resize(m);
        Dist[i].resize(m);
        for(int j = 0; j < m; j++){
            Dist[i][j] = -1;
            fin >> maze[i][j];
            if(maze[i][j] == 'S'){
                from = make_point(i, j);
            }else if(maze[i][j] == 'T'){
                to = make_point(i, j);
            }
        }
    }
    queue<POINT*> BFS;
    BFS.push(from);
    Dist[from->x][from->y] = 0;
    POINT* now;
    while(!BFS.empty()){
        now = BFS.front();
        BFS.pop();
        vector<POINT*> ways = getWays(now, n, m);
        for(int i = 0; i < ways.size(); i++){
            if(maze[ways[i]->x][ways[i]->y] == '.' || maze[ways[i]->x][ways[i]->y] == 'T'){
                Dist[ways[i]->x][ways[i]->y] = Dist[now->x][now->y] + 1;
                maze[ways[i]->x][ways[i]->y] = ways[i]->direct;
                if(ways[i]->x == to->x && ways[i]->y == to->y) break;
                BFS.push(ways[i]);
            }
        }
    }

    fout << Dist[to->x][to->y] << NL;

    if(Dist[to->x][to->y] > 0){
        vector<char> way;
        while(to->x != from->x || to->y != from->y){
            char direct = maze[to->x][to->y];
            way.push_back(direct);
            if(direct == 'L') to->y++;
            if(direct == 'R') to->y--;
            if(direct == 'U') to->x++;
            if(direct == 'D') to->x--;
        }
        for(int i = way.size() - 1; i >= 0; i--){
            fout << way[i];
        }
    }

    return 0;
}

