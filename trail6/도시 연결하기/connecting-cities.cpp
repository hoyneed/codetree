#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 50;
constexpr int INF = 1e9;
constexpr int DR[4]{-1,0,1,0};
constexpr int DC[4]{0,-1,0,1};
using Pos = pair<int,int>;
using State = tuple<int,int,int>; // {dist, r, c}
using MinHeap = priority_queue<State,vector<State>,greater<>>;
int N,M;
array<array<int,MAX_N>,MAX_N> grid;
array<array<int,MAX_N>,MAX_N> dist;

bool IsOut(const int r, const int c) {
    if(r<0||c<0||r>=N||c>=M) return true;
    return false;
}

void FillHeap(const int sr, const int sc, MinHeap& pq) {
    dist[sr][sc] = 0;
    vector<Pos> members;
    members.emplace_back(sr,sc);
    for(int i = 0;i<(int)members.size();++i) {
        const auto [r,c] = members[i];
        for(int d=0;d<4;++d) {
            const int nr = r + DR[d];
            const int nc = c + DC[d];
            if(IsOut(nr,nc) || grid[nr][nc] == 0 || dist[nr][nc] == 0) continue;
            dist[nr][nc] = 0;
            members.emplace_back(nr,nc);
        }
    }
    for(int i=0;i<(int)members.size();++i) {
        const auto& [r,c] = members[i];
        for(int d=0;d<4;++d) {
            for(int weight=1;weight<max(M,N);++weight){
                const int nr = r + DR[d] * weight;
                const int nc = c + DC[d] * weight;
                if(IsOut(nr,nc) || dist[nr][nc] == 0) break;
                if(grid[nr][nc]) {
                    if(dist[nr][nc] > weight-1) {
                        dist[nr][nc] = weight-1;
                        pq.emplace(weight-1,nr,nc);
                    }
                    break;
                }
            }
        }
    }
}

int Solve(const int sr, const int sc) {
    int ret = 0;
    MinHeap pq;
    FillHeap(sr,sc,pq);
    while(!pq.empty()) {
        const auto [w,r,c] = pq.top();
        pq.pop();
        if(dist[r][c] != w) continue;
        ret += w;
        FillHeap(r,c,pq);
    }

    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            if(grid[i][j] == 1 && dist[i][j] != 0) return -1;
        }
    }
    return ret;
}
}
// namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            cin >> grid[i][j];
        }
        fill_n(dist[i].begin(),M,INF);
    }
    int sr = -1, sc = -1;
    for(int i = 0; i<N; ++i) {
        for(int j=0;j<M;++j) {
            if(grid[i][j]) {
                sr = i, sc = j;
                break;
            }
        }
        if(sr != -1) break;
    }
    cout << Solve(sr,sc);
    return 0;
}