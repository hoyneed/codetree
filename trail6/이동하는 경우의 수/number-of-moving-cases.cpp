#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
constexpr int NEG_INF = INT_MIN / 2;
int N,M;
using Edge = tuple<int, int, int>;
array<int, MAX_N> indegree;
array<vector<Edge>, MAX_N> graph;
array<vector<Edge>, MAX_N> rev;
array<int, MAX_N> max_dist;
array<bool, MAX_N> visited;
array<bool, MAX_N> vv;
int cnt;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=0;i<M;++i){
        int u,v,c;
        cin >> u >> v >> c;
        graph[u].emplace_back(i, v,c);
        rev[v].emplace_back(i, u,c);
        ++indegree[v];
    }
    fill_n(max_dist.begin() + 1, N, NEG_INF);
    queue<pair<int,int>> q;
    max_dist[1] = 0;
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            q.emplace(i, max_dist[i]);
        }
    }
    while(!q.empty()) {
        const auto [u,w] = q.front();
        q.pop();
        for(const auto [idx, v, nw] : graph[u]) {
            if(max_dist[u] >= 0) {
                if(w + nw > max_dist[v]) {
                    max_dist[v] = w + nw;
                }
            }
            if(--indegree[v] == 0) {
                q.emplace(v,max_dist[v]);
            }
        }
    }
    cnt = 0;
    queue<int> que;
    vv[N] = true;
    que.push(N);
    while(!que.empty()) {
        const int u = que.front();
        que.pop();
        if(u == 1) continue;
        for(const auto [idx, v, w] : rev[u]) {
            if(!visited[idx] && max_dist[u] - w == max_dist[v]) {
                visited[idx] = true;
                ++cnt;
                if(!vv[v]){
                    vv[v] = true;
                    que.push(v);
                }         
            }
        }
    }
    cout << max_dist[N] << ' ' << cnt;
    return 0;
}