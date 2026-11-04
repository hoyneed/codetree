#include <iostream>
#include <queue>
#include <array>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 32001;
int N,M;
array<int,MAX_N> indegree;
array<vector<int>,MAX_N> graph;
priority_queue<int,vector<int>,greater<>> pq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v;
        cin >> u >> v;
        ++indegree[v];
        graph[u].push_back(v);
    }
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0){
            pq.push(i);
        }
    }
    while(!pq.empty()) {
        const int u = pq.top();
        pq.pop();
        cout << u << ' ';
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                pq.push(v);
            }
        }
    }
    return 0;
}