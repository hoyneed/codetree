#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M1,M2;
using Edge = pair<int,int>;
array<vector<int>,MAX_N> graph;
array<int,MAX_N> indegree;
vector<int> order;
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M1 >> M2;
    while(M1--) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        ++indegree[v];
    }
    // 양방향은 고려할 필요 없음
    order.reserve(N);

    for(int i=1;i<=N;++i) {
        if(indegree[i] == 0) {
            order.push_back(i);
        }
    }
    for(int i=0;i<(int)order.size();++i) {
        const int u = order[i];
        for(const int v: graph[u]) {
            if(--indegree[v] == 0) {
                order.push_back(v);
            }
        }
    }
    cout << (N == (int)order.size() ? "Yes" : "No");

    return 0;
}