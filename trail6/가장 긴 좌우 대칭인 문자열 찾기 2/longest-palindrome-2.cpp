#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
namespace {
constexpr int MAX_N = 200'001;
int N;
string temp, str;
int A[MAX_N];
} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> temp;
    str.reserve(2 * temp.length());
    for(const auto ch : temp) {
        str += '#';
        str += ch;
    }
    str += '#';
    N = str.length();
    int r=-1,p=-1;
    for(int i=0;i<N;++i) {
        if(r < i) {
            A[i] = 0;
        } else {
            int ii = 2 * p - i;
            A[i] = min(r-i,A[ii]);
        }

        while(i - A[i] >= 0 && i + A[i] + 1 < N &&
        str[i-A[i] - 1] == str[i + A[i] + 1]) ++A[i];

        if(i+A[i] > r) {
            r = i + A[i];
            p = i;
        }

    }
    int answer = 0;
    for(int i=0;i<N;++i){
        answer = max(answer, 2* A[i]+1);
    }
    cout << answer / 2;

    return 0;
}