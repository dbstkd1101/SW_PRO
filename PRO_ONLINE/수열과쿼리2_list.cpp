#include<stdio.h>
#include<list>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

list<int> li;

void insert(int x) {
    auto it = lower_bound(li.begin(), li.end(), x); // O(n) : list는 random access iterator가 아니므로 log 복잡도가 적용되지 않는다.
    if (it != li.end() && *it == x) return;
    li.insert(it, x);
}

void erase(int x) {
    auto it = lower_bound(li.begin(), li.end(), x); // O(n)
    if (it == li.end() || *it != x) return;
    li.erase(it);
}

void update(int x, int y) {
    auto it_x = lower_bound(li.begin(), li.end(), x); // O(n)
    if (it_x == li.end() || *it_x != x) return;

    auto it_y = lower_bound(li.begin(), li.end(), y); // O(n)
    if (it_y != li.end() && *it_y == y) return;

    *it_x = y;
    li.splice(it_y, li, it_x);
}

void front(int c) {
    if (li.empty()) printf("empty\n");
    else if (li.size() < c) printf("%d\n", li.back());
    else printf("%d\n", *next(li.begin(), c - 1));
}

void back(int c) {
    if (li.empty()) printf("empty\n");
    else if (li.size() < c) printf("%d\n", li.front());
    else printf("%d\n", *prev(li.end(), c));
}

int main() {
    freopen("input.txt", "r", stdin);
    int t, q, x, y;
    string cmd;
    scanf("%d", &t);
    for (; t; t--) {
        li.clear();
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