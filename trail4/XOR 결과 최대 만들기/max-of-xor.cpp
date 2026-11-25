#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <cstdint>

using namespace std;
namespace {
constexpr int MAX_N = 20;
int N,M;
array<uint32_t, MAX_N> arr;

} // namespace
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i=0;i<N;++i) {
        cin >> arr[i];
    }
    vector<char> mask(N);
    fill_n(mask.rbegin(), M, 1);
    uint32_t answer = 0;
    do {
        uint32_t seed = 0;
        for(int i=0;i<N;++i) {
            if(mask[i]) {
                seed ^= arr[i];
            }
        }
        answer = max(answer, seed);
    } while (next_permutation(mask.begin(), mask.end()));
    cout << answer << '\n';

    return 0;
}