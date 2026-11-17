#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
namespace {
constexpr int MAX_N = 25;
constexpr int DR[4]{-1,0,1,0};
constexpr int DC[4]{0,-1,0,1};
int N;
using Pos = pair<int,int>;
array<array<bool, MAX_N>, MAX_N> grid;
array<array<bool, MAX_N>, MAX_N> visited;
vector<int> village;
vector<Pos> st;

bool IsOut(const int r,const int c) {
    return r < 0 || c < 0 || r >= N || c >= N;
}

int DFS(const int start_r, const int start_c) {
    int cnt = 1;
    visited[start_r][start_c] = true;
    st.emplace_back(start_r,start_c);
    while(!st.empty()) {
        const auto [r,c] = st.back();
        st.pop_back();
        for(int d=0;d<4;++d) {
            const int nr = r + DR[d];
            const int nc = c + DC[d];
            if(IsOut(nr,nc) || !grid[nr][nc] || visited[nr][nc])
                continue;
            visited[nr][nc] = true;
            ++cnt;
            st.emplace_back(nr,nc);
        }
    }
    return cnt;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            cin >> grid[i][j];
        }
    }
    village.reserve(N * N);
    st.reserve(N * N);
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            if(!grid[i][j] || visited[i][j]) continue;
            village.push_back(DFS(i,j));
        }
    }
    ranges::sort(village);
    cout << village.size() << '\n';
    for(const int v : village) {
        cout << v << '\n';
    }

    return 0;
}