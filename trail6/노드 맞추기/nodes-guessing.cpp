#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>

using namespace std;
namespace {
constexpr int MAX_N = 1'001;
int N,M;
unordered_map<string_view, int> idxs;
array<int, MAX_N> indegree;
struct Node{
    string name;
    vector<int> children;
};
array<Node, MAX_N> tree;
array<vector<int>,MAX_N> graph;
string str0, str1;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    idxs.reserve(N);
    for(int i=0;i<N;++i) {
        cin >> tree[i].name;
        idxs[tree[i].name] = i;
    }
    cin >> M;
    while(M--) {
        cin >> str0 >> str1;
        const int u = idxs[str0];
        const int v = idxs[str1];
        ++indegree[u];
        graph[v].push_back(u);
    }
    vector<int> order;
    order.reserve(N);
    for(int i=0;i<N;++i) {
        if(indegree[i] == 0) {
            order.push_back(i);
        }
    }
    // 1. 트리 개수 출력
    const int tree_cnt = order.size();
    cout << tree_cnt << '\n';
    // 2. 루트 노드 사전 순 출력
    auto cmp = [](const int a,const int b) {
        return tree[a].name < tree[b].name;
    };
    ranges::sort(order, cmp);
    for(const int i : order) {
        cout << tree[i].name << ' ';
    }
    cout << '\n';
    for(int i=0;i<(int)order.size();++i) {
        const int u = order[i];
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                tree[u].children.push_back(v);
                order.push_back(v);
            }
        }
    }
    // 3. 사전 순으로 앞선 노드부터 정보 출력
    ranges::sort(order,cmp);
    for(const int idx : order) {
        auto& [name, children] = tree[idx];
        cout << name << ' ' << children.size();
        ranges::sort(children,cmp);
        for(const int c : children) {
            cout << ' ' << tree[c].name;
        }
        cout << '\n';
    }

    return 0;
}