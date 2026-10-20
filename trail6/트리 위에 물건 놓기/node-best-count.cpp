#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N;
array<vector<int>, MAX_N> graph;
array<int,MAX_N> parent;

// dp[u][0]: u에 물건을 놓지 않음
// dp[u][1]: u에 물건을 놓음
array<array<int, 2>, MAX_N> dp;
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> order{1};
    order.reserve(N);
    for(int i=0;i<(int)order.size();++i) {
        const int cur = order[i];
        for(const auto next : graph[cur]) {
            if(parent[cur] == next) continue;
            parent[next] = cur;
            order.push_back(next);
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        const int cur = order[i];

        dp[cur][0] = 0;
        dp[cur][1] = 1;

        for (const int next : graph[cur]) {
            if (next == parent[cur]) continue;

            // cur에 물건이 없으면
            // 자식에는 반드시 물건이 필요
            dp[cur][0] += dp[next][1];

            // cur에 물건이 있으면
            // 자식은 두 경우 중 최소 선택
            dp[cur][1] += min(dp[next][0], dp[next][1]);
        }
    }

    cout << min(dp[1][0], dp[1][1]);
    return 0;
}