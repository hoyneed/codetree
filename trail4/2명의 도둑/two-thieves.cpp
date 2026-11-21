#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

namespace {
constexpr int MAX_N = 10;

int N, M, C;
array<array<int, MAX_N>, MAX_N> grid;
array<array<int, MAX_N>, MAX_N> best;

// (r, c)부터 M개의 물건 중 무게 합 <= C를 만족하는 최대 가치 계산
int calcMaxVal(const int r, const int c) {
  int max_val = 0;
  const int total_masks = 1 << M;

  for (int mask = 1; mask < total_masks; ++mask) {
    int weight_sum = 0;
    int val_sum = 0;
    for (int i = 0; i < M; ++i) {
      if (mask & (1 << i)) {
        int w = grid[r][c + i];
        weight_sum += w;
        val_sum += w * w;
      }
    }
    if (weight_sum <= C) {
      max_val = max(max_val, val_sum);
    }
  }
  return max_val;
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M >> C;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> grid[i][j];
    }
  }

  // 1. 모든 가능한 시작 위치에 대해 최대 가치 사전 계산
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c <= N - M; ++c) {
      best[r][c] = calcMaxVal(r, c);
    }
  }

  // 2. 두 도둑의 위치 쌍 완전 탐색
  int ans = 0;
  for (int r1 = 0; r1 < N; ++r1) {
    for (int c1 = 0; c1 <= N - M; ++c1) {
      // 같은 행에서 두 번째 도둑이 겹치지 않게 선택하는 경우
      for (int c2 = c1 + M; c2 <= N - M; ++c2) {
        ans = max(ans, best[r1][c1] + best[r1][c2]);
      }
      // 다른 행(r2 > r1)에서 두 번째 도둑이 선택하는 경우
      for (int r2 = r1 + 1; r2 < N; ++r2) {
        for (int c2 = 0; c2 <= N - M; ++c2) {
          ans = max(ans, best[r1][c1] + best[r2][c2]);
        }
      }
    }
  }

  cout << ans << '\n';
  return 0;
}