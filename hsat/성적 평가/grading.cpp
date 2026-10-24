#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
namespace {
constexpr int MAX_N = 100'001;
int N;
using Score = array<int,4>;
using Rank = array<int,4>;
array<Score, MAX_N> scores;
array<Rank, MAX_N> ranks;
vector<int> indices;

void FillRank(const int game) {
    auto cmp = [&](const int a, const int b) {
        return scores[a][game] > scores[b][game];
    };
    ranges::sort(indices,cmp);
    int r = 0;
    int p = 1;
    int s = 5000;
    for(const int i : indices) {
        if(s > scores[i][game]) {
            s = scores[i][game];
            r += p;
            p = 0;
        }
        ranks[i][game] = r;
        ++p;
    }
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N;
    for(int i=0;i<3;++i) {
        for(int j=0;j<N;++j) {
            cin >> scores[j][i];
            scores[j][3] += scores[j][i];
        }
    }
    indices.resize(N);
    iota(indices.begin(),indices.end(),0);
    for(int i=0;i<4;++i) {
        FillRank(i);
    }
    for(int i=0;i<4;++i) {
        for(int j=0;j<N;++j) {
            cout << ranks[j][i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}