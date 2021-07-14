/*
* pair<int, int>
* first : frequency
* second : id
*/
#include<set>
using namespace std;
using pii = pair<int, int>;

struct Group {
    int sum;
    set<pii> s;

    template<typename T>        // pii type    
    void insert(T& key) {       // 값을 받아서 insert 
        sum += key.first;       // sum도 증가
        s.insert(key);
    }
    template<typename T>        // set<pii>::iterator type
    void erase(T it) {          // iterator를 받아서 erase
        sum -= it->first;       // sum도 감소
        s.erase(it);
    }
    void clear() {
        sum = 0;
        s.clear();
    }
}lgroup, rgroup;
auto& lset = lgroup.s;          // lgroup.s를 lset으로 접근하기 위해
auto& rset = rgroup.s;          // rgroup.s를 rset으로 접근하기 위해

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
    pii o = { obj.frequency, obj.id };
    if (lset.empty() || o < *lset.rbegin()) lgroup.insert(o);
    else rgroup.insert(o);
    balance();
}

int removeMembers(int mode) {
    int id = 0;
    if (mode == 0) {
        id = lset.begin()->second;
        lgroup.erase(lset.begin());
    }
    if (mode == 1) {
        if (lset.size() == rset.size()) {
            id = rset.begin()->second;
            rgroup.erase(rset.begin());
        }
        id += lset.rbegin()->second;
        lgroup.erase(--lset.end());
    }
    if (mode == 2 && rset.size()) {
        id = rset.rbegin()->second;
        rgroup.erase(--rset.end());
    }
    balance();
    return id;
}

void getSum(int sum[]) {
    sum[0] = lgroup.sum;
    sum[1] = rgroup.sum;
    if (lset.size() > rset.size()) sum[0] -= lset.rbegin()->first;
}

void userInit(int memberCount, Member members[]) {
    lgroup.clear(), rgroup.clear();
    for (int i = 0; i < memberCount; i++) addMember(members[i]);
}