#include <iostream>
#include <array>
#include <vector>
#include <utility>
using namespace std;
namespace {
constexpr int MAX_N = 101;
constexpr int DY[2]{1,0};
constexpr int DX[2]{0,1};
int N,M;
using Pos = pair<int,int>;
array<array<bool,MAX_N>,MAX_N> grid;
array<array<bool,MAX_N>,MAX_N> visited;

bool IsOut(const int y, const int x) {
    return y < 0 || x < 0 || y >= N || x >= M;
}

bool DFS() {
    vector<Pos> st;
    st.reserve(N*M);
    st.emplace_back(0,0);
    visited[0][0] = true;
    while(!st.empty()) {
        const auto [y,x] = st.back();
        st.pop_back();
        for(int d=0;d<2;++d) {
            const int ny = y + DY[d];
            const int nx = x + DX[d];
            if(IsOut(ny,nx) || !grid[ny][nx] || visited[ny][nx]) continue;
            visited[ny][nx] = true;
            if(ny == N-1 && nx == M-1) return true;
            st.emplace_back(ny,nx);
        }
    }
    return false;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            cin >> grid[i][j];
        }
    }
    cout << DFS();

    return 0;
}