#include <iostream>
#include <array>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N;
typedef struct{
    int p,v;
} Node;
array<Node, MAX_N> tree;
array<int, MAX_N> indegree;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=2;i<=N;++i) {
        bool t;
        int a,p;
        cin >> t >> a >> p;
        if(!t) a = -a;
        ++indegree[p];
        tree[i] = {p,a};
    }
    queue<int> q;
    for(int i=2;i<=N;++i) {
        if(!indegree[i]) q.push(i);
    }
    while(!q.empty()) {
        const auto& [p, val] = tree[q.front()];
        q.pop();
        if(--indegree[p] == 0) q.push(p);
        if(val > 0) tree[p].v += val;
    }
    cout << tree[1].v;
    return 0;
}