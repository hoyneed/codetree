#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;
int N, S, D;

array<vector<int>, MAX_N> graph;
array<int, MAX_N> parent;
array<int, MAX_N> height;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> S >> D;

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 1. S를 루트로 하는 트리의 순회 순서 생성
    vector<int> order;
    order.reserve(N);
    order.push_back(S);

    for (int i = 0; i < (int)order.size(); ++i) {
        const int cur = order[i];

        for (const int next : graph[cur]) {
            if (next == parent[cur]) continue;

            parent[next] = cur;
            order.push_back(next);
        }
    }

    // 2. Bottom-up DP로 각 정점의 높이 계산
    for (int i = N - 1; i >= 0; --i) {
        int cur = order[i];

        for (int next : graph[cur]) {
            if (next == parent[cur])
                continue;

            height[cur] = max(height[cur], height[next] + 1);
        }
    }

    // 3. 실제 방문해야 하는 정점 개수 계산
    int answer = 0;

    for (int i = 1; i <= N; ++i) {
        if (i == S) continue;
        if (height[i] >= D) answer += 2;
    }

    cout << answer;

    return 0;
}