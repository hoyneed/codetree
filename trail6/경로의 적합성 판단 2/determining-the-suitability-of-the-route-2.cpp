#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M,K;
array<int,MAX_N> parent;
array<int,MAX_N> rank;

int Find(const int node) {
    if(parent[node] == node) return node;
    return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(rank[a] < rank[b]) swap(a,b);
    else if(rank[a] == rank[b]) ++rank[a];
    parent[b] = a;
}
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    iota(parent.begin(),parent.begin()+N+1,0);
    while(M--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    int root;
    cin >> root;
    root = Find(root);
    while(--K) {
        int node;
        cin >> node;
        if(Find(node) != root) {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
    return 0;
}