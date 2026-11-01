#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

using LL = long long;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent;
    vector<int> rk;

    explicit DSU(int n)
        : parent(n), rk(n,0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);

        if (a == b) return false;

        if (rk[a] < rk[b]) swap(a, b);
        else if(rk[a] == rk[b]) ++rk[a];
        parent[b] = a;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<array<int, 3>> points(N);

    for (auto& [x, y, z] : points) {
        cin >> x >> y >> z;
    }

    vector<Edge> edges;
    edges.reserve(3 * (N - 1));

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);

    // x, y, z 좌표별 정렬
    for (int axis = 0; axis < 3; ++axis) {

        ranges::sort(order,
            [&](int a, int b) {
                return points[a][axis] < points[b][axis];
            }
        );

        // 정렬 결과에서 인접한 점들만 간선 생성
        for (int i = 1; i < N; ++i) {
            const int u = order[i - 1];
            const int v = order[i];

            // 문제에서 정의한 실제 간선 비용
            const int w = min({
                abs(points[u][0] - points[v][0]),
                abs(points[u][1] - points[v][1]),
                abs(points[u][2] - points[v][2])
            });

            edges.emplace_back(u, v, w);
        }
    }

    // 크루스칼: 간선 가중치 오름차순 정렬
    ranges::sort(edges,
        [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        }
    );

    DSU dsu(N);

    LL answer = 0;
    int selected = 0;

    for (const auto& [u, v, w] : edges) {

        if (!dsu.Union(u, v))
            continue;

        answer += w;
        ++selected;

        // MST 완성
        if (selected == N - 1) break;
    }

    cout << answer;

    return 0;
}