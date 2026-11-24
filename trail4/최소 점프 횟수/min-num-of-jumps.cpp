#include <iostream>
#include <array>
#include <algorithm>
#include <climits>
using namespace std;
namespace {
constexpr int MAX_N = 10;
int N;
array<int, MAX_N> arr;
int answer;
void DFS(const int idx, const int depth) {
    if(depth > answer) return;
    if(idx == N - 1) {
        answer = min(answer, depth);
        return;
    }
    const int limit = arr[idx];
    for(int i = 1;i<=limit;++i) {
        if(idx + i == N) break;
        DFS(idx+i, depth+1);
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=0;i<N;++i) {
        cin >> arr[i];
    }
    answer = INT_MAX;
    DFS(0,0);
    cout << (answer == INT_MAX ? -1 : answer) << '\n';
    return 0;
}