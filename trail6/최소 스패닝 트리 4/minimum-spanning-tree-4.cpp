#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N,M;
array<char,MAX_N> types;
array<int,MAX_N> parent;
array<int,MAX_N> rank;
vector<tuple<int,int,int>> edges;
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
    if(rank[a] < rank[b]) swap(a,b);
    else if (rank[a] == rank[b]) ++rank[a];
    parent[b] = a;
    --groups;
    return true;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=1;i<=N;++i) {
        cin >> types[i];
    }
    edges.reserve(M);
    while(M--) {
        int u,v,w;
        cin >> u >> v >> w;
        if(types[u] == types[v]) continue;
        edges.emplace_back(w,u,v);
    }
    ranges::sort(edges);
    groups = N;
    iota(parent.begin(),parent.begin()+N+1,0);
    int answer = 0;
    for(const auto& [w,u,v] : edges) {
        if(Union(u,v)) {
            answer += w;
        }
    }
    cout << (groups == 1 ? answer : -1);
    return 0;
}