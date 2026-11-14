#include <iostream>
#include <array>
#include <vector>   
#include <algorithm>
#include <utility>
using namespace std;
namespace {
constexpr int MAX_N = 101;
constexpr int DY[4]{-1,0,1,0};
constexpr int DX[4]{0,-1,0,1};
using Pos = pair<int,int>;
int N,M,K;
array<array<int,MAX_N>,MAX_N> grid;
array<array<bool,MAX_N>,MAX_N> visited;

bool IsOut(const int y, const int x) {
    return y <= 0 || x <= 0 || x > N || y > N;
}

int Run(vector<Pos>& q, const vector<char>& mask) {
    for(int i=1;i<=N;++i) {
        fill_n(visited[i].begin()+1,N,false);
    }
    for(const auto [y,x] : q) {
        visited[y][x] = true;
    }
    int cnt = K;
    for(int head=0;head<(int)q.size();++head) {
        const auto [y,x] = q[head];
        for(int d=0;d<4;++d) {
            const int ny = y + DY[d];
            const int nx = x + DX[d];
            if(IsOut(ny,nx) || visited[ny][nx] ||
            (grid[ny][nx] > 0 && !mask[grid[ny][nx]-1])) continue;
            visited[ny][nx] = true;
            ++cnt;
            q.emplace_back(ny,nx);
        }
    }
    q.resize(K);
    return cnt;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> M;
    int rocks = 0;
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=N;++j) {
            cin >> grid[i][j];
            if(grid[i][j]){
                grid[i][j] = ++rocks;
            }
        }
    }
    vector<Pos> starts;
    starts.reserve(N*N);
    for(int i=0;i<K;++i) {
        int r, c;
        cin >> r >> c;
        starts.emplace_back(r,c);
    }
    vector<char> mask(rocks,0);
    fill_n(mask.rbegin(),M,1);
    int answer = 0;
    do {
        answer = max(answer, Run(starts, mask));
    } while (next_permutation(mask.begin(),mask.end()));
    cout << answer;
    return 0;
}