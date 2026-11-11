#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace {
int N, Q;
string S;
vector<int> Manacher(const string& s) {
    string t = "^";
    t.reserve(s.size() * 2 + 3);

    for (const char c : s) {
        t += '#';
        t += c;
    }

    t += "#$";

    const int N = (int)t.size();

    // p[i]: i를 중심으로 하는 최대 팰린드롬 반지름
    vector<int> p(N, 0);

    int center = 0;
    int right = 0;

    for (int i = 1; i < N - 1; ++i) {

        if (i < right) {
            const int mirror = 2 * center - i;

            p[i] = min(right - i, p[mirror]);
        }

        // 팰린드롬 확장
        while (t[i - p[i] - 1] ==
               t[i + p[i] + 1]) {
            ++p[i];
        }

        // 가장 오른쪽까지 확장된 구간 갱신
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    return p;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;

    cin >> S;

    // O(N) 전처리
    const vector<int> p = Manacher(S);

    while (Q--) {
        int a, b;
        cin >> a >> b;

        // 1-based 인덱스를 그대로 사용
        const int center = a + b;
        const int radius = b - a;

        cout << (p[center] >= radius ? "Yes" : "No")
             << '\n';
    }

    return 0;
}