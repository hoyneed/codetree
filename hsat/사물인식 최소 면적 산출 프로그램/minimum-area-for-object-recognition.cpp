#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;
namespace {
constexpr int MAX_K = 21;
constexpr int MAX_X = 1001;
int N,K;
using Point = pair<int,int>;
array<vector<Point>, MAX_K> colors;
struct Square{
    int min_x, min_y;
    int max_x, max_y;
    int depth, area;
    Square() = default;
    Square(int minx,int miny, int maxx, int maxy,int d) :
        min_x(minx), min_y(miny), max_x(maxx), max_y(maxy), depth(d) {
        if(min_x == MAX_X) area = 0;
        else area = (max_x - min_x) * (max_y - min_y);
    }
    bool operator<(const Square& other) const {
        if(area != other.area) return area > other.area;
        return depth < other.depth;
    }
};

int FindMin() {
    priority_queue<Square> pq;
    pq.emplace(MAX_X,MAX_X,-MAX_X,-MAX_X,0);
    while(!pq.empty()) {
        const auto [min_x, min_y, max_x, max_y,depth,area] = pq.top();
        pq.pop();
        if(depth == K) {
            return area;
        }
        // 사각형 안에 이미 들어가는 점이 있는 경우 다른 경우 볼 필요 없이 바로 선택
        bool is_inside = false;
        for(const auto [nx,ny] : colors[depth + 1]) {
            if(min_x <= nx && nx <= max_x && min_y <= ny && ny <= max_y) {
                is_inside = true;
                pq.emplace(min_x,min_y,max_x,max_y,depth+1);
                break;
            }
        }
        if(is_inside) continue;
        for(const auto [nx,ny] : colors[depth + 1]) {
            const int nmin_x = min(min_x,nx);
            const int nmin_y = min(min_y,ny);
            const int nmax_x = max(max_x,nx);
            const int nmax_y = max(max_y,ny);
            pq.emplace(nmin_x,nmin_y,nmax_x,nmax_y,depth+1);
        }
    }
    return INT_MAX;
}
} // namespace


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> K;
    colors.fill({});
    for(int i=0;i<N;++i) {
        int x,y,k;
        cin >> x >> y >> k;
        colors[k].emplace_back(x,y);
    }
    cout << FindMin();
    return 0;
}