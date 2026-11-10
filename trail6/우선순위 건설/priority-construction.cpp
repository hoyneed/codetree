#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 501;
int N;
array<int, MAX_N> indegree;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> times;
array<int, MAX_N> dp;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        cin >> times[i];
        int u;
        for(cin >> u; u != -1; cin >> u) {
            graph[u].push_back(i);
            ++indegree[i];
        }
    }
    fill_n(dp.begin()+1, N, -1);
    queue<int> q;
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            dp[i] = times[i];
            q.push(i);
        }
    }
    int answer = 0;
    while(!q.empty()) {
        const int u = q.front();
        q.pop();
        for(const int v : graph[u]) {
            dp[v] = max(dp[v], dp[u] + times[v]);
            if(--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    for(int i = 1;i <= N; ++i) {
        cout << dp[i] << '\n';
    }
    return 0;
}