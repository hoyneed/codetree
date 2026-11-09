#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 101;
int N, M;
using Edge = pair<int,int>;
array<int, MAX_N> outdegree;
array<vector<Edge>, MAX_N> graph;
array<int, MAX_N> dp;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v,c;
        cin >> u >> v >> c;
        graph[u].emplace_back(v,c);
        ++outdegree[v];
    }
    queue<int> q;
    vector<int> pieces;
    for(int i=1;i<=N;++i) {
        if(outdegree[i] == 0) {
            q.push(i);
        }
    }
    dp[N] = 1;
    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        if(graph[u].empty() && dp[u]) {
            pieces.push_back(u);
        }
        for(const auto [v, c] : graph[u]) {
            dp[v] += dp[u] * c;
            if(--outdegree[v] == 0) {
                q.push(v);
            }
        }
    }
    ranges::sort(pieces);
    for(const int p : pieces) {
        cout << p << ' ' << dp[p] << '\n';
    }
    return 0;
}