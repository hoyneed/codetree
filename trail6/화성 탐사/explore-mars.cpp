#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <numeric>
#include <tuple>
#include <queue>
#include <unordered_map>

using namespace std;
namespace {
constexpr int DY[4]{-1,0,1,0};
constexpr int DX[4]{0,-1,0,1};
constexpr int MAX_N = 50;
constexpr int MAX_X = 102;
int N;
using Point = pair<int,int>; // {y,x}
struct HashPoint{
    size_t operator()(const Point& p) const {
        return hash<int>{}(p.first) ^ (hash<int>{}(p.second) << 2);
    }
};
using Edge = tuple<int,int,int>; // {거리, from, to}
int idx;
array<array<int,MAX_N>,MAX_N> grid;
array<Point,MAX_X> stations;
array<array<bool,MAX_N>,MAX_N> visited;
unordered_map<Point,int, HashPoint> index;
vector<Edge> edges;
array<int,MAX_X> parent;
array<int,MAX_X> ranks;
int groups;

int Find(int x) {
    while(x != parent[x]) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return false;
    if(ranks[a] < ranks[b]) swap(a,b);
    else if (ranks[a] == ranks[b]) ++ranks[a];
    parent[b] = a;
    --groups;
    return true;
}


bool IsOut(const int r, const int c) {
    if(r<0||c<0||r>=N||c>=N) return true;
    return false;
}

void BFS(const int start) {
    const auto& [start_y, start_x] = stations[start];
    int found = 0;
    for(int i=0;i<N;++i) {
        fill_n(visited[i].begin(),N,false);
    }
    visited[start_y][start_x] = false;
    queue<Point> q;
    q.emplace(start_y,start_x);
    for(int dist=0;dist<N*N && !q.empty();++dist) {
        int sz = q.size();
        while(sz--) {
            const auto [y,x] = q.front();
            q.pop();
            for(int d=0;d<4;++d) {
                const int ny = y + DY[d];
                const int nx = x + DX[d];
                if(IsOut(ny,nx) || visited[ny][nx] || grid[ny][nx] == -1) continue;
                visited[ny][nx] = true;
                if(grid[ny][nx] == 2) {
                    const int to = index[Point(ny,nx)];
                    if(to > start) {
                        edges.emplace_back(dist+1,start,to);
                        if(++found == idx - start) return;
                    }
                }
                q.emplace(ny,nx);
            }
        }
    }
}
} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    idx = 1;
    index.reserve(MAX_X);
    for(int r=0;r<N;++r) {
        for(int c=0;c<N;++c) {
            cin >> grid[r][c];
            if(grid[r][c] == 2) {
                stations[idx] = {r,c};
                index[stations[idx]] = idx;
                ++idx;
            } else if (grid[r][c] == 1) {
                stations[0] = {r,c};
                index[stations[0]] = 0;
            }
        }
    }
    edges.reserve((idx+1) * idx / 2);
    for(int i=0;i<idx-1;++i) {
        BFS(i);
    }
    ranges::sort(edges);
    groups = idx;
    iota(parent.begin(),parent.begin()+idx,0);
    int answer = 0;
    for(const auto& [w,u,v] : edges) {
        if(groups == 1) break;
        if(Union(u,v)) {
            answer += w;
        }
    }
    cout << (groups == 1 ? answer : -1);
    return 0;
}