/// === sol.cpp ===
#ifndef NULL
#define NULL  0
struct Member {
    int id, frequency;
};
#endif

/*
* Member 사용
* set과 sum을 관리하는 group 생성
*/
#include<set>
using namespace std;

struct Compare {
    bool operator()(const Member& a, const Member& b) const {
        return a.frequency != b.frequency ? a.frequency < b.frequency : a.id < b.id;
    }
};
struct Group {
    int sum;
    set<Member, Compare> s;

    template<typename T>            // Member type
    void insert(T& key) {           // 값을 받아서 insert
        sum += key.frequency;       // sum도 추가
        s.insert(key);
    }
    template<typename T>            // set<Member, Compare>::iterator type
    void erase(T it) {              // iterator 받아서 erase
        sum -= it->frequency;       // sum도 감소
        s.erase(it);
    }
    void clear() {
        sum = 0;
        s.clear();
    }
}lgroup, rgroup;
auto& lset = lgroup.s;          // lgroup.s를 lset으로 접근하기 위해
auto& rset = rgroup.s;          // rgroup.s를 lset으로 접근하기 위해

void balance() {
    if (lset.size() > rset.size() + 1) {
        rgroup.insert(*lset.rbegin());
        lgroup.erase(--lset.end());
    }
    if (lset.size() < rset.size()) {
        lgroup.insert(*rset.begin());
        rgroup.erase(rset.begin());
    }
}

void addMember(Member obj) {
    if (lset.empty() || Compare{}(obj, *lset.rbegin())) lgroup.insert(obj);
    else rgroup.insert(obj);
    balance();
}

int removeMembers(int mode) {
    int id = 0;
    if (mode == 0) {
        id = lset.begin()->id;
        lgroup.erase(lset.begin());
    }
    if (mode == 1) {
        if (lset.size() == rset.size()) {
            id = rset.begin()->id;
            rgroup.erase(rset.begin());
        }
        id += lset.rbegin()->id;
        lgroup.erase(--lset.end());
    }
    if (mode == 2 && rset.size()) {
        id = rset.rbegin()->id;
        rgroup.erase(--rset.end());
    }
    balance();
    return id;
}

void getSum(int sum[]) {
    sum[0] = lgroup.sum;
    sum[1] = rgroup.sum;
    if (lset.size() > rset.size()) sum[0] -= lset.rbegin()->frequency;
}

void userInit(int memberCount, Member members[]) {
    lgroup.clear(), rgroup.clear();
    for (int i = 0; i < memberCount; i++) addMember(members[i]);
}