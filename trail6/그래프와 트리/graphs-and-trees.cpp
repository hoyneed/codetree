#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 501;
int N, M;

array<vector<int>,MAX_N> graph;
array<int,MAX_N> parent;

bool IsTree(const int root) {
    bool is_tree = true;
    parent[root] = 0;
    queue<int> q;
    q.push(root);
    while(!q.empty()) {
        const int cur = q.front();
        q.pop();
        for(const int next : graph[cur]) {
            if(next == parent[cur]) continue;
            if(parent[next] != -1) {
                is_tree = false;
                continue;
            }
            parent[next] = cur;
            q.push(next);
        }
    }
    if(parent[root] != 0) is_tree = false;
    return is_tree;
}
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    fill_n(parent.begin(),N+1,-1);
    for(int i=0;i<M;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int answer = 0;
    for(int i=1;i<=N;++i) {
        if(parent[i] != -1) continue;
        if(IsTree(i)) ++answer;
    }
    cout << answer;
    return 0;
}