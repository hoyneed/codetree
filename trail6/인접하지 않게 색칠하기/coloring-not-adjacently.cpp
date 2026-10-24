#include <iostream>
#include <array>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

namespace {
using LL = long long;

constexpr int MAX_N = 100'001;
constexpr int MAX_K = 10;
constexpr LL NEG = LLONG_MIN / 4;

int N, K;

array<int, MAX_N> tree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> parent;
vector<int> order;

// dp[u][0][k]: u를 선택하지 않고 정확히 k개 선택
// dp[u][1][k]: u를 선택하고 정확히 k개 선택
array<array<array<LL, MAX_K + 1>, 2>, MAX_N> dp;

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) {
        cin >> tree[i];
    }

    cin >> K;

    order.reserve(N);
    order.push_back(1);

    for (int i = 0; i < (int)order.size(); ++i) {
        const int cur = order[i];

        for (const int next : graph[cur]) {
            if (parent[cur] == next)
                continue;

            parent[next] = cur;
            order.push_back(next);
        }
    }

    // Bottom-up Tree DP
    for (int u = N - 1; u >= 0; --u) {
        const int cur = order[u];

        dp[cur][0].fill(NEG);
        dp[cur][1].fill(NEG);

        dp[cur][0][0] = 0;
        dp[cur][1][1] = tree[cur];

        for (const int next : graph[cur]) {
            if (parent[cur] == next)
                continue;

            // 내림차순으로 순회
            for (int i = K; i >= 1; --i) {
                for (int j = 1; j <= i; ++j) {

                    // cur를 선택하지 않은 경우
                    const LL childBest = max(
                        dp[next][0][j],
                        dp[next][1][j]
                    );

                    if (dp[cur][0][i-j] != NEG && childBest != NEG) {

                        dp[cur][0][i] = max(
                            dp[cur][0][i],
                            dp[cur][0][i-j] + childBest
                        );
                    }

                    // cur를 선택한 경우
                    // next는 반드시 선택하지 않아야 함
                    if (dp[cur][1][i-j] != NEG && dp[next][0][j] != NEG) {

                        dp[cur][1][i] = max(
                            dp[cur][1][i],
                            dp[cur][1][i-j] + dp[next][0][j]
                        );
                    }
                }
            }
        }
    }

    LL answer = 0;

    for (int i = 0; i <= K; ++i) {
        answer = max({answer, dp[1][0][i], dp[1][1][i]});
    }

    cout << answer;

    return 0;
}