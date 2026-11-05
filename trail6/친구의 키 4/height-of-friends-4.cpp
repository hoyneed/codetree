#include <iostream>
#include <vector>
#include <utility>

using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N, M;
struct Edge {
    int from, to;
};

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;


    vector<Edge> edges(M);
    // {도착 정점, 단서 인덱스}
    vector<vector<pair<int, int>>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        auto& [a, b] = edges[i];
        cin >> a >> b;

        graph[a].emplace_back(b, i);
    }

    // 처음 k개의 단서에 모순이 없는지 판별
    auto IsConsistent = [&](int k) -> bool {
        vector<int> indegree(N + 1, 0);

        // 처음 k개의 간선만 고려
        for (int i = 0; i < k; ++i) {
            ++indegree[edges[i].to];
        }

        // 위상 정렬
        vector<int> que;
        que.reserve(N);

        for (int i = 1; i <= N; ++i) {
            if (indegree[i] == 0) {
                que.push_back(i);
            }
        }

        for (int head = 0; head < (int)que.size(); ++head) {
            const int cur = que[head];
            for (const auto& [next, idx] : graph[cur]) {
                // k번째 이후의 단서는 제외
                if (idx >= k) break;

                if (--indegree[next] == 0) {
                    que.push_back(next);
                }
            }
        }

        // 모든 정점을 처리했다면 사이클 없음
        return (int)que.size() == N;
    };

    // 최초로 모순이 발생하는 단서의 번호
    int low = 1;
    int high = M + 1;

    while (low < high) {
        const int mid = low + (high - low) / 2;

        if (IsConsistent(mid)) {
            // 아직 모순이 없으므로 더 많은 단서 확인
            low = mid + 1;
        }
        else {
            // 이미 모순이 발생했으므로 앞쪽 확인
            high = mid;
        }
    }

    if (low == M+1) {
        cout << "Consistent";
    } else {
        cout << low;
    }

    return 0;
}