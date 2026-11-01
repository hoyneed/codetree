#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
using Edge = pair<int,int>;
using LL = long long;
array<vector<Edge>,MAX_N> graph;
array<bool,MAX_N> visited;

LL Prim() {
    visited[1] = true;
    priority_queue<Edge,vector<Edge>,greater<>> pq;
    for(const auto e : graph[1]) {
        pq.push(e);
    }
    LL total = 0;
    int cnt = 1;
    while(!pq.empty() && cnt != N) {
        const auto [w,u] = pq.top();
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        total += w;
        ++cnt;
        for(const auto& [c,v] : graph[u]) {
            if(visited[v]) continue;
            pq.emplace(c,v);
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
        graph[u].emplace_back(w,v);
        graph[v].emplace_back(w,u);
    }
    cout << Prim();
    return 0;
}