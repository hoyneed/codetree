#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
namespace {
constexpr int MAX_N = 15;
int N;
using Line = pair<int,int>;
vector<Line> segments;
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    segments.reserve(N);
    for(int i=0;i<N;++i) {
        int l,r;
        cin >> l >> r;
        segments.emplace_back(l,r);
    }
    ranges::sort(segments, [](const Line& a, const Line& b)
    {
        if(a.second != b.second) return a.second < b.second;
        return a.first > b.first;
    });
    int cnt = 0;
    int cur = -1;
    for(const auto& [l,r] : segments) {
        if(l <= cur) continue;
        cur = r;
        ++cnt;
    }
    cout << cnt;

    return 0;
}