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
        //홀수 일 때
        if (memCnt%2==1) {
            rst = mid.id;
            memset(&mid, -1, sizeof(mid));
            memCnt--;
        }
        //짝수 일 때 && 한 개이상 있을 때
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
    //mid가 없을 경우
    if (mid.id == -1) {
        // left가 더 많을 때 -> mid로 하나 toss
        if (leftSet.size() > rightSet.size()) {
            auto it = --leftSet.end();
            mid = { it->id, it->frequency };
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
        }
        // 서로 같을 경우, right -> mid로 하나 toss
        else {
            if (memCnt > 0) {
                auto it = rightSet.begin();
                mid = { it->id, it->frequency };
                freqSum[1] -= it->frequency;
                rightSet.erase(it);
            }
        }
    }
    // mid가 존재하면서
    else {
        // 왼쪽이 더 많으면
        if (leftSet.size() - 1 > rightSet.size()) {
            auto it = --leftSet.end();
            Member tmp = mid;
            mid = { it->id, it->frequency };
            freqSum[0] -= it->frequency;
            leftSet.erase(it);
            rightSet.insert(tmp);
        }
        // 오른쪽이 더 많으면
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
    // mid 초기화
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
