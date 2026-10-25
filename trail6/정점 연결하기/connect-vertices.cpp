#include <iostream>
#include <array>
#include <numeric>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N;
array<int,MAX_N> parent;

int Find(const int node) {
    if(node == parent[node]) return node;
    return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a==b) return;
    if(a > b) swap(a,b);
    parent[b] = a;
}
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    iota(parent.begin(),parent.begin()+N+1,0);
    for(int i=0;i<N-1;++i) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    int cnt = 0;
    for(int i=1;i<=N;++i) {
        if(parent[i] != i) continue;
        cout << i << ' ';
        if(++cnt == 2) break;
    }
    return 0;
}