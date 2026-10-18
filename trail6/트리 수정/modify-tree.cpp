#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <array>
#include <tuple>

using namespace std;
namespace {
constexpr int MAX_N = 2'000;
using LL = long long;
using Edge = tuple<int,int,int>;
using State = tuple<int,int,LL>;

int N;
array<vector<Edge>, MAX_N> graph;
array<Edge,MAX_N> edges;

// 특정 간선을 제거했다고 가정하고 start에서 가장 먼 정점과 거리 반환
pair<int, LL> Farthest(const int start, const int banned) {
    queue<State> qu;
    qu.emplace(start, -1, 0);

    pair<int, LL> ret = {start, 0};

    while (!qu.empty()) {
        const auto [cur,parent,dist] = qu.front();
        qu.pop();

        if (dist > ret.second) {
            ret = {cur, dist};
        }

        for (const auto [id,to,weight] : graph[cur]) {
            // 제거한 간선은 통과 불가
            if (id == banned) continue;
            if (to == parent) continue;

            qu.emplace(to, cur, dist + weight);
        }
    }

    return ret;
}

// start가 속한 컴포넌트의 지름 계산
LL Diameter(const int start, const int banned) {
    int a = Farthest(start, banned).first;

    return Farthest(a, banned).second;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].emplace_back(i, v, w);
        graph[v].emplace_back(i, u, w);
        edges[i] = {u, v, w};
    }

    LL answer = 0;

    // 모든 간선을 하나씩 제거해 본다.
    for (int i = 0; i < N - 1; ++i) {
        const auto [u,v,weight] = edges[i];

        // 간선 i를 제거하면 u와 v는 서로 다른 컴포넌트에 속함
        LL diamA = Diameter(u, i);
        LL diamB = Diameter(v, i);

        // 두 지름의 끝점을 연결하는 것이 최적
        LL candidate = diamA + diamB + weight;
        answer = max(answer, candidate);
    }

    cout << answer;

    return 0;
}