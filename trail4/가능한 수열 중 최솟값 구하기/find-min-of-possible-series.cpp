#include <iostream>
#include <string>

using namespace std;

namespace {
constexpr char nums[3]{'4', '5', '6'};
int N;
string seq;

// 마지막 문자가 추가된 상태에서 인접한 동일 부분 수열이 있는지 검사
bool IsValid() {
  const int len = seq.length();
  const int half = len / 2;

  for (int k = 1; k <= half; ++k) {
    bool same = true;
    for (int i = 0; i < k; ++i) {
      if (seq[len - 2 * k + i] != seq[len - k + i]) {
        same = false;
        break;
      }
    }
    if (same) return false;
  }
  return true;
}

// 사전순으로 가장 앞선 수열을 찾으면 true를 반환하며 즉시 종료
bool DFS() {
  if ((int)seq.length() == N) {
    cout << seq << '\n';
    return true;
  }

  for (const char ch : nums) {
    seq.push_back(ch);
    if (IsValid() && DFS()) {
      return true;
    }
    seq.pop_back();
  }
  return false;
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  seq.reserve(N);
  DFS();

  return 0;
}