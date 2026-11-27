#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <climits>
#include <numeric>

using namespace std;

namespace {
constexpr int MAX_2N = 20;

int N;
int total_sum = 0;
int min_diff = INT_MAX;
array<int, MAX_2N> arr;

void DFS(const int idx, const int cnt,const int cur_sum) {
  if (min_diff <= (total_sum & 1)) return;  // 이론적 최솟값(0 또는 1) 도달 시 조기 종료

  if (cnt == N) {
    min_diff = min(min_diff, abs(total_sum - 2 * cur_sum));
    return;
  }

  // 남은 원소를 전부 뽑아도 N개를 채울 수 없는 경우 가지치기
  if (2 * N - idx < N - cnt) return;

  // 현재 원소를 첫 번째 그룹에 포함
  DFS(idx + 1, cnt + 1, cur_sum + arr[idx]);
  // 현재 원소를 두 번째 그룹에 포함
  DFS(idx + 1, cnt, cur_sum);
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  const int total_cnt = 2 * N;
  for (int i = 0; i < total_cnt; ++i) {
    cin >> arr[i];
  }

  total_sum = accumulate(arr.begin(), arr.begin() + total_cnt, 0);

  DFS(1, 1, arr[0]);

  cout << min_diff << '\n';
  return 0;
}