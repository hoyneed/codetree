#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
#include <bit>

using namespace std;

namespace {
constexpr int MAX_N = 12;
constexpr int MAX_M = 15;

struct Line {
  int a, b;
  auto operator<=>(const Line& other) const {
    return b <=> other.b;  // 위에서부터 내려오므로 높이(b) 기준 오름차순 정렬
  }
};

int N, M;
array<Line, MAX_M> lines;
array<int, MAX_N> target;

// mask에 포함된 가로줄만 사용하여 사다리 결과를 시뮬레이션
array<int, MAX_N> simulate(const int mask) {
  array<int, MAX_N> res{};
  iota(res.begin() + 1, res.begin() + N + 1, 1);

  for (int i = 0; i < M; ++i) {
    if (mask & (1 << i)) {
      swap(res[lines[i].a], res[lines[i].a + 1]);
    }
  }
  return res;
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;

  for (int i = 0; i < M; ++i) {
    cin >> lines[i].a >> lines[i].b;
  }

  sort(lines.begin(), lines.begin() + M);

  // 모든 가로줄을 사용했을 때의 초기 결과 계산
  const int total_masks = 1 << M;
  target = simulate(total_masks - 1);

  // 역전 쌍 개수 = 초기 결과를 만들기 위한 이론상 최소 인접 스왑 수
  int min_possible = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = i + 1; j <= N; ++j) {
      if (target[i] > target[j]) ++min_possible;
    }
  }

  int ans = M;

  for (uint32_t mask = 0; mask < total_masks; ++mask) {
    int cnt = popcount(mask);
    if (cnt >= ans || cnt < min_possible) continue;

    if (simulate(mask) == target) {
      ans = cnt;
      if (ans == min_possible) break;  // 이론적 최솟값 도달 시 조기 종료
    }
  }

  cout << ans << '\n';
  return 0;
}