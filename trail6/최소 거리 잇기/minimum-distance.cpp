#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>

using namespace std;
namespace {
using LL = long long;
constexpr int MAX_N = 201;
int N,M;
using Pos = pair<int,int>;
array<Pos,MAX_N> positions;
array<int,MAX_N> parent;
array<int,MAX_N> rank;
vector<tuple<LL,int,int>> edges; // {길이^2, u, v}

int groups;

int Find(int x) {
    while(x != parent[x]) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool Union(int a,int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return false;
    if(rank[a] < rank[b]) swap(a,b);
    else if (rank[a] == rank[b]) ++rank[a];
    parent[b] = a;
    --groups;
    return true;
}

LL Dist2(const int a,const int b) {
    const auto& [ax,ay] = positions[a];
    const auto& [bx,by] = positions[b];
    return 1LL * (ax-bx) * (ax-bx) + 1LL * (ay-by) * (ay-by);
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(),parent.begin()+N+1,0);
    for(int i=1;i<=N;++i) {
        cin >> positions[i].first >> positions[i].second;
    }
    groups = N;
    edges.reserve(N*N);
    while(M--) {
        int u,v;
        cin >> u >> v;
        Union(u,v);
    }
    for(int i=1;i<N;++i) {
        for(int j=i+1;j<=N;++j) {
            if(Find(i) == Find(j)) continue;
            edges.emplace_back(Dist2(i,j),i,j);
        }
    }
    ranges::sort(edges);
    double answer = 0.0;
    for(const auto& [w,u,v] : edges) {
        if(Union(u,v)) {
            answer += sqrt(w);
        }
        if(groups == 1) break;
    }
    cout << fixed;
    cout.precision(2);
    cout << answer;
    return 0;
}