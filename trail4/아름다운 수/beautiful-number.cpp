#include <iostream>
#include <vector>
using namespace std;
namespace {
int N;
int cnt;
vector<int> st;
void Run() {
    if((int)st.size() == N) {
        ++cnt;
        return;
    }
    for(int i=1;i<=4;++i) {
        if((int)st.size() + i > N) break;
        for(int j=0;j<i;++j) {
            st.push_back(i);
        }
        Run();
        st.resize(st.size() - i);
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    st.reserve(N);
    cnt = 0;
    Run();
    cout << cnt << '\n';
    return 0;
}