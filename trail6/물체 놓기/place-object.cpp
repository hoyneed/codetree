#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
namespace {
constexpr int MAX_N = 300;
constexpr int INF = 1e9;
int N;
using Edge = pair<int,int>;
array<array<int,MAX_N>,MAX_N> graph;
array<int,MAX_N> dist;
array<bool,MAX_N> visited;

int Prim() {
    int total = 0;
    visited[0] = true;
    for(int i=1;i<=N;++i) {
        int cur = -1;
        int min_dist = 1e9;
        for(int j=1;j<=N;++j) {
            if(visited[j]) continue;
            if(min_dist > dist[j]) {
                min_dist = dist[j];
                cur = j;
            }
        }
        visited[cur] = true;
        total += min_dist;
        for(int j=1;j<=N;++j) {
            if(visited[j]) continue;
            dist[j] = min(dist[j], graph[cur][j]);
        }
    }
    return total;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        cin >> dist[i];
    }
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            cin >> graph[i][j];
        }
    }
    cout << Prim();
    return 0;
}