#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

namespace {
using LL = long long;
int H,K,R;
int N;

LL answer;
vector<queue<int>> tree;

void Push(int node,const int num) {
    node += N/2;
    tree[node].push(num);
}

void Process(const int day) {
    for(int i = 1;i < N/2;++i) {
        auto& q = tree[i];
        int child = i << 1;
        if(day % 2) ++child;
        auto& child_q = tree[child];
        if(child_q.empty()) continue;
        q.push(child_q.front());
        child_q.pop();
        if(i == 1 && !q.empty()) {
            answer += q.front();
            q.pop();
        }
    }
}


} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> K >> R;
    N = (1 << (H+1));
    tree.assign(N,{});
    for(int i=0;i<N/2;++i) {
        for(int j=0;j<K;++j) {
            int w;
            cin >> w;
            Push(i,w);
        }
    }
    answer = 0;
    for(int day=1;day<R;++day) {
        Process(day);
    }
    cout << answer;
    return 0;
}