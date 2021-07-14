#include<stdio.h>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

vector<int> v;	// ctrl + r * 2 함수, 변수명 일괄 변경

void insert(int x) {
    // lower_bound : x보다 크거나 같은 가장 처음 iterator 반환
    // upper_bound: x보다 큰 가장 처음 iterator 반환
    auto it = lower_bound(v.begin(), v.end(), x);   // O(log n)
    if (it != v.end() && *it == x) return;
    v.insert(it, x);
}

void erase(int x) {
    auto it = lower_bound(v.begin(), v.end(), x);   // O(log n)
    if (it == v.end() || *it != x) return;

    //auto it = find(v.begin(), v.end(), x);            // O(n)
    //if (it == v.end()) return;

    v.erase(it);
}

void update(int x, int y) {
    auto it_x = lower_bound(v.begin(), v.end(), x); // O(log n)
    if (it_x == v.end() || *it_x != x) return;

    if (binary_search(v.begin(), v.end(), y)) return; // O(log n)

    v.erase(it_x);
    v.insert(lower_bound(v.begin(), v.end(), y), y);
}

void front(int c) {
    if (v.empty()) printf("empty\n");
    else if (v.size() < c) printf("%d\n", v.back());
    else printf("%d\n", v[c - 1]);
}

void back(int c) {
    if (v.empty()) printf("empty\n");
    else if (v.size() < c) printf("%d\n", v.front());
    else printf("%d\n", v[v.size() - c]);
}

int main() {
    int t, q, x, y;
    string cmd;
    scanf("%d", &t);
    for (; t; t--) {
        v.clear();
        scanf("%d", &q);
        for (; q; q--) {
            cin >> cmd >> x;
            if (cmd == "insert") insert(x);
            else if (cmd == "erase") erase(x);
            else if (cmd == "update") {
                cin >> y;
                update(x, y);
            }
            else if (cmd == "front") front(x);
            else back(x);
        }
    }
    return 0;
}