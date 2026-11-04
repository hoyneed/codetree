#include <array>
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;
namespace {
using LL = long long;
constexpr int MAX_N = 100'001;
constexpr LL INF = LLONG_MAX / 4;
int N,M,K;
int cnt;
using Edge = pair<int,int>;
priority_queue<Edge,vector<Edge>,greater<>> pq;
array<vector<Edge> ,MAX_N> graph;
array<LL, MAX_N> dist;

LL Prim() {
    LL total = 0;
    while(!pq.empty()) {
        if(cnt == N) break;
        const auto [w, u] = pq.top();
        pq.pop();
        if(w != dist[u]) continue;
        dist[u] = 0;
        total += w;
        for(const auto& [nw,v] : graph[u]) {
            if(dist[v] <= nw) continue;
            dist[v] = nw;
            pq.emplace(nw,v);
        }
    }
    return total;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    fill_n(dist.begin()+1, N, INF);
    cnt = 0;
    for(int i=0;i<K;++i) {
        int u;
        cin >> u;
        pq.emplace(0,u);
        dist[u] = 0;
        ++cnt;
    }
    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].emplace_back(w,v);
        graph[v].emplace_back(w,u);
    }
    cout << Prim();

    return 0;
}