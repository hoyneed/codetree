#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <ranges>
#include <cmath>
using namespace std;
namespace {
using LL = long long;
constexpr int MAX_N = 1e5;
int N;
LL B;
array<int,MAX_N> perf;

bool Check (const int limit) {
    LL cost = 0;
    for(int i=0;i<N;++i) {
        if(perf[i] >= limit) return true;
        const int diff = limit - perf[i];
        cost += 1LL * diff * diff;
        if(cost > B) return false;
    }
    return true;
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> B;
    for(int i = 0;i<N;++i) {
        cin >> perf[i];
    }
    sort(perf.begin(), perf.begin() + N);
    int low = perf[0];
    int high = perf[0] + (int)sqrt(B);
    while(low <= high) {
        const int mid = low + (high - low) / 2;
        if(Check(mid)) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << high;
    return 0;
}