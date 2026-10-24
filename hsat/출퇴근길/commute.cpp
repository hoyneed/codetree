#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<bool> BFS(
    const vector<vector<int>>& graph,int start, int blocked) {
    const int N = graph.size() - 1;

    vector<bool> visited(N + 1, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while(!q.empty()) {
        const int cur = q.front();
        q.pop();
        for (int next : graph[cur]) {
            if (next == blocked || visited[next]) continue;

            visited[next] = true;
            q.push(next);
        }
    }

    return visited;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);
    vector<vector<int>> revGraph(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        revGraph[v].push_back(u);
    }

    int S, T;
    cin >> S >> T;

    // 정방향 탐색
    auto fromS = BFS(graph, S, T);
    auto fromT = BFS(graph, T, S);

    // 역방향 탐색
    auto toT = BFS(revGraph, T, -1);
    auto toS = BFS(revGraph, S, -1);

    int answer = 0;

    for (int v = 1; v <= N; ++v) {
        if (v == S || v == T)
            continue;

        if (fromS[v] && toT[v] && fromT[v] && toS[v]) {
            ++answer;
        }
    }

    cout << answer;

    return 0;
}