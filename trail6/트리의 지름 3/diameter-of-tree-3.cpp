#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <array>

using namespace std;

namespace {
using LL = long long;
constexpr int MAX_N = 100'001;
using Edge = pair<int,int>;

int N;
array<vector<Edge>,MAX_N> graph;

// start에서 모든 정점까지의 거리
vector<LL> BFS(int start) {
    vector<LL> dist(N + 1, -1);
    queue<int> qu;

    dist[start] = 0;
    qu.push(start);

    while (!qu.empty()) {
        int cur = qu.front();
        qu.pop();

        for (const auto [to, cost] : graph[cur]) {
            if (dist[to] != -1)
                continue;

            dist[to] = dist[cur] + cost;
            qu.push(to);
        }
    }

    return dist;
}

int FindFarthest(const vector<LL>& dist) {
    return max_element(dist.begin() + 1,dist.end()) - dist.begin();
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

    // 1. 임의의 정점에서 지름의 한 끝점 A 찾기
    const int A = FindFarthest(BFS(1));

    // 2. A에서 모든 정점까지 거리 계산
    const vector<LL> distA = BFS(A);

    // 3. 지름의 다른 끝점 B 찾기
    const int B = FindFarthest(distA);

    // 4. B에서 모든 정점까지 거리 계산
    const vector<LL> distB = BFS(B);

    LL answer = 0;

    // 5. 지름 쌍 (A,B)를 제외하고 최대 거리 탐색
    for (int v = 1; v <= N; ++v) {
        if (v == A || v == B) continue;
        answer = max({answer, distA[v], distB[v]});
    }

    cout << answer;

    return 0;
}