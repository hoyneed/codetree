#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
namespace {
constexpr int MAX_N = 1001;
int N,M;
array<int, MAX_N> indegree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> dp;
array<bool, MAX_N> extra;
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
    queue<int> q;
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            dp[i] = 1;
            q.push(i);
        }
    }
    int answer = 0;
    while(!q.empty()) {
        const int u = q.front();
        q.pop();
        answer = max(answer, dp[u]);
        for(const int v : graph[u]) {
            if(dp[v] < dp[u]) {
                dp[v] = dp[u];
                extra[v] = false;
            } else if (dp[v] == dp[u]) {
                extra[v] = true;
            }
            if(--indegree[v] == 0) {
                if(extra[v]) ++dp[v];
                q.push(v);
            }
        }
    }
    cout << answer;
    return 0;
}