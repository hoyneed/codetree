#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
using Process = pair<int,int>;
array<int,MAX_N> indegree;
array<int,MAX_N> times;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> dp;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    queue<int> q;
    for(int i=1;i<=N;++i) {
        int p;
        cin >> times[i] >> p;
        indegree[i] = p;
        if(p == 0) {
            dp[i] = times[i];
            q.push(i);
        }
        while(p--) {
            int v;
            cin >> v;
            graph[v].push_back(i);
        }
    }
    int answer = 0;
    while(!q.empty()) {
        const int u = q.front();
        q.pop();
        answer = max(answer, dp[u]);
        for(const int v : graph[u]) {
            dp[v] = max(dp[v], dp[u] + times[v]);
            if(--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << answer;
    return 0;
}