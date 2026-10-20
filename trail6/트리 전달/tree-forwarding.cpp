#include <iostream>
#include <array>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<vector<int>,MAX_N> child;
array<int,MAX_N> tree;

void Propagate(const int node, const int val) {
    for(const int ch : child[node]) {
        tree[ch] += val;
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=1;i<=N;++i) {
        int p;
        cin >> p;
        if(p == -1) continue;
        child[p].push_back(i);
    }
    while(M--) {
        int i, w;
        cin >> i >> w;
        tree[i] += w;
    }
    for(int i=1;i<=N;++i) {
        cout << tree[i] << ' ';
        Propagate(i, tree[i]);
    }
    return 0;
}