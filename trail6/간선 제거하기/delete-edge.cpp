#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
using LL = long long;
int N,M;
array<int,MAX_N> parent;

struct Edge{
    int w,u,v;
    auto operator<=>(const Edge& other) const = default;
};
vector<Edge> edges;

void Init() {
    fill_n(parent.begin()+1,N,-1);
    edges.reserve(M);
}

int Find(int x) {
    if(parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return false;
    if(parent[a] > parent[b]) swap(a,b);
    parent[a] += parent[b];
    parent[b] = a;
    return true;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    Init();
    LL total = 0;
    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        edges.emplace_back(w,u,v);
        total += w;
    }
    ranges::sort(edges);
    LL needed = 0;
    for(const auto& [w,u,v] : edges) {
        if(Union(u,v)) {
            needed += w;
        }
    }
    cout << total - needed;
    return 0;
}