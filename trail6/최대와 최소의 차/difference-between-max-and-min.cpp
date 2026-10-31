#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <ranges>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
vector<tuple<bool,int,int>> edges;
array<int,MAX_N> parent;
array<int,MAX_N> ranks;
int groups;

int Find(int x) {
    while(x != parent[x]) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return false;
    if(ranks[a] < ranks[b]) swap(a,b);
    else if (ranks[a] == ranks[b]) ++ranks[a];
    parent[b] = a;
    --groups;
    return true;
}
} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(), parent.begin() + N + 1,0);
    edges.reserve(M);
    for(int i=0;i<M;++i) {
        int u,v;
        bool w;
        cin >> u >> v >> w;
        edges.emplace_back(w,u,v);
    }
    ranges::sort(edges);
    int max_cost = 0;
    groups = N;
    for(const auto& [w,u,v] : edges) {
        if(groups == 1) break;
        if(Union(u,v) && !w) {
            ++max_cost;
        }
    }
    iota(parent.begin(),parent.begin()+N+1,0);
    fill_n(ranks.begin()+1,N,0);
    int min_cost = 0;
    groups = N;
    for(const auto& [w,u,v] : edges | views::reverse) {
        if(groups == 1) break;
        if(Union(u,v) && !w) {
            ++min_cost;
        }
    }
    cout << 1LL * max_cost * max_cost - 1LL * min_cost * min_cost;
    return 0;
}