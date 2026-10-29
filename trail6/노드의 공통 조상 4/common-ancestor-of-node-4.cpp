#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;
constexpr int LOG = 17;
int N, Q;
array<vector<int>,MAX_N> graph;
array<array<int, LOG>,MAX_N> up;
array<int,MAX_N> depth;
void Build() {
    // 루트는 1번
    queue<int> q;
    q.push(1);

    depth[1] = 0;

    // 1. BFS로 부모와 깊이 계산
    while(!q.empty()) {
        const int cur = q.front();
        q.pop();

        for (const int next : graph[cur]) {
            if (next == up[cur][0]) continue;

            up[next][0] = cur;
            depth[next] = depth[cur] + 1;

            q.push(next);
        }
    }

    // 2. Binary Lifting 테이블 계산
    for (int k = 1; k < LOG; ++k) {
        for (int v = 1; v <= N; ++v) {
            const int mid = up[v][k - 1];

            up[v][k] = up[mid][k - 1];
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
    if (a == b)
        return a;

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

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    Build();

    cin >> Q;

    while (Q--) {
        int a, b;
        cin >> a >> b;

        cout << LCA(a, b) << '\n';
    }

    return 0;
}