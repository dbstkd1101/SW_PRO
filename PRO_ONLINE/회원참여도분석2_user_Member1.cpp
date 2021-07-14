/// === sol.cpp ===
#ifndef NULL
#define NULL  0
struct Member {
    int id, frequency;
};
#endif

/*
* Member ���
* ä���� main�Լ��� Member�� ���ɰŶ�
* operator overloading class�ܺο� �ϵ� Compare����
*/
#include<set>
using namespace std;

struct Compare {
    bool operator()(const Member& a, const Member& b) const {
        return a.frequency != b.frequency ? a.frequency < b.frequency : a.id < b.id;
    }
};
set<Member, Compare> lset, rset;
int lsum, rsum;

void balance() {
    if (lset.size() > rset.size() + 1) {
        lsum -= lset.rbegin()->frequency;
        rsum += lset.rbegin()->frequency;
        //����.... Value�� �׳� �־ �Ǵ� �ű���.
        rset.insert(*lset.rbegin());
        //�Ǽ� ����
        lset.erase(--lset.end());
    }
    if (lset.size() < rset.size()) {
        lsum += rset.begin()->frequency;
        rsum -= rset.begin()->frequency;
        lset.insert(*rset.begin());
        rset.erase(rset.begin());
    }
}

void addMember(Member obj) {
    if (lset.empty() || Compare{}(obj, *lset.rbegin())) {
        lsum += obj.frequency;
        lset.insert(obj);
    }
    else {
        rsum += obj.frequency;
        rset.insert(obj);
    }
    balance();
}

int removeMembers(int mode) {
    int id = 0;
    if (mode == 0) {
        id = lset.begin()->id;
        lsum -= lset.begin()->frequency;
        lset.erase(lset.begin());
    }
    if (mode == 1) {
        if (lset.size() == rset.size()) {
            id = rset.begin()->id;
            rsum -= rset.begin()->frequency;
            rset.erase(rset.begin());
        }
        id += lset.rbegin()->id;
        lsum -= lset.rbegin()->frequency;
        lset.erase(--lset.end());
    }
    if (mode == 2 && rset.size()) {
        id = rset.rbegin()->id;
        rsum -= rset.rbegin()->frequency;
        rset.erase(--rset.end());
    }
    balance();
    return id;
}

void getSum(int sum[]) {
    sum[0] = lsum;
    sum[1] = rsum;
    if (lset.size() > rset.size()) sum[0] -= lset.rbegin()->frequency;
}

void userInit(int memberCount, Member members[]) {
    lsum = rsum = 0;
    lset.clear(), rset.clear();
    for (int i = 0; i < memberCount; i++) addMember(members[i]);
}