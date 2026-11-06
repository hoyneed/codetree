#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>

using namespace std;
namespace {
constexpr int MAX_N = 101;
int N;
array<bool, 26> exists;
array<int, 26> indegree;
array<vector<int>, MAX_N> graph;
vector<int> order;
string pv, cur;
int total;

void MarkExist(string_view str) {
    for(const char c : str) {
        if(!exists[c-'a']) {
            exists[c-'a'] = true;
            ++total;
        }
    }
}

int FirstDiffIdx(string_view sv0, string_view sv1) {
    int idx = 0;
    while(idx < (int)min(sv0.size(),sv1.size()) && sv0[idx] == sv1[idx]) {
        ++idx;
    }
    return idx;
}

} // namespace
int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    total = 0;
    cin >> pv;
    MarkExist(pv);
    for(int i=1;i<N;++i) {
        cin >> cur;
        MarkExist(cur);
        const int idx = FirstDiffIdx(pv,cur);
        if(idx != (int)pv.size()) {
            const int u = pv[idx] - 'a';
            const int v = cur[idx] - 'a';
            graph[u].push_back(v);
            ++indegree[v];
        }
        cur.swap(pv);
    }
    order.reserve(30);
    for(int i=0;i<26;++i) {
        if(exists[i] && indegree[i] == 0) {
            order.push_back(i);
        }
    }
    bool flag = (order.size() != 1);
    for(int i=0;i<(int)order.size();++i) {
        const int u = order[i];
        const int sz = order.size();
        for(const int v : graph[u]) {
            if(--indegree[v] == 0) {
                order.push_back(v);
            }
        }
        if((int)order.size() > sz + 1) {
            flag = true;
        }
    }
    if((int)order.size() != total) {
        cout << -1;
    } else if (flag) {
        cout << "inf";
    } else {
        for(const int i : order)
            cout << char(i + 'a');
    }
    return 0;
}