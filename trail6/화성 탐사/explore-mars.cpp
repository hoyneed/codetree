#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

namespace {
using Point = pair<int, int>;
constexpr int INF = 1'000'000'000;
constexpr int dr[4]{-1, 1, 0, 0};
constexpr int dc[4]{0, 0, -1, 1};

int N;
vector<vector<int>> board;
vector<Point> bases;

// 활성화된 기지 집합에서 가장 가까운
// 비활성 기지를 찾아 반환
pair<int, int> FindNearest(const vector<bool>& selected) {
    vector<vector<int>> dist(N, vector<int>(N, -1));

    queue<Point> q;

    // Multi-source BFS:
    // 모든 활성화된 기지를 시작점으로 사용
    for (int i = 0; i < (int)bases.size(); ++i) {
        if (!selected[i]) continue;

        auto [r, c] = bases[i];

        dist[r][c] = 0;
        q.emplace(r, c);
    }

    // BFS
    while(!q.empty()) {
        const auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            const int nr = r + dr[d];
            const int nc = c + dc[d];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;
            if (board[nr][nc] == -1) continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.emplace(nr, nc);
        }
    }

    // 가장 가까운 비활성 기지 선택
    int bestID = -1;
    int bestDist = INF;

    for (int i = 0; i < (int)bases.size(); ++i) {
        if (selected[i]) continue;

        const auto [r, c] = bases[i];

        if (dist[r][c] == -1) continue;

        if (dist[r][c] < bestDist) {
            bestDist = dist[r][c];
            bestID = i;
        }
    }

    return {bestID, bestDist};
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    board.resize(N, vector<int>(N));

    Point start{-1, -1};

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cin >> board[r][c];

            if (board[r][c] == 1) {
                start = {r, c};
            }
            else if (board[r][c] == 2) {
                bases.push_back({r, c});
            }
        }
    }

    // 최초 활성화 기지를 0번 인덱스로
    bases.insert(bases.begin(), start);

    int B = bases.size();

    vector<bool> selected(B, false);
    selected[0] = true;

    int answer = 0;

    // Prim: 매번 가장 가까운 비활성 기지 추가
    for (int count = 1; count < B; ++count) {
        auto [next, cost] = FindNearest(selected);

        // 도달 가능한 비활성 기지가 없다면
        // 모든 기지를 활성화할 수 없음
        if (next == -1) {
            cout << -1;
            return 0;
        }

        selected[next] = true;
        answer += cost;
    }

    cout << answer;

    return 0;
}