#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;
namespace {
int N,M;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    vector<int> arr(N);
    iota(arr.begin(), arr.end(), 1);
    vector<char> mask(N,0);
    fill_n(mask.begin(), M, 1);
    do {
        for (int i=0;i<N;++i) {
            if(mask[i]) {
                cout << arr[i] << ' ';
            }
        }
        cout << '\n';
    } while(prev_permutation(mask.begin(),mask.end()));

    return 0;
}