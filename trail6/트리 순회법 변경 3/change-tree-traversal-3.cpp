#include <iostream>
#include <array>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_N = 100'001;

int N;
array<int, MAX_N> inorder;
array<int, MAX_N> postorder;
array<int, MAX_N> pos;

struct Task {
    int inStart;
    int postStart;
    int len;
};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    // 중위 순회
    for (int i = 0; i < N; ++i) {
        cin >> inorder[i];
        pos[inorder[i]] = i;
    }

    // 후위 순회
    for (int i = 0; i < N; ++i) {
        cin >> postorder[i];
    }

    vector<Task> st;
    st.reserve(N);
    st.push_back({0, 0, N});

    bool first = true;

    while (!st.empty()) {
        const Task cur = st.back();
        st.pop_back();

        if (cur.len == 0) continue;

        // 후위 순회의 마지막 원소가 루트
        const int root = postorder[cur.postStart + cur.len - 1];

        // 전위 순회이므로 루트부터 출력
        if (!first) cout << ' ';
        cout << root;
        first = false;

        // 중위 순회에서 루트의 위치
        const int rootPos = pos[root];

        // 왼쪽/오른쪽 서브트리 크기
        const int leftLen = rootPos - cur.inStart;
        const int rightLen = cur.len - leftLen - 1;

        // 스택은 LIFO이므로 오른쪽부터 추가

        // 오른쪽 서브트리
        if (rightLen > 0) {
            st.push_back({
                rootPos + 1,
                cur.postStart + leftLen,
                rightLen
            });
        }

        // 왼쪽 서브트리
        if (leftLen > 0) {
            st.push_back({
                cur.inStart,
                cur.postStart,
                leftLen
            });
        }
    }
    return 0;
}