/// === sol.cpp ===
#ifndef NULL
#define NULL  0
struct Member {
    int id, frequency;
};
#endif

/// === submit area start ===
#include <set>
#include <string>
using namespace std;

struct compare {
    bool operator()(const Member& a, const Member& b) const {
        return a.frequency != b.frequency ? a.frequency < b.frequency : a.id < b.id;
    }
}comp;

set<Member, compare> leftSet;
set<Member, compare> rightSet;
Member mid;
int memCnt;
int freqSum[2];

extern void shuffle();

void addMember(Member obj) {
    if (memCnt == 0) mid = obj;
    else {
        if (comp(obj, mid)) {
            leftSet.insert(obj);
            freqSum[0] += obj.frequency;
        }
        else {
            rightSet.insert(obj);
            freqSum[1] += obj.frequency;
        }
        shuffle();
    }
}

int removeMembers(int mode) {
    int rst=-1;

    switch (mode) {
    case 0:
        if (memCnt == 1) {
            rst = mid.id;
            memset(&mid, -1, sizeof(mid));
        }
        else if (memCnt > 1) {
            auto it = leftSet.begin();
            rst = it->id;
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
        }
        memCnt--;
        shuffle();
        return rst;
    case 1:
        //Ȧ�� �� ��
        if (memCnt%2==1) {
            rst = mid.id;
            memset(&mid, -1, sizeof(mid));
            memCnt--;
        }
        //¦�� �� �� && �� ���̻� ���� ��
        else if(memCnt>0){
            rst = mid.id;
            memset(&mid, -1, sizeof(mid));
            memCnt--;

            auto it = leftSet.end();
            it--;
            rst += it->id;
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
            memCnt--;
        }
        shuffle();
        return rst;
    case 2:
        if (1 <= memCnt && memCnt <= 2) {
            rst = mid.id;
            memset(&mid, -1, sizeof(mid));
        }
        else if (memCnt > 2) {
            auto it = rightSet.begin();
            rst = it->id;
            freqSum[1] -= it->frequency;
            rightSet.erase(it);
        }
        memCnt--;
        shuffle();
        return rst;
    }
}

void getSum(int sum[]) {    
      sum[0] = freqSum[0];
      sum[1] = freqSum[1];
}

void shuffle() {
    //mid�� ���� ���
    if (mid.id == -1) {
        // left�� �� ���� �� -> mid�� �ϳ� toss
        if (leftSet.size() > rightSet.size()) {
            auto it = --leftSet.end();
            mid = { it->id, it->frequency };
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
        }
        // ���� ���� ���, right -> mid�� �ϳ� toss
        else {
            if (memCnt > 0) {
                auto it = rightSet.begin();
                mid = { it->id, it->frequency };
                freqSum[1] -= it->frequency;
                rightSet.erase(it);
            }
        }
    }
    // mid�� �����ϸ鼭
    else {
        // ������ �� ������
        if (leftSet.size() - 1 > rightSet.size()) {
            auto it = --leftSet.end();
            Member tmp = mid;
            mid = { it->id, it->frequency };
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
            rightSet.insert(tmp);
        }
        // �������� �� ������
        else if (leftSet.size() < rightSet.size()) {
            auto it = rightSet.begin();
            Member tmp = mid;
            mid = { it->id, it->frequency };
            freqSum[1] -= it->frequency;
            rightSet.erase(it);
            leftSet.insert(tmp);
        }
    }
}

void userInit(int memberCount, Member members[]) {
    freqSum[0] = 0, freqSum[1] = 0;
    // mid �ʱ�ȭ
    memset(&mid, -1, sizeof(mid));
    leftSet.clear();
    rightSet.clear();
    for (int i = 0; i < memberCount; i++) {
        if (i == 0) mid = members[i];
        else {
            if (comp(members[i], mid)) {
                leftSet.insert(members[i]);
                freqSum[0] += members[i].frequency;
            }
            else {
                rightSet.insert(members[i]);
                freqSum[1] += members[i].frequency;
            }
            shuffle();
        }
    }
    memCnt = memberCount;
}
