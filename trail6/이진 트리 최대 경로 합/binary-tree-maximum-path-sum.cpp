#include <iostream>
#include <array>
#include <vector>
#include <climits>
#include <algorithm>
#include <tuple>
#include <ranges>
using namespace std;
namespace {
constexpr int MAX_N = 30'001;
int N;
array<vector<int>, MAX_N> graph;
array<int, MAX_N> tree;
array<int, MAX_N> parent;
vector<int> order;
array<array<int,2>, MAX_N> down;
array<int, MAX_N> up;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i=1;i<=N;++i) {
        cin >> tree[i];
    }
    order = {1};
    order.reserve(N);
    for(int i=0;i < (int)order.size(); ++i) {
        const int cur = order[i];
        for(const int next : graph[cur]) {
            if(parent[cur] == next) continue;
            parent[next] = cur;
            order.push_back(next);
        }
    }
    for(const int cur : order | views::reverse) {
        down[cur] = {};
        for(const int next : graph[cur]) {
            if(parent[cur] == next) continue;
            const int newSum = tree[next] + down[next][0];
            if(newSum > down[cur][0]) {
                down[cur][1] = down[cur][0];
                down[cur][0] = newSum;
            } else if (newSum > down[cur][1]) {
                down[cur][1] = newSum;
            }
        }
    }
    int answer = INT_MIN;
    for(const int cur : order) {
        const int p = parent[cur];
        if(up[p] + tree[p] > 0) {
            up[cur] = up[p] + tree[p];
        }
        if(up[cur] > down[cur][1]) {
            answer = max(answer,up[cur] +tree[cur]+ down[cur][0]);
        } else {
            answer = max(answer, tree[cur] + down[cur][0] + down[cur][1]);
        }
    }
    cout << answer;
    return 0;
}