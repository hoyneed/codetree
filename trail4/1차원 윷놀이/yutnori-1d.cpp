#include <iostream>
#include <array>
#include <algorithm>
using namespace std;
namespace {
constexpr int MAX_N = 13;
constexpr int MAX_M = 101;
constexpr int MAX_K = 4;
int N,M,K;
array<int, MAX_N> turns;
array<int, MAX_K> piece;
int answer;

void Run(const int idx, const int point) {
    if(idx == N) {
        return;
    }
    for(int i=0;i<K;++i) {
        if(piece[i] >= M) continue;
        piece[i] += turns[idx];
        int np = point;
        if(piece[i] >= M) ++np;
        answer = max(answer, np);
        Run(idx+1, np);
        piece[i] -= turns[idx];
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    for(int i=0;i<N;++i) {
        cin >> turns[i];
    }
    fill_n(piece.begin(), K, 1);
    answer = 0;
    Run(0,0);
    cout << answer << '\n';

    return 0;
}