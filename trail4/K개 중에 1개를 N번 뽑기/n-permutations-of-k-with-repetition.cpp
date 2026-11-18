#include <iostream>
#include <vector>
using namespace std;
namespace {
int K,N;
vector<int> st;

void Run(const int lv) {
    if(lv == N) {
        for(const int i : st) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i=1;i<=K;++i) {
        st.push_back(i);
        Run(lv + 1);
        st.pop_back();
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K >> N;
    st.reserve(N);
    Run(0);
    return 0;
}