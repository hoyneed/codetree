#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N, R;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> tree;
array<int, MAX_N> parent;
array<int, MAX_N> sz;
vector<int> order;
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> R;
  for (int i = 1; i < N; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  int root = -1;
  if (graph[R].size() > 1) {
    root = R;
  } else {
    queue<int> q;
    q.push(R);
    parent[R] = 0;
    while (!q.empty()) {
      const int cur = q.front();
      q.pop();
      if (graph[cur].size() > 2) {
        root = cur;
        break;
      }
      for (const int next : graph[cur]) {
        if (parent[cur] == next) continue;
        parent[next] = cur;
        q.push(next);
      }
    }
  }
  if (root == -1) root = N;
  order = {root};
  order.reserve(N);
  parent[root] = 0;
  for (int i = 0; i < (int)order.size(); ++i) {
    const int cur = order[i];
    for (const int next : graph[cur]) {
      if (next == parent[cur]) continue;
      parent[next] = cur;
      order.push_back(next);
    }
  }
  for (int i = N - 1; i > 0; --i) {
    const int cur = order[i];
    sz[parent[cur]] += ++sz[cur];
  }
  ++sz[root];
  int max_size = 0;
  int min_size = N;
  for (const int node : graph[root]) {
    max_size = max(max_size, sz[node]);
    min_size = min(min_size, sz[node]);
  }
  cout << max_size - min_size;
  return 0;
}