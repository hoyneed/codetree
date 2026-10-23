#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
namespace {
constexpr int DY[4]{1,0,-1,0};
constexpr int DX[4]{0,-1,0,1};
constexpr int MAX_N = 200'001;
// 각 차선 기준 오른쪽 차선
constexpr int RT[4]{3,0,1,2};
int N;
array<pair<int,int>,MAX_N> arr;
array<int,MAX_N> pass_t;
array<queue<int>,4> ques;
array<bool,4> can_pass;

// 모든 큐가 비었는지 확인
bool IsEmpty() {
    const auto& [q0,q1,q2,q3] = ques;
    return q0.empty() && q1.empty() && q2.empty() && q3.empty();
}
// 모든 큐에 원소가 있는지 확인
bool IsOver() {
    const auto& [q0,q1,q2,q3] = ques;
    return !q0.empty() && !q1.empty() && !q2.empty() && !q3.empty();
}
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=1;i<=N;++i) {
        int t;
        char w;
        cin >> t >> w;
        arr[i] = {t, w - 'A'};
    }
    fill_n(pass_t.begin()+1,N,-1);
    int time = 0;
    int car_idx = 1;
    while(true) {
        while(car_idx <= N && arr[car_idx].first == time) {
            ques[arr[car_idx].second].push(car_idx);
            ++car_idx;
        }
        // 아직 들어올 차가 있는데 대기열에 차가 없으면 다음 차가 들어오는 시간까지 점프
        // 들어올 차가 없고 대기열이 비었으면 종료
        if(IsEmpty()) {
            if(car_idx <= N){
                time = arr[car_idx].first;
                continue;
            } else {
                break;
            }
        }
        // 모든 위치에 차가 있으면 교착상태로 종료
        if(IsOver()) break;
        for(int i=0;i<4;++i) {
            can_pass[i] = ques[RT[i]].empty();
        }
        for(int i=0;i<4;++i) {
            if(!can_pass[i] || ques[i].empty()) continue;
            const int cur = ques[i].front();
            ques[i].pop();
            pass_t[cur] = time;
        }
        ++time;
    }
    for(int i=1;i<=N;++i) {
        cout << pass_t[i] << '\n';
    }
    return 0;
}