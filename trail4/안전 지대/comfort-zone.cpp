#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_N = 50;
constexpr int DY[4]{-1, 1, 0, 0};
constexpr int DX[4]{0, 0, -1, 1};
struct Point {
  int y, x;
};

int N, M;
array<array<int, MAX_N>, MAX_N> grid;
array<array<int, MAX_N>, MAX_N> visited;
vector<Point> st;

bool IsOut(const int y, const int x) {
    return y < 0 || y >= N || x < 0 || x >= M;
}

void DFS(int sy, int sx, int k) {
  visited[sy][sx] = k;
  st.emplace_back(sy,sx);
  while (!st.empty()) {
    const auto [y, x] = st.back();
    st.pop_back();
    for (int d = 0; d < 4; ++d) {
      const int ny = y + DY[d];
      const int nx = x + DX[d];
      if (IsOut(ny,nx)) continue;
      if (visited[ny][nx] == k || grid[ny][nx] <= k) continue;
      visited[ny][nx] = k;
      st.emplace_back(ny,nx);
    }
  }
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;

  int max_h = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> grid[i][j];
      max_h = max(max_h, grid[i][j]);
    }
  }
  st.reserve(N * N);

  int best_k = 1;
  int max_zones = 0;

  for (int k = 1; k < max_h; ++k) {
    int zones = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (grid[i][j] > k && visited[i][j] != k) {
          DFS(i, j, k);
          ++zones;
        }
      }
    }
    if (zones > max_zones) {
      max_zones = zones;
      best_k = k;
    }
  }
  cout << best_k << ' ' << max_zones << '\n';
  return 0;
}