#include <iostream>
#include <queue>
#include <array>
#include <vector>
#include <utility>
using namespace std;
namespace {
constexpr int MAX_N = 501;
int N,M;
using Edge = pair<int,int>;
array<vector<Edge>,MAX_N> graph;
array<bool,MAX_N> visited;

int Prim() {
    int total = 0;
    visited[1] = true;
    int cnt = 1;
    priority_queue<Edge,vector<Edge>,greater<>> pq;
    for(const auto&[v,w] : graph[1]) {
        pq.emplace(w,v);
    }
    while(!pq.empty()) {
        if(cnt == N) break;
        const auto [w,u] = pq.top();
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        total += w;
        ++cnt;
        for(const auto& [v,w] : graph[u]) {
            if(visited[v]) continue;
            pq.emplace(w,v);
        }
    }
    return total;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v,w);
        graph[v].emplace_back(u,w);
    }
    cout << Prim();
    return 0;
}