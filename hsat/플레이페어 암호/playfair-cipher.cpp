#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;
namespace {
int K,L;
string message, key;
using Point = pair<int,int>;
array<bool,26> exists;
array<array<char,5>,5> grid;
array<Point,26> pos;

vector<array<char,2>> Split() {
    vector<array<char,2>> ret;
    ret.reserve(L);
    int idx = 0;
    while(idx < L) {
        ret.push_back({});
        auto& arr = ret.back();
        arr[0] = message[idx++];
        if(idx >= L) {
            arr[1] = 'X';
        } else if(arr[0] == message[idx]) {
            if(arr[0] == 'X') {
                arr[1] = 'Q';
            } else {
                arr[1] = 'X';
            }
        } else {
            arr[1] = message[idx++];
        }
    }
    return ret;
}

void Encode(vector<array<char,2>>& vec) {
    for(auto& arr: vec) {
        auto [r0, c0] = pos[arr[0]-'A'];
        auto [r1, c1] = pos[arr[1]-'A'];
        if(r0 == r1) {
            c0 = (c0+1) % 5;
            c1 = (c1+1) % 5;
            arr[0] = grid[r0][c0];
            arr[1] = grid[r1][c1];
        } else if (c0 == c1) {
            r0 = (r0+1) % 5;
            r1 = (r1+1) % 5;
            arr[0] = grid[r0][c0];
            arr[1] = grid[r1][c1];
        } else {
            swap(c0,c1);
            arr[0] = grid[r0][c0];
            arr[1] = grid[r1][c1];
        }
    }
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> message >> key;
    L = message.length();
    K = key.length();
    int idx = 0;
    int ch_idx = 0;
    exists = {};
    for(int r=0;r<5;++r) {
        for(int c=0;c<5;++c) {
            while(idx < K && exists[key[idx] - 'A']) {
                ++idx;
            }
            if(idx == K) {
                while(exists[ch_idx] || ch_idx == int('J' - 'A')) {
                    ++ch_idx;
                }
                exists[ch_idx] = true;
                grid[r][c] = char('A' + ch_idx);
            } else {
                exists[key[idx] - 'A'] = true;
                grid[r][c] = key[idx++];
            }
            pos[grid[r][c] - 'A'] = {r,c};
        }
    }
    vector<array<char,2>> vec = Split();
    Encode(vec);
    for(const auto& arr : vec) {
        cout << arr[0] << arr[1];
    }
    return 0;
}