#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
namespace {
constexpr int MAX_N = 50'001;
constexpr int LOG = 17;
int N,Q;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> depth;
array<array<int,LOG>, MAX_N> up;
array<int, MAX_N> tin;

void Build() {
    // 1. DFS로 트리 깊이 완성, DFS 방문 순서 기록
    int timer = 0;
    vector<int> st = {1};
    depth[1] = 0;

    while(!st.empty()) {
        const int cur = st.back();
        st.pop_back();

        tin[cur] = ++timer;

        for(const int next : graph[cur]) {
            if(next == up[cur][0]) continue;
            up[next][0] = cur;
            depth[next] = depth[cur] + 1;
            st.push_back(next);
        }
    }

    for(int k=1;k<LOG;++k) {
        for(int u=1;u<=N;++u) {
            const int mid = up[u][k-1];
            up[u][k] = up[mid][k-1];
        }
    }
}
int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // 1. 깊이 맞추기
    const int diff = depth[a] - depth[b];

    for (int k = 0; k < LOG; ++k) {
        if (diff & (1 << k)) {
            a = up[a][k];
        }
    }

    // 한 정점이 다른 정점의 조상인 경우
    if (a == b) return a;

    // 2. 동시에 위로 이동
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }

    // 3. 공통 부모 반환
    return up[a][0];
}

int LCA3(const int a, const int b, const int c) {
    const int lo = min({a, b, c}, [](const int x, const int y) {
        return tin[x] < tin[y];
    });

    const int hi = max({a, b, c}, [](const int x, const int y) {
        return tin[x] < tin[y];
    });

    return LCA(lo, hi);
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
        int a,b,c;
        cin >> a >> b >> c;
        cout << LCA3(a,b,c) << '\n';
    }
    return 0;
}