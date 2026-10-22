#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
#include <tuple>
#include <queue>

using namespace std;
namespace {
constexpr char DCH[4]{'>','<','v','^'};
constexpr int DY[4]{0,0,1,-1};
constexpr int DX[4]{1,-1,0,0};
// 좌회전, 우회전
constexpr array<array<int,2>,4> ND{{
    {3,2},
    {2,3},
    {0,1},
    {1,0}
}};
int H,W;
array<string, 25> grid;
array<array<bool,25>, 25> visited;
using State = tuple<int,int,int,int>; // {y,x,dir,visit_cnt}
int total;
int min_len;
struct Ret{
    int y,x, dir;
    string command;
};
Ret answer;

bool IsOut(const int y, const int x) {
    if(y<0||x<0||y>=H||x>=W) return true;
    return false;
}
bool IsValid(const int y,const int x, const int dir) {
    if(IsOut(y,x) || grid[y][x] == '.') return false;
    for(int i=1;i<=2;++i) {
        const int ny = y + DY[dir]*i;
        const int nx = x + DX[dir]*i;
        if(IsOut(ny,nx) || grid[ny][nx] == '.' || visited[ny][nx]) return false;
    }
    return true;
}

void BFS(const int start_y, const int start_x) {
    for(int i=0;i<H;++i) {
        fill_n(visited[i].begin(),W,false);
    }
    int start_d = -1;
    for(int d=0;d<4;++d) {
        if(IsValid(start_y,start_x,d)) {
            start_d = d;
            break;
        }
    }
    if(start_d == -1) return;
    visited[start_y][start_x] = true;
    string cmd{};
    queue<State> qu;
    qu.emplace(start_y,start_x,start_d,1);
    while(!qu.empty()) {
        const auto [y,x,d,cnt] = qu.front();
        qu.pop();
        if((int)cmd.length() > min_len) return;
        if(cnt == total) {
            if(min_len > (int)cmd.length()) {
                min_len = cmd.length();
                answer = {start_y,start_x,start_d,cmd};
            }
            return;
        }
        if(IsValid(y,x,d)) {
            cmd += 'A';
            for(int i=1;i<=2;++i) {
                visited[y+ DY[d]*i][x+DX[d]*i] = true;
            }
            qu.emplace(y+ DY[d]*2,x+DX[d]*2,d,cnt+2);
            continue;
        }
        int next_dir = -1;
        for(int i=0;i<2;++i) {
            const int nd = ND[d][i];
            if(IsValid(y,x,nd)) {
                if(i == 0) cmd += 'L';
                else cmd += 'R';
                next_dir =  nd;
                break;               
            }
        }
        if(next_dir == -1) return;
        qu.emplace(y,x,next_dir,cnt);
    }
}
} // namespace


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W;
    total = 0;
    for(int i=0;i<H;++i) {
        cin >> grid[i];
        for(const auto ch : grid[i]) {
            if(ch == '#') ++total;
        }
    }
    min_len = INT_MAX;
    answer = {};
    for(int i=H-1;i>=0;--i) {
        for(int j=W-1;j>=0;--j) {
            if(grid[i][j] == '.') continue;
            BFS(i,j);
        }
    }
    cout << answer.y + 1 <<' ' << answer.x + 1 << '\n';
    cout << DCH[answer.dir] <<'\n';
    cout << answer.command;
    return 0;
}
