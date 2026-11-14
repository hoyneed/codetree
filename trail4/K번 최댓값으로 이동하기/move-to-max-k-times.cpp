#include <iostream>
#include <array>
#include <algorithm>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 101;
constexpr int DY[4]{-1,0,0,1};
constexpr int DX[4]{0,-1,1,0};
int N, K;
array<array<int, MAX_N>,MAX_N> grid;
array<array<bool, MAX_N>,MAX_N> visited;
struct Pos{
    int y,x;
    auto operator<=>(const Pos& other) const = default;
};

bool IsOut(const int y, const int x) {
    return y <= 0 || x <= 0 || y > N || x > N;
}
Pos Move(const Pos& st) {
    for(int i=1;i<=N;++i) {
        fill_n(visited[i].begin()+1,N,false);
    }
    const auto [sy, sx] = st;
    visited[sy][sx] = true;
    const int limit = grid[sy][sx];
    Pos cand{-1,-1};
    int max_value = -1;
    queue<Pos> q;
    q.push(st);
    while(!q.empty()) {
        const auto [y,x] = q.front();
        q.pop();
        for(int d=0;d<4;++d) {
            const int ny = y + DY[d];
            const int nx = x + DX[d];
            if(IsOut(ny,nx) || grid[ny][nx] >= limit || visited[ny][nx]) {
                continue;
            }
            visited[ny][nx] = true;
            if(max_value < grid[ny][nx]) {
                max_value = grid[ny][nx];
                cand = {ny,nx};
            } else if (max_value == grid[ny][nx] && cand > Pos{ny,nx}) {
                cand = {ny,nx};
            }
            q.emplace(ny,nx);
        }
    }
    if(max_value == -1) return st;
    return cand;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            cin >> grid[i][j];
        }
    }
    Pos pos;
    cin >> pos.y >> pos.x;
    while(K--) {
        pos = Move(pos);
    }
    cout << pos.y << ' ' << pos.x;
    return 0;
}