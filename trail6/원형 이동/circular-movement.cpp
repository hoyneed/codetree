#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;
namespace{
using LL = long long;
constexpr int MAX_N = 200'001;
const int INF = INT_MAX / 2;
int N, M;
LL K;
array<int, MAX_N> cost;
array<bool, MAX_N> blocked;
struct DSU {
    int groups;
    vector<int> parent;

    explicit DSU(int n)
        : groups(n), parent(n + 1) {
            iota(parent.begin(),parent.end(),0);
        }

    int Find(int x) {
        while(x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return;
        if (cost[a] > cost[b]) swap(a, b);
        parent[b] = a;
        --groups;
    }
};
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> cost[i];
    }

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        if (a % N + 1 == b) {
            blocked[a] = true;
        }
        else {
            blocked[b] = true;
        }
    }

    DSU dsu(N);

    // 공사하지 않는 구간만 연결
    for (int i = 1; i <= N; ++i) {
        if (blocked[i]) continue;

        const int next = (i == N ? 1 : i + 1);
        dsu.Union(i, next);
    }
    // group이 1개면 통행 비용이 0이므로 항상 가능
    if(dsu.groups == 1) {
        cout << 1;
        return 0;
    }
    // 집합별 최소 통행권 가격
    vector<int> minCost;
    minCost.reserve(dsu.groups);

    for (int i = 1; i <= N; ++i) {
        if(dsu.parent[i] != i) continue;
        minCost.push_back(cost[i]);
    }

    // 집합마다 가장 저렴한 통행권 하나 구매
    LL total = 0;

    for(const int c : minCost) {
        total += c;
    }

    cout << (total <= K ? 1 : 0);

    return 0;
}