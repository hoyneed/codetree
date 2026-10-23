#include <iostream>
#include <array>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> tree;
array<int, MAX_N> parent;
vector<int> order;
// dp[i][0]: i번 노드를 선택한 경우, dp[i][1]: i번 노드를 선택하지 않은 경우
array<array<int,2>,MAX_N> dp;
using Pair = pair<int,int>;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        cin >> tree[i];
    }
    for(int i=1;i<N;++i) {
        int u,v;
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
        for(const int next : graph[cur]) {
            if(parent[cur] == next) continue;
            dp[cur][0] += dp[next][1];
            dp[cur][1] += max(dp[next][0], dp[next][1]);
        }
    }
    const int answer = max(dp[1][0],dp[1][1]);
    vector<int> selected;
    selected.reserve(N/2);
    queue<Pair> q;
    q.emplace(1, true);
    while(!q.empty()) {
        const auto [node, can_select] = q.front();
        q.pop();
        if(!can_select || dp[node][0] < dp[node][1]) {
            for(const int next : graph[node]) {
                if(parent[node] == next) continue;
                q.emplace(next, true);
            }
        } else {
            selected.push_back(node);
            for(const int next : graph[node]) {
                if(parent[node] == next) continue;
                q.emplace(next,false);
            }
        }
    }
    ranges::sort(selected);
    cout << answer << '\n';
    for(const int n : selected) {
        cout << n << ' ';
    }
    return 0;
}