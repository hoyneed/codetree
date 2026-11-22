#include <iostream>
#include <vector>
using namespace std;
namespace {
int K, N;
vector<int> vect;

void DFS() {
    const int depth = vect.size();
    if (depth == N) {
        for (const int i : vect) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i=1;i<=K;++i) {
        if(depth > 1 &&
            i == vect[depth-1] && i == vect[depth-2]) {
            continue;
        }
        vect.push_back(i);
        DFS();
        vect.pop_back();
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K >> N;
    vect.reserve(N);
    DFS();

    return 0;
}