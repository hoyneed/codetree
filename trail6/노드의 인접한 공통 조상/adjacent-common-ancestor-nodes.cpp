#include <iostream>
#include <array>
#include <vector>
#include <queue>

using namespace std;
namespace {
constexpr int MAX_N = 10'001;
int N;
int A,B;
array<int, MAX_N> parent;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    int root = -1;
    int root_deg = -1;
    for(int i=1;i<N;++i) {
        int u,v;
        cin >> u >> v;
        parent[v] = u;
    }
    cin >> A >> B;
    int depth_A = 0, depth_B = 0;
    int node = A;
    while(parent[node] != 0) {
        ++depth_A;
        node = parent[node];
    }
    node = B;
    while(parent[node] != 0 ) {
        ++depth_B;
        node = parent[node];
    }
    while(depth_A != depth_B) {
        if(depth_A > depth_B) {
            A = parent[A];
            --depth_A;
        } else {
            B = parent[B];
            --depth_B;
        }
    }
    while(A != B) {
        A = parent[A];
        B = parent[B];
    }
    cout << A;
    return 0;
}