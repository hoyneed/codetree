#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
array<int,MAX_N> tree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> parent;
vector<int> order;
// dp[i][0] : i번 노드를 선택했을 때 최댓값, dp[i][1]: i번 노드를 선택하지 않았을 때 최댓값
array<array<int,2>,MAX_N> dp;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        cin >> tree[i];
    }
    if(N == 1){
        cout << tree[1];
        return 0;
    }
    for(int i=1;i<N;++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    order = {1};
    order.reserve(N);
    for(int i=0;i<(int)order.size();++i) {
        const int cur = order[i];
        for(const int next : graph[cur]) {
            if(parent[cur] == next) continue;
            parent[next] = cur;
            order.push_back(next);
        }
    }
    for(int i=N-1;i>=0;--i) {
        const int cur = order[i];
        dp[cur][0] = tree[cur];
        for(const int child : graph[cur]) {
            if(parent[cur] == child) continue;
            dp[cur][0] += dp[child][1];
            dp[cur][1] += max(dp[child][0], dp[child][1]);
        }
    }
    cout << max(dp[1][0],dp[1][1]);
    return 0;
}