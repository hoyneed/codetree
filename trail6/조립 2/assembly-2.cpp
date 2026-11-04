#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N,M;
array<int,MAX_N> indegree;
array<vector<int>,MAX_N> graph;
vector<int> available;
array<bool,MAX_N> exists;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int a, k;
        cin >> a >> k;
        indegree[a] += k;
        while(k--) {
            int b;
            cin >> b;
            graph[b].push_back(a);
        }
    }
    int cnt;
    cin >> cnt;
    available.reserve(N);
    while(cnt--) {
        int u;
        cin >> u;
        if(!exists[u]) {
            exists[u] = true;
            available.push_back(u);
        }
    }
    for(int i=0;i<(int)available.size();++i) {
        const int u = available[i];
        for(const int v : graph[u]) {
            if(!exists[v] && --indegree[v] == 0) {
                exists[v] = true;
                available.push_back(v);
            }
        }
    }
    ranges::sort(available);
    cout << available.size() << '\n';
    for(const int i : available) {
        cout << i << ' ';
    }

    
    return 0;
}