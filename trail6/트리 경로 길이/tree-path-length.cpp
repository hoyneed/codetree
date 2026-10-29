#include <iostream>
#include <array>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
constexpr int LOG = 18;
int N, Q;
array<vector<int>, MAX_N> graph;
array<array<int,LOG>, MAX_N> up;
array<int, MAX_N> depth;

void Build() {
    vector<int> st = {1};
    depth[1] = 0;

    while(!st.empty()) {
        const int cur = st.back();
        st.pop_back();

        for(const int next : graph[cur]) {
            if(next == up[cur][0]) continue;
            up[next][0] = cur;
            depth[next] = depth[cur]+1;
            for(int k=1;k<LOG;++k) {
                up[next][k] = up[up[next][k-1]][k-1];
            }
            st.push_back(next);
        }
    }
}

int Query(int a, int b) {
    if(depth[a] < depth[b]) swap(a,b);
    const int da = depth[a], db = depth[b];
    const int diff = da - db;
    for(int k=0;k<LOG;++k) {
        if(diff & (1 << k)) {
            a = up[a][k];
        }
    }
    if(a == b) {
        return 1 + da - depth[a];
    }

    for(int k=LOG-1;k>=0;--k) {
        if(up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }
    return 1 - depth[up[a][0]] * 2 + da + db;
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
    Build();
    cin >> Q;
    while(Q--) {
        int u,v;
        cin >> u >> v;
        cout << Query(u,v) << '\n';
    }
    return 0;
}