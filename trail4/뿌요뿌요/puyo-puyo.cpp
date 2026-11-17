#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
using namespace std;
namespace {
constexpr int MAX_N = 100;
constexpr int DR[4]{-1,0,1,0};
constexpr int DC[4]{0,-1,0,1};
int N;
struct Pos {
    int y,x;
}; 
array<array<int, MAX_N>, MAX_N> grid;
array<array<int, MAX_N>, MAX_N> visited;
vector<Pos> st;

bool IsOut(const int r, const int c) {
    return r < 0 || c < 0 || r >= N || c >= N;
}

int DFS(const int sr, const int sc) {
    const int val = grid[sr][sc];
    int cnt = 1;
    visited[sr][sc] = true;
    st.emplace_back(sr,sc);
    while(!st.empty()) {
        const auto [r,c] = st.back();
        st.pop_back();
        for(int d = 0;d<4;++d) {
            const int nr = r + DR[d];
            const int nc = c + DC[d];
            if(IsOut(nr,nc) || grid[nr][nc] != val || visited[nr][nc])
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
    for(int r=0;r<N;++r) {
        for(int c=0;c<N;++c) {
            cin >> grid[r][c];
        }
    }
    st.reserve(N*N);
    int max_size = 1;
    int busted = 0;
    for(int r=0;r<N;++r) {
        for(int c=0;c<N;++c) {
            if(visited[r][c]) continue;
            const int sz = DFS(r,c);
            max_size = max(max_size, sz);
            if(sz >= 4) {
                ++busted;
            }
        }
    }

    cout << busted << ' ' << max_size << '\n';
    return 0;
}