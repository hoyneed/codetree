#include <iostream>
#include <array>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 101;
constexpr int DY[4]{-1,0,1,0};
constexpr int DX[4]{0,-1,0,1};
int N, K;
struct Pos {
    int y,x;
};
array<array<bool, MAX_N>, MAX_N> grid;
array<array<bool, MAX_N>, MAX_N> visited;

bool IsOut(const int r, const int c) {
    return !(0 < r && r <= N && 0 < c && c <= N);
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
    int answer = 0;
    queue<Pos> q;
    while(K--) {
        int r,c;
        cin >> r >> c;
        visited[r][c] = true;
        q.emplace(r,c);
        ++answer;
    }
    while(!q.empty()) {
        const auto [r,c] = q.front();
        q.pop();
        for(int d = 0;d<4;++d) {
            const int nr = r + DY[d];
            const int nc = c + DX[d];
            if(IsOut(nr,nc) || grid[nr][nc] || visited[nr][nc]) continue;
            visited[nr][nc] = true;
            ++answer;
            q.emplace(nr,nc);
        }
    }
    cout << answer;
    return 0;
}