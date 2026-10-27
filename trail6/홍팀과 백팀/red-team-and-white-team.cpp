#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> sz;

public:
    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        parent[b] = a;
    }

    bool Same(int a, int b) {
        return Find(a) == Find(b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // 각 사람마다 자신과 반대 팀 상태 관리
    DSU dsu(2 * N);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;

        // 이미 같은 팀이라면 모순
        if (dsu.Same(a, b)) {
            cout << 0 << '\n';
            return 0;
        }

        // 서로 다른 팀이라는 정보 반영
        dsu.Union(a, b + N);
        dsu.Union(a + N, b);
    }

    cout << 1;

    return 0;
}