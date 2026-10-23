#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

namespace {

using LL = long long;

constexpr int MAX_K = 10;
constexpr LL NEG = -(1LL << 60);

// dp[u][k][0]: u를 선택하지 않음
// dp[u][k][1]: u를 선택함
using State = array<array<LL, 2>, MAX_K + 1>;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> graph(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<LL> weight(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> weight[i];
    }

    int K;
    cin >> K;

    // 1. 부모 -> 자식 순서 생성
    vector<int> parent(N + 1, 0);
    vector<int> order;
    order.reserve(N);

    order.push_back(1);

    for (int i = 0; i < (int)order.size(); ++i) {
        int u = order[i];

        for (int v : graph[u]) {
            if (v == parent[u]) continue;

            parent[v] = u;
            order.push_back(v);
        }
    }

    // 2. Bottom-up Tree DP
    vector<State> dp(N + 1);
    vector<int> subtreeSize(N + 1, 0);

    for (int idx = N - 1; idx >= 0; --idx) {
        int u = order[idx];

        // DP 초기화
        for (auto& state : dp[u]) {
            state = {NEG, NEG};
        }

        dp[u][0][0] = 0;
        dp[u][1][1] = weight[u];

        int size = 1;

        // 자식 서브트리를 하나씩 병합
        for (int v : graph[u]) {
            if (v == parent[u]) continue;

            State next;

            for (auto& state : next) {
                state = {NEG, NEG};
            }

            // 현재까지 선택한 정점 수
            for (int a = 0; a <= min(K, size); ++a) {

                // 자식 서브트리에서 선택할 정점 수
                for (int b = 0;b <= min(K - a, subtreeSize[v]);++b) {

                    // u를 선택하지 않는 경우
                    LL childBest = max(dp[v][b][0], dp[v][b][1]);

                    if (dp[u][a][0] != NEG && childBest != NEG) {
                        next[a + b][0] = max(next[a + b][0], dp[u][a][0] + childBest);
                    }

                    // u를 선택하는 경우
                    // v는 반드시 선택하지 않아야 함
                    if (dp[u][a][1] != NEG && dp[v][b][0] != NEG) {
                        next[a + b][1] = max(next[a + b][1], dp[u][a][1] + dp[v][b][0]);
                    }
                }
            }

            dp[u] = next;
            size += subtreeSize[v];
        }

        subtreeSize[u] = size;
    }

    // 3. 최대 K개이므로 1~K개 중 최댓값
    LL answer = 0;

    for (int k = 1; k <= K; ++k) {
        answer = max({answer,dp[1][k][0], dp[1][k][1]});
    }

    cout << answer;

    return 0;
}