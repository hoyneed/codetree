#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;
constexpr int INF = 1'000'000'000;

// 0: 현재 정점에 물건이 있음
// 1: 자식에 의해 현재 정점이 커버됨
// 2: 부모가 현재 정점을 커버해야 함
using State = array<int, 3>;
int N;
array<vector<int>,MAX_N> graph;
array<State,MAX_N> dp;
int Add(int a, int b) {
    return min(INF, a + b);
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 1. 부모 -> 자식 순서 생성
    vector<int> parent(N + 1, 0);
    vector<int> order;
    order.reserve(N);

    order.push_back(1);

    for (int i = 0; i < (int)order.size(); ++i) {
        const int u = order[i];
        for (int v : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }

    // 2. Bottom-up Tree DP


    for (int i = N - 1; i >= 0; --i) {
        int u = order[i];

        int picked = 1;
        int none = 0;
        int some = INF;

        for (int v : graph[u]) {
            if (v == parent[u]) continue;

            const auto& [childPicked, childCovered,  childNeedsParent] = dp[v];

            // u에 물건이 있는 경우:
            // 자식의 세 상태 모두 허용
            picked = Add(
                picked,
                min({childPicked, childCovered, childNeedsParent})
            );

            // u에 물건이 없는 경우:
            // 자식 중 적어도 하나에 물건이 있어야 함
            int nextSome = min(
                Add(some, min(childPicked, childCovered)),
                Add(none, childPicked)
            );

            // u에도 자식에도 물건이 없는 경우
            int nextNone = Add(none, childCovered);

            some = nextSome;
            none = nextNone;
        }

        dp[u] = {picked, some, none};
    }

    // 3. 루트는 부모가 없으므로
    // dp[1][2]는 정답으로 사용할 수 없음
    cout << min(dp[1][0], dp[1][1]);

    return 0;
}