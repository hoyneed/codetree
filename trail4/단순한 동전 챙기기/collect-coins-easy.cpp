#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>
#include <climits>
#include <string>
#include <utility>

using namespace std;
namespace {
constexpr int MAX_N = 20;
constexpr int MAX_M = 11;
int N;
constexpr int INF = INT_MAX / 2;
struct State {
    int r, c;
    int val, cnt;
};
using Pos = pair<int,int>;
array<string, MAX_N> grid;
array<Pos, MAX_M> nodes;
array<array<int, MAX_M>, MAX_M> graph;
array<bool, MAX_M> exists;
int max_num;
int answer;

void DFS(const int node, const int coins, const int dist) {
    if(dist > answer) return;
    if(coins == 3) {
        answer = min(answer , dist + graph[node][10]);
        return;
    }
    if(coins + (max_num - node) < 3) return;
    for(int i= node+1;i<=max_num;++i) {
        if(!exists[i]) continue;
        DFS(i, coins+1, dist + graph[node][i]);
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    max_num = 0;
    for(int i=0;i<N;++i) {
        cin >> grid[i];
        for(int j=0;j<N;++j) {
            if(grid[i][j] == 'E') {
                nodes[10] = {i,j};
                exists[10] = true;
            } else if (grid[i][j] == 'S') {
                nodes[0] = {i,j};
                exists[0] = true;
            } else if (grid[i][j] != '.') {
                const int val = grid[i][j] - '0';
                nodes[val] = {i,j};
                max_num = max(max_num, val);
                exists[val] = true;
            }
        }
    }

    for(int i=0;i<11;++i) {
        fill(graph[i].begin(), graph[i].end(), INF);
    }
    for(int i=0;i<=max_num;++i) {
        const Pos& u = nodes[i];
        for(int j=i+1;j<=max_num;++j) {
            const Pos& v = nodes[j];
            graph[i][j] = abs(u.first - v.first) + abs(u.second - v.second);
        }
        const Pos& e = nodes[10];
        graph[i][10] = abs(u.first - e.first) + abs(u.second - e.second);
    }

    answer = INF;

    DFS(0,0,0);
    cout << (answer == INF ? -1 : answer) << '\n';
    return 0;
}