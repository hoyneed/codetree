#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
namespace {
constexpr int MAX_N = 1000;
int N;
array<int,MAX_N> indegree;
array<vector<int>, MAX_N> graph;

void PrintFormat(const int num) {
    cout << setfill('0') << setw(3) << num;
}

void FindFirst() {
    vector<int> idg(indegree.begin(), indegree.begin() + N);
    vector<int> order(N);
    priority_queue<int,vector<int>,greater<>> pq;
    for(int i=0;i<N;++i) {
        if(idg[i] == 0) {
            pq.push(i);
        }
    }
    int num = 0;
    while(!pq.empty()) {
        const int u = pq.top();
        pq.pop();
        order[u] = ++num;
        for(const int v : graph[u]) {
            if(--idg[v] == 0) {
                pq.push(v);
            }
        }
    }
    for(const int i : order) {
        PrintFormat(i);
    }
}

void FindLast() {
    vector<int> idg(indegree.begin(), indegree.begin() + N);
    vector<int> order(N);
    priority_queue<int> pq;
    for(int i=0;i<N;++i) {
        if(idg[i] == 0) {
            pq.push(i);
        }
    }
    int num = 0;
    while(!pq.empty()) {
        const int u = pq.top();
        pq.pop();
        order[u] = ++num;
        for(const int v : graph[u]) {
            if(--idg[v] == 0) {
                pq.push(v);
            }
        }
    }
    for(const int i : order) {
        PrintFormat(i);
    }
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i=0;i<N-1;++i) {
        char op;
        cin >> op;
        if(op == '<') {
            graph[i].push_back(i+1);
            ++indegree[i+1];
        } else {
            graph[i+1].push_back(i);
            ++indegree[i];
        }
    }
    FindFirst();
    cout << '\n';
    FindLast();
    return 0;
}