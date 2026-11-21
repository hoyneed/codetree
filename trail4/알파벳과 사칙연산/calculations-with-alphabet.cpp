#include <algorithm>
#include <array>
#include <iostream>
#include <climits>
#include <string>
#include <vector>

using namespace std;

namespace {
using LL = long long;
string expr;
array<int, 6> val;
vector<int> used_chars;
LL max_ans = LLONG_MIN;

// 왼쪽에서 오른쪽으로 순서대로 수식 계산
LL Evaluate() {
  LL res = val[expr[0] - 'a'];
  const int len = (int)expr.length();

  for (int i = 1; i < len; i += 2) {
    char op = expr[i];
    LL num = val[expr[i + 1] - 'a'];

    if (op == '+') {
      res += num;
    } else if (op == '-') {
      res -= num;
    } else {
      res *= num;
    }
  }
  return res;
}

// 등장한 알파벳들에 1 ~ 4 사이의 정수를 배정하는 백트래킹
void DFS(int idx) {
  if (idx == (int)used_chars.size()) {
    max_ans = max(max_ans, Evaluate());
    return;
  }

  int ch_idx = used_chars[idx];
  for (int num = 1; num <= 4; ++num) {
    val[ch_idx] = num;
    DFS(idx + 1);
  }
}
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> expr;

  // 식에 실제로 등장하는 알파벳만 추출
  array<bool, 6> exist{};
  for (int i = 0; i < (int)expr.length(); i += 2) {
    const int ch_idx = expr[i] - 'a';
    if (!exist[ch_idx]) {
      exist[ch_idx] = true;
      used_chars.push_back(ch_idx);
    }
  }

  DFS(0);

  cout << max_ans << '\n';
  return 0;
}