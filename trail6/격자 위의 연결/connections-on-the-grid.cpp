#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;
namespace {
constexpr int MAX_N = 301;
constexpr int MAX_X = MAX_N * MAX_N;
int N,M;

array<int, MAX_X> parent;
array<int, MAX_X> rank;
vector<tuple<int,int,int>> edges;

int Flatten(const int y, const int x) {
    return M * y + x;
}

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
    return true;
}

} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(),parent.begin()+N*M,0);
    edges.reserve(2*N*M);
    for(int r=0;r<N;++r) {
        for(int c=0;c<M-1;++c) {
            int w;
            cin >> w;
            const int u = Flatten(r,c);
            const int v = Flatten(r,c+1);
            edges.emplace_back(w,u,v);
        }
    }
    for(int r=0;r<N-1;++r) {
        for(int c=0;c<M;++c) {
            int w;
            cin >> w;
            const int u = Flatten(r,c);
            const int v = Flatten(r+1,c);
            edges.emplace_back(w,u,v);
        }
    }
    ranges::sort(edges);
    int answer = 0;
    for(const auto& [w,u,v] : edges) {
        if (Union(u,v)) {
            answer += w;
        }
    }
    cout << answer;
    return 0;
}