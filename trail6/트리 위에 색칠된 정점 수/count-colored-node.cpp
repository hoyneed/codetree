#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <ranges>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
constexpr int LOG = 18;
int N,K,Q;
array<vector<int>,MAX_N> graph;
array<int, MAX_N> depth;
array<bool, MAX_N> colored;
array<int, MAX_N> cnt;
array<array<int, LOG>, MAX_N> up;

void Build() {
    vector<int> st{1};
    st.reserve(N);
    depth[1] = 0;
    cnt[1] = (int)colored[1];
    while(!st.empty()) {
        const int u = st.back();
        st.pop_back();
        for(const int v : graph[u]) {
            if(v == up[u][0]) continue;
            up[v][0] = u;
            cnt[v] = cnt[u] + (int)colored[v];
            depth[v] = depth[u] + 1;
            for(int k=1;k<LOG;++k) {
                up[v][k] = up[up[v][k-1]][k-1];
            }
            st.push_back(v);
        }
    }
}

int LCA(int a,int b) {
    if(depth[a] < depth[b]) swap(a,b);
    const int diff = depth[a] - depth[b];
    for(const int k : views::iota(0,LOG)) {
        if(diff & (1 << k)) {
            a = up[a][k];
        }
    }
    if(a == b) return a;
    for(int k=LOG-1;k>=0;--k) {
        if(up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }
    return up[a][0];
}

int Query(const int a, const int b) {
    const int lca = LCA(a,b);
    return cnt[a] + cnt[b] - 2*cnt[lca] + (int)colored[lca];
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cin >> K;
    for(int i=0;i<K;++i) {
        int u;
        cin >> u;
        colored[u] = true;
    }
    Build();
    cin >> Q;
    while(Q--) {
        int a,b;
        cin >> a >> b;
        cout << Query(a,b) << '\n';
    }
    return 0;
}