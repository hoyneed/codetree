#include <iostream>
#include <array>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
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
    if(rank[a] == rank[b]) {
        ++rank[a];
    }
    parent[b] = a;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(),parent.begin()+N+1,0);
    while(M--) {
        int c,a,b;
        cin >> c >> a >> b;
        if(!c) {
            Union(a,b);
        } else {
            cout << (Find(a) == Find(b)) <<  '\n';
        }
    }
    return 0;
}