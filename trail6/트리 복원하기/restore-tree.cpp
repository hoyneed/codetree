#include <iostream>
#include <array>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 501;
constexpr int INF = 1e9;
int N;
using Edge = tuple<int,int,int>;
array<array<int,MAX_N>,MAX_N> graph;
array<int,MAX_N> dist;
vector<Edge> edges;

void Build() {
    edges.reserve(N);
    priority_queue<Edge,vector<Edge>,greater<>> pq;
    int cnt = 1;
    for(int i=1;i<=N;++i) {
        dist[i] = graph[1][i];
        if(i != 1)
            pq.emplace(dist[i],1,i);
    }
    while(!pq.empty()) {
        if(cnt == N) break;
        const auto [w,u,v] = pq.top();
        pq.pop();
        if(w != dist[v]) continue;
        dist[v] = 0;
        edges.emplace_back(u < v ? u : v, u < v ? v : u, w);
        ++cnt;
        for(int next = 2;next <= N;++next) {
            if(dist[next] <= graph[v][next]) continue;
            dist[next] = graph[v][next];
            pq.emplace(dist[next],v,next);
        }
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            cin >> graph[i][j];
        }
    }
    Build();
    ranges::sort(edges);
    for(const auto& [u,v,w] : edges) {
        cout << u << ' ' << v << ' ' << w << '\n';
    }
    return 0;
}