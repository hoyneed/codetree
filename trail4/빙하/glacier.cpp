#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <utility>
using namespace std;
namespace {
constexpr int MAX_N = 201;
constexpr int DY[4]{-1, 0, 1, 0};
constexpr int DX[4]{0, -1, 0, 1};
int N, M;
using Pos = pair<int, int>;
int ice;
array<array<bool, MAX_N>, MAX_N> grid;
array<array<bool, MAX_N>, MAX_N> temp;
array<array<bool, MAX_N>, MAX_N> visited;
deque<Pos> dq;

bool IsOut(const int y, const int x) {
  return y < 0 || x < 0 || y >= N || x >= M;
}

void FillQueue() {
  for (int i = 0; i < (int)dq.size(); ++i) {
    const auto [y, x] = dq[i];
    for (int d = 0; d < 4; ++d) {
      const int ny = y + DY[d];
      const int nx = x + DX[d];
      if (IsOut(ny, nx) || visited[ny][nx] || grid[ny][nx]) continue;
      visited[ny][nx] = true;
      dq.emplace_back(ny, nx);
    }
  }
}
bool Proceed(int& melted) {
  melted = 0;
  for (int i = 0; i < (int)dq.size(); ++i) {
    const auto [y, x] = dq[i];
    for (int d = 0; d < 4; ++d) {
      const int ny = y + DY[d];
      const int nx = x + DX[d];
      if (IsOut(ny, nx) || !temp[ny][nx]) continue;
      temp[ny][nx] = false;
      ++melted;
      --ice;
    }
  }
  if (ice == 0) {
    return false;
  }
  for (int i = 0; i < N; ++i) {
    copy_n(temp[i].begin(), M, grid[i].begin());
  }
  int sz = dq.size();
  FillQueue();
  while (sz--) {
    dq.pop_front();
  }
  return true;
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  ice = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> grid[i][j];
      if (grid[i][j]) ++ice;
    }
  }
  for (int i = 0; i < N; ++i) {
    copy_n(grid[i].begin(), M, temp[i].begin());
  }
  dq.emplace_back(0, 0);
  visited[0][0] = true;
  FillQueue();
  int melted;
  int time = 1;
  while (Proceed(melted)) {
    ++time;
  }
  cout << time << ' ' << melted;

  return 0;
}