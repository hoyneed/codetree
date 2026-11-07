#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<int, MAX_N> outdegree;
array<vector<int>, MAX_N> graph;
vector<int> order;
int cnt;

void Build() {
    priority_queue<int> pq;
    order.assign(N+1,0);
    cnt = N;
    for(int i=1;i<=N;++i) {
        if(outdegree[i] == 0){
            pq.push(i);
        }
    }
    while(!pq.empty()) {
        const int u = pq.top();
        pq.pop();
        order[u] = cnt--;
        for(const int v : graph[u]) {
            if(--outdegree[v] == 0) {
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
        ++outdegree[u];
        graph[v].push_back(u);
    }
    Build();
    if(cnt == 0) {
        for(int i=1;i<=N;++i) {
            cout << order[i] << ' ';
        }
    } else {
        cout << -1;
    }

    return 0;
}