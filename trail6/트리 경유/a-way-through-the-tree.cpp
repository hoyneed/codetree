#include <iostream>
#include <bitset>

using namespace std;

namespace {
constexpr int MAX_N = (1 << 20) + 1;

int N, Q;
bitset<MAX_N> tree;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;

    while (Q--) {
        int target;
        cin >> target;

        int node = target;
        int blocked = 0;

        while (node > 1) {
            if (tree[node]) {
                blocked = node;
            }
            node >>= 1;
        }

        cout << blocked << '\n';

        if (blocked == 0) {
            tree.set(target);
        }
    }

    return 0;
}