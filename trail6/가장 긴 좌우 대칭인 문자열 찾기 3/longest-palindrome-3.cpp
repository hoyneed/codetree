#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace {
int N;
char excluded;
string S;
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> excluded;

    cin >> S;

    vector<int> d1(N), d2(N);
    int answer = 0;

    // excluded 문자를 제외한 각 구간에 Manacher 적용
    for (int start = 0; start < N; ) {

        if (S[start] == excluded) {
            ++start;
            continue;
        }

        int end = start;

        while (end < N && S[end] != excluded) {
            ++end;
        }

        // 현재 구간: [start, end)

        // 1. 홀수 길이 팰린드롬
        int l = start;
        int r = start - 1;

        for (int i = start; i < end; ++i) {
            int k = (i > r)
                ? 1
                : min(d1[l + r - i], r - i + 1);

            while (i - k >= start &&
                   i + k < end &&
                   S[i - k] == S[i + k]) {
                ++k;
            }

            d1[i] = k;

            answer = max(answer, 2 * k - 1);

            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }

        // 2. 짝수 길이 팰린드롬
        l = start;
        r = start - 1;

        for (int i = start; i < end; ++i) {
            int k = (i > r)
                ? 0
                : min(d2[l + r - i + 1], r - i + 1);

            while (i - k - 1 >= start &&
                   i + k < end &&
                   S[i - k - 1] == S[i + k]) {
                ++k;
            }

            d2[i] = k;

            answer = max(answer, 2 * k);

            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }

        start = end;
    }

    cout << answer << '\n';

    return 0;
}