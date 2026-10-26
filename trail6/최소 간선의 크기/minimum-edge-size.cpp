#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
namespace{
int N, M;
int A, B;
struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int node) {
        if (parent[node] == node) return node;
        return parent[node] = Find(parent[node]);
    }

    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }

    bool Same(int a, int b) {
        return Find(a) == Find(b);
    }
};
} // namespace

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    cin >> A >> B;

    vector<Edge> edges(M);

    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
    }

    // 만족도 내림차순 정렬
    ranges::sort(edges, ranges::greater(), &Edge::w);

    DSU dsu(N);

    for (const auto& [u, v, w] : edges) {
        dsu.Union(u, v);

        // 처음 연결되는 순간의 가중치가 정답
        if (dsu.Same(A, B)) {
            cout << w;
            break;
        }
    }

    return 0;
}