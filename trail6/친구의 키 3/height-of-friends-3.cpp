#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<int,MAX_N> indegree;
array<vector<int>,MAX_N> graph;
vector<int> order;
void Build() {
    order.reserve(N);
    priority_queue<int,vector<int>,greater<>> pq;
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            pq.push(i);
        }
    }
    while(!pq.empty()) {
        const int u = pq.top();
        pq.pop();
        order.push_back(u);
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                pq.push(v);
            }
        }
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        ++indegree[v];
    }
    Build();
    if(N == (int)order.size()) {
        for(const int i : order) {
            cout << i << ' ';
        }
    } else {
        cout << -1;
    }
    return 0;
}