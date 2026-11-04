#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

using LL = long long;
using Edge = pair<int, int>; // {next, weight}

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1, -1) {}

    int Find(const int x) {
        if(parent[x] < 0) return x;
        return parent[x] = Find(parent[x]);
    }

    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);

        if (a == b) return false;

        if (parent[a] > parent[b]) swap(a, b);
        parent[a] += parent[b];
        parent[b] = a;
        return true;
    }
};

struct WeightedEdge {
    int u, v, w;
};

// start에서 가장 먼 정점과 그 거리 반환
pair<int, LL> Farthest(int start, const vector<vector<Edge>>& tree) {
    int N = (int)tree.size() - 1;

    vector<LL> dist(N + 1, -1);
    vector<int> st;

    st.push_back(start);
    dist[start] = 0;

    int farthest = start;

    while (!st.empty()) {
        const int cur = st.back();
        st.pop_back();

        if (dist[cur] > dist[farthest])
            farthest = cur;

        for (const auto& [next, weight] : tree[cur]) {
            if (dist[next] != -1)
                continue;

            dist[next] = dist[cur] + weight;
            st.push_back(next);
        }
    }

    return {farthest, dist[farthest]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<WeightedEdge> edges(M);

    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
    }

    // 1. 간선 가중치 오름차순 정렬
    sort(edges.begin(), edges.end(),
         [](const auto& a, const auto& b) {
             return a.w < b.w;
         });

    DSU dsu(N);

    vector<vector<Edge>> tree(N + 1);

    LL mstWeight = 0;
    int selected = 0;

    // 2. Kruscal
    for (const auto& [u, v, w] : edges) {
        if (!dsu.Union(u, v))
            continue;

        mstWeight += w;

        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);

        if (++selected == N - 1)
            break;
    }

    // 3. 트리의 지름 계산
    auto [A, unused] = Farthest(1, tree);
    auto [B, diameter] = Farthest(A, tree);

    cout << mstWeight << '\n';
    cout << diameter << '\n';

    return 0;
}