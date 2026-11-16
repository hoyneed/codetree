#include <iostream>
#include <array>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 1001;
int N,M;
array<vector<int>, MAX_N> graph;
array<bool, MAX_N> visited;

int DFS() {
    int cnt = 0;
    visited[1] = true;
    vector<int> st{1};
    st.reserve(N);
    while(!st.empty()) {
        const int u = st.back();
        st.pop_back();
        for(const int v : graph[u]) {
            if(visited[v]) continue;
            visited[v] = true;
            ++cnt;
            st.push_back(v);
        }
    }
    return cnt;
}
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cout << DFS();
    return 0;
}