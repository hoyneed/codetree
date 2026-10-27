#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N, M;
array<int, MAX_N> parent;

int Find(const int node) {
    if(parent[node] == node) return node;
    return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(a > b) swap(a,b);
    parent[b] = a;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(), parent.begin() + N + 1,0);
    int num;
    for (num=0;num<M;++num) {
        int k;
        cin >> k;
        const int root = Find(k);
        if(root == 0) break;
        Union(root-1,root);
    }
    cout << num;
    return 0;
}