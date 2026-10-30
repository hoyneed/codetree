#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

namespace {
using LL = long long;
constexpr int MAX_N = 100'001;
constexpr int LOG = 18;

using Edge = pair<int,int>;

int N, Q;

array<vector<Edge>,MAX_N> graph;
array<array<int, LOG>,MAX_N> up;
array<int,MAX_N> depth;
array<LL,MAX_N> dist;

void Build() {
    vector<int> st;
    st.reserve(N);
    st.push_back(1);

    while (!st.empty()) {
        const int u = st.back();
        st.pop_back();

        for (const auto& [v, w] : graph[u]) {
            if (v == up[u][0])
                continue;

            // 부모와 깊이
            up[v][0] = u;
            depth[v] = depth[u] + 1;

            // 루트부터의 누적 가중치
            dist[v] = dist[u] + w;

            // Binary Lifting 테이블
            for (int k = 1; k < LOG; ++k) {
                up[v][k] = up[up[v][k - 1]][k - 1];
            }

            st.push_back(v);
        }
    }
}

int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // 1. 깊이 맞추기
    int diff = depth[a] - depth[b];

    for (int k = 0; k < LOG; ++k) {
        if (diff & (1 << k)) {
            a = up[a][k];
        }
    }

    if (a == b) return a;

    // 2. LCA 바로 아래까지 이동
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }

    return up[a][0];
}

LL GetDistance(int a, int b) {
    const int lca = LCA(a, b);

    return dist[a] + dist[b] - 2LL * dist[lca];
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    Build();

    cin >> Q;

    while (Q--) {
        int a, b;
        cin >> a >> b;

        cout << GetDistance(a, b) << '\n';
    }

    return 0;
}