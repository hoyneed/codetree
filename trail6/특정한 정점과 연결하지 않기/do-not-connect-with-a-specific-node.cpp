#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M,K;
int A,B;

array<int,MAX_N> parent;
array<int,MAX_N> sz;
int group_cnt;

int Find(const int x) {
    if(parent[x] == x) return x;
    return parent[x] = Find(parent[x]);
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return false;
    if(sz[a] < sz[b]) swap(a,b);
    --group_cnt;
    sz[a] += sz[b];
    parent[b] = a;
    return true;
}
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(), parent.begin() + N + 1, 0);
    fill_n(sz.begin(), N+1, 1);
    group_cnt = N;
    while(M--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    cin >> A >> B >> K;
    const int root = Find(A);
    const int exclude = Find(B);
    vector<int> groups;
    groups.reserve(group_cnt);
    for(int i=1;i<=N;++i) {
        if(parent[i] != i) continue;
        if(i == root || i == exclude) continue;
        groups.push_back(sz[i]);
    }
    int answer = sz[root];
    if(K >= (int)groups.size()) {
        for(const int e : groups) {
            answer += e;
        }
        cout << answer;
        return 0;
    }
    ranges::nth_element(groups, groups.begin() + K, ranges::greater{});
    for(int i=0;i<K ;++i) {
        answer += groups[i];
    }
    cout << answer;
    return 0;
}