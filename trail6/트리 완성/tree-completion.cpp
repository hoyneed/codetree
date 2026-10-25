#include <iostream>
#include <array>
#include <numeric>
using namespace std;
namespace {
    constexpr int MAX_N = 100'001;
    int N,M;
    array<int,MAX_N> parent;
    array<int,MAX_N> rank;
    int root = 1;

    int Find(const int node) {
        if(parent[node] == node) return node;
        return parent[node] = Find(parent[node]);
    }

    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if(a == b) return false;
        if(rank[a] < rank[b]) swap(a,b);
        else if (rank[a] == rank[b]) ++rank[a];
        parent[b] = a;
        if(rank[root] < rank[a]) {
            root = a;
        }
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    iota(parent.begin(),parent.begin()+N+1,0);
    int answer = 0;
    root = 1;
    while(M--) {
        int u,v;
        cin >> u >> v;
        if(!Union(u,v)) {
            ++answer;
        }
    }
    
    for(int i=1;i<=N;++i) {
        if(Union(root,i)) {
            ++answer;
        }
    }
    cout << answer;
    return 0;
}