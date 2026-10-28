#include <iostream>
#include <array>
#include <numeric>
using namespace std;
namespace {
constexpr int MAX_N =100'001;
int N,M; 
array<int,MAX_N> parent;
int total;

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
    if(a>b) swap(a,b);
    while(a < b) {
        --total;
        parent[b] = a;
        b = Find(b-1);
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(), parent.begin()+N+1, 0);
    total = N;
    while(M--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
        cout << total << '\n';
    }
    return 0;
}