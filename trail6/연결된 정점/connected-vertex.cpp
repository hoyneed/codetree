#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<int,MAX_N> parent;
array<int,MAX_N> sz;

int Find(const int node) {
    if(parent[node] == node) return node;
    return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    parent[b] = a;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(),parent.begin()+N+1,0);
    fill_n(sz.begin()+1,N,1);
    while(M--) {
        char cmd;
        cin >> cmd;
        if(cmd == 'x') {
            int a,b;
            cin >> a >> b;
            Union(a,b);
        } else {
            int a;
            cin >> a;
            cout << sz[Find(a)] << '\n';
        }
    }
    return 0;
}