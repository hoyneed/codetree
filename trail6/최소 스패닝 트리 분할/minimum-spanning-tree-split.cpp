#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N, M;
vector<tuple<int, int, int>> edges;  // {weight, u, v}
array<int, MAX_N> parent;
array<int, MAX_N> rank;

int groups;

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
  if (rank[a] < rank[b])
    swap(a, b);
  else if (rank[a] == rank[b])
    ++rank[a];
  parent[b] = a;
  --groups;
  return true;
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  edges.reserve(M);
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
  }
  groups = N;
  iota(parent.begin(), parent.begin() + N + 1, 0);
  ranges::sort(edges);
  int answer = 0;
  for (const auto& [w, u, v] : edges) {
    if (groups == 2) break;
    if (Union(u, v)) {
      answer += w;
    }
  }
  cout << answer;
  return 0;
}