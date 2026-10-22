#include <iostream>
#include <array>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> parent;
array<int, MAX_N> tree;
vector<int> order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        cin >> tree[i];
    }
    if(N == 1) {
        cout << 0;
        return 0;
    }
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    order.reserve(N);
    order.push_back(1);
    for(int i=0;i<(int)order.size();++i) {
        const int cur = order[i];
        for(const auto next : graph[cur]) {
            if(parent[cur] == next) continue;
            parent[next] = cur;
            order.push_back(next);
        }
    }
    int answer = 0;
    for(int i=N-1;i>0;--i) {
        const int cur = order[i];
        if(tree[cur] != 1) {
            const int diff = tree[cur] - 1;
            tree[cur] = 1;
            tree[parent[cur]] += diff;
            answer += (diff > 0 ? diff : -diff);
        }
    }
    cout << answer;
    return 0;
}