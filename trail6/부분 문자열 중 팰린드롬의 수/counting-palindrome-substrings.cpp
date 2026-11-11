#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace{
using LL = long long;
string s, t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    // 패딩된 문자열 생성
    t.reserve(2 * s.size() + 3);
    t = "^";

    for (char c : s) {
        t += '#';
        t += c;
    }

    t += "#$";

    const int N = (int)t.size();

    // p[i]: i를 중심으로 하는 팰린드롬의 반지름
    vector<int> p(N, 0);

    int center = 0;
    int right = 0;

    LL answer = 0;

    for (int i = 1; i < N - 1; ++i) {

        // 현재 위치가 기존 팰린드롬 내부라면
        // 대칭 위치의 반지름을 재활용
        if (i < right) {
            int mirror = 2 * center - i;
            p[i] = min(right - i, p[mirror]);
        }

        // 추가 확장
        while (t[i - p[i] - 1] == t[i + p[i] + 1]) {
            ++p[i];
        }

        // 가장 오른쪽까지 뻗은 팰린드롬 갱신
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // 원래 문자열의 팰린드롬 개수
        answer += (p[i] + 1) / 2;
    }

    cout << answer;

    return 0;
}