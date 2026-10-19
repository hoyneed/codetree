#include <iostream>
#include <vector>
#include <array>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;

int N;
array<int,MAX_N> preorder;
array<int,MAX_N> inorder;
array<int,MAX_N> pos;

struct Task {
    int preStart;
    int inStart;
    int len;
    bool output;
};

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> preorder[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> inorder[i];
        pos[inorder[i]] = i;
    }

    vector<Task> st;
    st.reserve(2 * N);

    st.push_back({0, 0, N, false});

    bool first = true;

    while (!st.empty()) {
        Task cur = st.back();
        st.pop_back();

        if (cur.len == 0) continue;

        const int root = preorder[cur.preStart];

        // 후위 순회의 루트 출력 단계
        if (cur.output) {
            if (!first) cout << ' ';
            cout << root;
            first = false;
            continue;
        }

        // 중위 순회에서 루트 위치
        int rootPos = pos[root];

        // 왼쪽과 오른쪽 서브트리 크기
        int leftLen = rootPos - cur.inStart;
        int rightLen = cur.len - leftLen - 1;

        // 역순으로 삽입

        // 3. 루트 출력
        st.push_back({cur.preStart, cur.inStart,  cur.len, true});

        // 2. 오른쪽 서브트리
        if (rightLen > 0) {
            st.push_back({
                cur.preStart + 1 + leftLen,
                rootPos + 1,
                rightLen,
                false
            });
        }

        // 1. 왼쪽 서브트리
        if (leftLen > 0) {
            st.push_back({
                cur.preStart + 1,
                cur.inStart,
                leftLen,
                false
            });
        }
    }
    return 0;
}