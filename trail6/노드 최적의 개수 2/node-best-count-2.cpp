#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
constexpr int INF = 200'000;
int N,M;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> parent;
vector<int> order;
array<bool, MAX_N> has_item;
// dp[i][0] : i번 노드에 물건이 없을 때 최소 개수
// dp[i][1] : i번 노드에 물건이 있을 때 최소 개수
array<array<int,2>,MAX_N> dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    while(M--) {
        int u;
        cin >> u;
        has_item[u] = true;
    }
    order.reserve(N);
    order.push_back(1);
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
        if(has_item[cur] == true) {
            dp[cur][0] = INF;
            dp[cur][1] = 0;
            for(const int next : graph[cur]) {
                if(parent[cur] == next) continue;
                dp[cur][1] += min(dp[next][0], dp[next][1]);
            }
        } else {
            dp[cur][0] = 0;
            dp[cur][1] = 1;
            for(const int next : graph[cur]) {
                if(parent[cur] == next) continue;
                dp[cur][0] += dp[next][1];
                dp[cur][1] += min(dp[next][0], dp[next][1]);
            }
        }
    }
    cout << min(dp[1][0],dp[1][1]);
    return 0;
}