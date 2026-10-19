#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <tuple>
#include <ranges>
using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
struct Task {
    int preStart, len;
    bool output;
    Task() = default;
    Task(int p, int l, bool o) : preStart(p), len(l), output(o) {}
};
array<int, MAX_N> preorder;

} // namespace

int main() {
    // Please write your code here.
    ios::sync_with_stdio(false);
    cin >> N;
    
    for(int i=0;i<N;++i) {
        cin >> preorder[i];
    }
    vector<Task> st;
    st.emplace_back(0,N,false);
    bool is_first = true;
    while(!st.empty()) {
        const auto [preStart, len, output] = st.back();
        st.pop_back();
        if (len == 0) continue;
        const int root = preorder[preStart];
        // 후위 순회의 루트 노드 출력
        if(output) {
            if(!is_first) cout << '\n';
            cout << root;
            is_first = false;
            continue;
        }
        ranges::subrange sr(preorder.begin() + preStart + 1, preorder.begin() + preStart + len);
        const auto [l_st, r_ed] = sr;
        // 처음으로 root보다 커지는 노드가 오른쪽 구간의 시작
        const auto r_st = ranges::upper_bound(sr, root);
        const int leftLen = r_st - l_st;
        const int rightLen = r_ed - r_st;
        st.emplace_back(preStart,len,true);
        if(rightLen > 0) {
            st.emplace_back(preStart+leftLen+1,rightLen,false);
        }
        if(leftLen > 0) {
            st.emplace_back(preStart+1,leftLen,false);
        }
    }
    return 0;
}