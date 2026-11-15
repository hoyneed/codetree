#include <iostream>
#include <array>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;
namespace {
constexpr int MAX_N = 8;
constexpr int DY[4]{-1,0,1,0};
constexpr int DX[4]{0,-1,0,1};
int N,K,U,D;
using Pos = pair<int,int>;
array<array<int,MAX_N>,MAX_N> grid;
array<array<bool,MAX_N>,MAX_N> visited;
vector<int> group_sz;

bool IsOut(const int y, const int x) {
    return y < 0 || x < 0 || y >= N || x >= N;
}

void FillGroup(const int start_y, const int start_x) {
    queue<Pos> q;
    q.emplace(start_y,start_x);
    visited[start_y][start_x] = true;
    group_sz.push_back(1);
    while(!q.empty()) {
        const auto [y,x] = q.front();
        q.pop();
        const int h = grid[y][x];
        for(int d = 0;d < 4; ++d) {
            const int ny = y + DY[d];
            const int nx = x + DX[d];
            if(IsOut(ny,nx) || visited[ny][nx]) continue;
            const int diff = abs(h - grid[ny][nx]);
            if(diff < U || diff > D) continue;
            visited[ny][nx] = true;
            ++group_sz.back();
            q.emplace(ny,nx);
        }
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> U >> D;
    for(int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
            cin >> grid[i][j];
        }
    }
    group_sz.reserve(N * N);
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            if(visited[i][j]) continue;
            FillGroup(i,j);
        }
    }
    if(K >= (int)group_sz.size()) {
        cout << N*N;
        return 0;
    }
    ranges::nth_element(group_sz, group_sz.begin() + K, ranges::greater{});
    int answer = 0;
    for(int i=0;i<K;++i) {
        answer += group_sz[i];
    }
    cout << answer;
    return 0;
}