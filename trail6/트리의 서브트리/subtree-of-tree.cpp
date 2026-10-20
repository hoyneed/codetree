#include <iostream>
#include <array>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,R,Q;
array<vector<int>, MAX_N> graph;
array<int,MAX_N> sz;
array<int, MAX_N> parent;
vector<int> order;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> R >> Q;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    order.reserve(N);
    order.push_back(R);
    for(int i=0;i<(int)order.size();++i) {
        const int cur = order[i];
        for(const auto next : graph[cur]) {
            if(next == parent[cur]) continue;
            parent[next] = cur;
            order.push_back(next);
        }
    }
    fill_n(sz.begin()+1,N,1);
    for(int i=N-1;i>0;--i) {
        const int cur = order[i];
        sz[parent[cur]] += sz[cur];
    }
    while(Q--){
        int q;
        cin >> q;
        cout << sz[q] << '\n';
    }
    return 0;
}