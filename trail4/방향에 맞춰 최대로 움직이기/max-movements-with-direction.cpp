#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;
namespace {
constexpr int DY[9]{0, -1, -1, 0, 1, 1, 1, 0, -1};
constexpr int DX[9]{0, 0, 1, 1, 1, 0, -1, -1, -1};
constexpr int MAX_N = 4;
int N;
int sy, sx;
int answer;
array<array<int, MAX_N>, MAX_N> grid;
array<array<int, MAX_N>, MAX_N> directions;

bool IsOut(const int r, const int c) {
    return r < 0 || c < 0 || r >= N || c >= N; 
}

void DFS(const int y, const int x, const int dist) {
    answer = max(answer, dist);
    const int d = directions[y][x];
    const int val = grid[y][x];
    for (int i=1;i<N;++i) {
        const int ny = y + DY[d] * i;
        const int nx = x + DX[d] * i;
        if(IsOut(ny,nx)) break;
        if(grid[ny][nx] <= val) continue;
        DFS(ny, nx, dist+1);
    }
}
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
            cin >> grid[i][j];
        }
    }
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
            cin >> directions[i][j];
        }
    }
    cin >> sy >> sx;
    --sy;
    --sx;
    answer = 0;
    DFS(sy,sx,0);
    cout << answer;
    return 0;
}