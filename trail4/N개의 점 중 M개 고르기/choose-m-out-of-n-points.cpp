#include <iostream>
#include <array>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;
namespace {
constexpr int MAX_N = 21;
struct Point {
  int y,x;
};
int N,M;
array<Point, MAX_N> points;
array<array<int, MAX_N>, MAX_N> graph;
int answer;

int Dist(const Point& a, const Point& b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i=0;i<N;++i) {
      cin >> points[i].x >> points[i].y;
      graph[i][i] = 0;
      for(int j=0;j<i;++j) {
        const int dist = Dist(points[i], points[j]);
        graph[i][j] = dist;
        graph[j][i] = dist;
      }
    }
    answer = INT_MAX;
    vector<char> mask(N, 0);
    fill_n(mask.rbegin(), M, 1);
    do {
      int max_dist = 0;
      for(int i=0;i<N-1;++i) {
        if(!mask[i]) continue;
        for(int j=i+1;j<N;++j) {
          if(!mask[j]) continue;
          max_dist = max(max_dist, graph[i][j]);
        }
      }
      answer = min(answer, max_dist);
    } while (next_permutation(mask.begin(),mask.end()));
    cout << answer << '\n';

    return 0;
}