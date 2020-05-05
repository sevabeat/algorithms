#include <fstream>
#include <vector>
#include <algorithm>
 
const int INF = 1000000000;
std::vector <std::pair <int, std::pair <int, int>>> edges;
std::vector <long long> dist;
std::vector <int> p;
std::vector <int> answer;
int N;
 
 
bool find_negative_cycle() {
 
    int vertex;
 
    for (int i = 0; i < N; i++) {
 
        vertex = -1;
        for (int j = 0; j < edges.size(); j++) {
 
            int to = edges[j].second.second;
            int from = edges[j].second.first;
            int weight = edges[j].first;
 
            if (dist[from] + weight >= -INF && dist[to] > dist[from] + weight) {
                dist[to] = dist[from] + weight;
                p[to] = from;
                vertex = to;
            }
            else if (dist[from] + weight < -INF) {
                dist[to] = -INF;
                p[to] = from;
                vertex = to;
            }
        }
    }
 
    if (vertex == -1) {
        return false;
    }
 
    else {
        int tempVertex = vertex;
 
        for (int i = 0; i < N; i++) {
            tempVertex = p[tempVertex];
        }
 
        for (int that = tempVertex; ;that = p[that]){
            answer.push_back(that);
 
            if (that == tempVertex && answer.size() > 1)
                return true;
        }
    }
}
 
int main() {
    std::ifstream fin ("negcycle.in");
    std::ofstream fOut ("negcycle.out");
 
    fin >> N;
 
    dist.assign(N, INF);
    p.assign(N, -1);
 
    int weight;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> weight;
            if (weight != INF) {
                edges.push_back({weight, {i, j}});
            }
        }
    }
    fin.close();
 
    if (find_negative_cycle()) {
 
        std::reverse (answer.begin(), answer.end());
        fOut << "YES\n" << answer.size() << "\n";
        for (int vertex : answer) {
            fOut << ++vertex << " ";
        }
    }
 
    else {
        fOut << "NO";
    }
    fOut.close();
 
    return 0;
}