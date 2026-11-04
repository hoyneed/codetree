#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;
namespace {
using LL = long long;
constexpr int MAX_N = 100'001;
constexpr LL INF = LLONG_MAX / 4;
int N,M,K;
using Edge = pair<int,int>;
array<vector<Edge>,MAX_N> graph;
array<LL,MAX_N> dist;

LL Prim() {
    LL total = 0;
    fill_n(dist.begin()+1, N, INF);
    dist[1] = 0;
    priority_queue<Edge,vector<Edge>,greater<>> pq;
    pq.emplace(0,1);
    while(!pq.empty()) {
        const auto [w,u] = pq.top();
        pq.pop();
        if(w != dist[u]) continue;
        total += w;
        dist[u] = 0;
        for(const auto& [nw, v] : graph[u]) {
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
    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].emplace_back(w,v);
        graph[v].emplace_back(w,u);
    }
    const LL answer = 1LL * (N-1) * (N-2) / 2 * K + Prim();
    cout << answer;
    return 0;
}