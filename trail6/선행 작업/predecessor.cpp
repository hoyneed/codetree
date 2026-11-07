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
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    priority_queue<Process,vector<Process>,greater<>> pq;
    for(int i=1;i<=N;++i) {
        int p;
        cin >> times[i] >> p;
        indegree[i] = p;
        if(p == 0) {
            pq.emplace(times[i], i);
        }
        while(p--) {
            int v;
            cin >> v;
            graph[v].push_back(i);
        }
    }
    int answer = 0;
    while(!pq.empty()) {
        const auto [t, u] = pq.top();
        pq.pop();
        answer = t;
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                pq.emplace(times[v] + t, v);
            }
        }
    }
    cout << answer;
    return 0;
}