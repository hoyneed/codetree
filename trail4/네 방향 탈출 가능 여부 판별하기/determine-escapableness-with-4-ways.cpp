#include <iostream>
#include <array>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 101;
constexpr int DY[4]{-1,0,1,0};
constexpr int DX[4]{0,-1,0,1};
int N,M;
struct Pos {
    int y,x;
};
array<array<bool, MAX_N>, MAX_N> grid;
array<array<bool, MAX_N>, MAX_N> visited;

bool IsOut(const int y, const int x) {
    if(y < 0 || x < 0 || y >= N || x >= M) return true;
    return false;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            cin >> grid[i][j];
        }
    }
    if(!grid[0][0]) {
        cout << 0;
        return 0;
    }
    queue<Pos> q;
    q.emplace(0,0);
    visited[0][0] = true;
    while(!q.empty()) {
        const auto [y,x] = q.front();
        q.pop();
        for(int d=0;d<4;++d) {
            const int ny = y + DY[d];
            const int nx = x + DX[d];
            if(IsOut(ny,nx) || !grid[ny][nx] || visited[ny][nx]) continue;
            visited[ny][nx] = true;
            if(ny == N-1 && nx == M-1) {
                cout << 1;
                return 0;
            }
            q.emplace(ny,nx);
        }
    }
    cout << 0;
    return 0;
}