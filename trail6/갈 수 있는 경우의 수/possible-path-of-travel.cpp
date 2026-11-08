#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
constexpr int MOD = 1e9 + 7;
using LL = long long;
int N,M;
array<int, MAX_N> indegree;
array<vector<int>, MAX_N> graph;
array<LL, MAX_N> dp;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        ++indegree[v];
    }
    dp[1] = 1;
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        const int u = q.front();
        q.pop();
        for(const int v : graph[u]) {
            dp[v] += dp[u];
            dp[v] %= MOD;
            if(--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << dp[N];
    return 0;
}