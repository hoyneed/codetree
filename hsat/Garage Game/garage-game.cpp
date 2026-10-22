#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

namespace {

constexpr int MAX_N = 15;
constexpr int MAX_ROWS = 3 * MAX_N;

using Board = array<array<int, MAX_N>, MAX_ROWS>;

struct Cell {
    int r, c;
    Cell() = default;
    Cell(int r, int c) : r(r), c(c) {}
};

int N;
int answer = 0;

constexpr int DR[4]{1, -1, 0, 0};
constexpr int DC[4]{0, 0, 1, -1};

void DFS(const Board& board, int turn, int score) {
    array<array<bool,MAX_N>,MAX_N> visited{};

    // 실제 차고는 아래쪽 N개 행
    const int base = 2 * N;

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {

            if (visited[r][c]) continue;

            // 1. BFS로 같은 색 연결 요소 탐색
            vector<Cell> component;
            component.reserve(MAX_N * MAX_N);

            component.emplace_back(r, c);
            visited[r][c] = true;

            const int color = board[base + r][c];

            int minR = r, maxR = r;
            int minC = c, maxC = c;

            for(int head = 0;head<(int)component.size();++head) {
                const Cell cur = component[head];

                minR = min(minR, cur.r);
                maxR = max(maxR, cur.r);
                minC = min(minC, cur.c);
                maxC = max(maxC, cur.c);

                for (int d = 0; d < 4; ++d) {
                    const int nr = cur.r + DR[d];
                    const int nc = cur.c + DC[d];

                    if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

                    if (visited[nr][nc]) continue;

                    if (board[base + nr][nc] != color) continue;
                    visited[nr][nc] = true;
                    component.emplace_back(nr,nc);
                }
            }

            // 2. 현재 연결 요소를 제거했을 때의 점수
            const int count = component.size();

            const int area =  (maxR - minR + 1) * (maxC - minC + 1);

            const int gain = count + area;

            // 3. 마지막 선택은 점수만 계산
            if (turn == 2) {
                answer = max(answer, score + gain);
                continue;
            }

            // 4. 다음 상태를 위해 격자 복사
            Board next = board;

            // 연결 요소의 차량 제거
            for (int i = 0; i < (int)component.size(); ++i) {
                const Cell p = component[i];
                next[base + p.r][p.c] = 0;
            }

            // 5. 중력 적용
            // 위쪽의 예비 차량까지 함께 떨어뜨림
            for (int col = 0; col < N; ++col) {
                int write = 3 * N - 1;

                for (int row = 3 * N - 1;
                     row >= 0; --row) {

                    if (next[row][col] != 0) {
                        next[write--][col] =
                            next[row][col];
                    }
                }

                // 남은 위쪽 영역을 빈칸 처리
                while (write >= 0) {
                    next[write--][col] = 0;
                }
            }

            // 6. 다음 턴 탐색
            DFS(next, turn + 1, score + gain);
        }
    }
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    Board board{};

    for (int r = 0; r < 3 * N; ++r) {
        for (int c = 0; c < N; ++c) {
            cin >> board[r][c];
        }
    }

    DFS(board, 0, 0);

    cout << answer;

    return 0;
}