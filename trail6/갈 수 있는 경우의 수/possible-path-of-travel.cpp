#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;
constexpr int MOD = 1'000'000'007;

int N, M;
array<int, MAX_N> indegree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        ++indegree[v];
    }

    dp[1] = 1;

    queue<int> q;

    // 진입 차수가 0인 모든 정점 삽입
    for (int i = 1; i <= N; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        const int u = q.front();
        q.pop();

        for (const int v : graph[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;

            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    cout << dp[N];

    return 0;
}