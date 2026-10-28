#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N;
array<int, MAX_N> parent;
array<int, MAX_N> sz;

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
    if(a == b) {
        cout << sz[a] << '\n';
        return;
    }
    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    parent[b] = a;
    cout << sz[a] << '\n';
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    iota(parent.begin(), parent.end(),0);
    fill(sz.begin(),sz.end(),1);
    while(N--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    return 0;
}