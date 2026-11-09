#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<int, MAX_N> outdegree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> dp;
array<int, MAX_N> nx;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v;
        cin >> u >> v;
        ++outdegree[u];
        graph[v].push_back(u);
    }
    dp[N] = 1;
    queue<int> q;
    for(int i=1;i<=N;++i) {
        if (outdegree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        const int u = q.front();
        q.pop();
        for(const int v : graph[u]) {
            if(dp[u]) {
                if(dp[u] + 1 > dp[v]) {
                    dp[v] = dp[u] + 1;
                    nx[v] = u;
                } else if (dp[u] + 1 == dp[v] && nx[v] > u) {
                    nx[v] = u;
                }
            }
            if(--outdegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if(!dp[1]) {
        cout << -1;
    } else {
        cout << dp[1] << '\n';
        int node = 1;
        while(node != N) {
            cout << node << ' ';
            node = nx[node];
        }
        cout << N;
    }
    return 0;
}