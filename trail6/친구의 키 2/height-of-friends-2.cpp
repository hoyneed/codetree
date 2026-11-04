#include <iostream>
#include <vector>
#include <array>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N, M;
array<int,MAX_N> indegree;
array<vector<int>, MAX_N> graph;
vector<int> order;
} // namespace

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
    order.reserve(N);
    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            order.push_back(i);
        }
    }
    for(int i=0;i<(int)order.size();++i) {
        const int u = order[i];
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                order.push_back(v);
            }
        }
    }
    cout <<  (N == (int)order.size() ? "Consistent" : "Inconsistent");
    return 0;
}