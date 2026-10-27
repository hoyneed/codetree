#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M,K;
array<int,MAX_N> val;
array<int,MAX_N> parent;

int Find(const int node) {
    if(parent[node] == node) return node;
    return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(val[a] > val[b]) swap(a,b);
    parent[b] = a;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    iota(parent.begin(), parent.begin() + N + 1, 0);
    for(int i=1;i<=N;++i) {
        cin >> val[i];
    }
    while(M--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    int cost = 0;
    int cnt = 0;
    int min_val = 10001;
    for(int i=1;i<=N;++i) {
        if(parent[i] != i) continue;
        min_val = min(min_val,val[i]);
        cost += val[i];
        ++cnt;
    }
    const int answer = cost + min_val * (cnt-2);
    if(answer > K)
        cout << "NO";
    else
        cout << answer;
    return 0;
}