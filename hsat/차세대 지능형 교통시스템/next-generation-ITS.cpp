#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 100;
// 상, 하, 좌, 우
constexpr int DY[4]{-1,1,0,0};
constexpr int DX[4]{0,0,-1,1};
// 각 신호 별 허용되는 다음 방향
constexpr int MASK[13] {
    0,
    0b1011, // 신호1
    0b1101, // 신호2
    0b0111, // 신호3
    0b1110, // 신호4
    0b1001, // 신호5
    0b0101, // 신호6
    0b0110, // 신호7
    0b1010, // 신호8
    0b1010, // 신호9
    0b1001, // 신호10
    0b0101, // 신호11
    0b0110, // 신호12
};
// 각 신호 별 자동차가 향해야 하는 방향
constexpr int DIR[13] {
    -1,
    3,0,2,1,
    3,0,2,1,
    3,0,2,1
};
// 좌회전/직진/우회전 방향
constexpr array<array<int,3>,4> ND{{
    {2,0,3},
    {3,1,2},
    {1,2,0},
    {0,3,1}
}};
struct Car {
    int y,x,dir;
    Car() = default;
    Car(int y,int x,int dir): y(y), x(x), dir(dir) {}
};
int N,T;
int N2;
array<array<array<int,4>,MAX_N>,MAX_N> grid;
array<array<bool,MAX_N>,MAX_N> visited;

bool IsOut(const int y,const int x) {
    if(y<0||x<0||y>=N||x>=N) return true;
    return false;
}

int BFS() {
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            visited[i][j] = false;
        }
    }
    visited[0][0] = true;
    queue<Car> qu;
    qu.emplace(0,0,0);
    int ret = 1;
    for(int t=0;t<T && !qu.empty();++t) {
        int sz = qu.size();
        while(sz--) {
            const auto [y,x,dir] = qu.front();
            qu.pop();
            const int signal = grid[y][x][t % 4];
            if(dir != DIR[signal]) continue;
            for(const int nd : ND[dir]) {
                if(!(MASK[signal] & (1 << nd))) continue;
                const int ny = y + DY[nd];
                const int nx = x + DX[nd];
                if(IsOut(ny,nx)) continue;
                if(!visited[ny][nx]){
                    ++ret;
                    visited[ny][nx] =true;
                }
                qu.emplace(ny,nx,nd);
            }
        }
    }
    return ret;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> T;
    N2 = N*N;
    for(int i=0;i<N2;++i) {
        const int y = i / N;
        const int x = i % N;
        for(int j=0;j<4;++j) {
            cin >> grid[y][x][j];
        }
    }
    cout << BFS();
    return 0;
}