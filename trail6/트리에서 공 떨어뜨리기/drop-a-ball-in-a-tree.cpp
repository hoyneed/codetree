#include <iostream>
#include <array>

using namespace std;

namespace {
constexpr int MAX_N = 200'001;

struct Node {
    int left, right;
};

int N;
long long K;
array<Node, MAX_N> tree;

int FindLastBall() {
    int node = 1;

    while (true) {
        const Node& cur = tree[node];

        if (cur.left == -1 && cur.right == -1)
            return node;

        // 자식이 하나뿐인 경우
        if (cur.left == -1) {
            node = cur.right;
        }
        else if (cur.right == -1) {
            node = cur.left;
        }
        // 두 자식이 존재하는 경우
        else if (K & 1LL) {
            node = cur.left;
            K = K / 2 + 1;
        }
        else {
            node = cur.right;
            K /= 2;
        }
    }
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 1; i <= N; ++i) {
        cin >> tree[i].left >> tree[i].right;
    }

    cin >> K;

    cout << FindLastBall() << '\n';

    return 0;
}