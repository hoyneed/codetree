#include <iostream>
#include <vector>

using namespace std;
namespace{
int N, K;
vector<int> arr;
vector<vector<int>> levels;
} // namespace


void BuildTree(int left, int right, int depth) {
    if (left > right)
        return;

    // 현재 구간의 가운데 원소가 루트
    int mid = (left + right) / 2;

    // 현재 깊이에 루트 값 저장
    levels[depth].push_back(arr[mid]);

    // 왼쪽 서브트리
    BuildTree(left, mid - 1, depth + 1);

    // 오른쪽 서브트리
    BuildTree(mid + 1, right, depth + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K;

    N = (1 << K) - 1;

    arr.resize(N);
    levels.resize(K);

    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    BuildTree(0, N - 1, 0);

    for (int depth = 0; depth < K; ++depth) {
        for (int node : levels[depth]) {
            cout << node << ' ';
        }
        cout << '\n';
    }

    return 0;
}