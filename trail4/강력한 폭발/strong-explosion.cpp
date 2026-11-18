#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
namespace {
constexpr int B[3][4][2] = {
{
    {-2,0},
    {-1,0},
    {1,0},
    {2,0}
},
{
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
},
{
    {-1,-1},
    {-1,1},
    {1,-1},
    {1,1}
}
};
constexpr int MAX_N = 20;
using Pos = pair<int,int>;
using Grid = array<array<bool, MAX_N>,MAX_N>;
int N;
Grid grid;
Grid visited;
vector<Pos> bombs;
int answer;

bool IsOut(const int y, const int x) {
    return y < 0 || x < 0 || y >= N || x >= N;
}

int Burst(const int y, const int x, const int type) {
    int ret = 0;
    if(!visited[y][x]) {
        ++ret;
        visited[y][x] = true;
    }
    for(int d=0;d<4;++d) {
        const int ny = y + B[type][d][0];
        const int nx = x + B[type][d][1];
        if(IsOut(ny,nx) || visited[ny][nx]) continue;
        ++ret;
        visited[ny][nx] = true;
    }
    return ret;
}

void Run(const int idx, const int cnt) {
    if(idx == (int)bombs.size()) {
        answer = max(answer, cnt);
        return;
    }
    Grid temp = visited;
    const auto [y,x] = bombs[idx];
    for(int type=0;type<3;++type) {
        Run(idx+1,cnt + Burst(y,x,type));
        visited = temp;
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    bombs.reserve(10);
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            cin >> grid[i][j];
            if(grid[i][j]) {
                bombs.emplace_back(i,j);
            }
        }
    }
    answer = 0;
    Run(0,0);
    cout << answer;
    return 0;
}