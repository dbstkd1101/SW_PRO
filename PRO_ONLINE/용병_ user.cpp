#include<list>
#include<algorithm>
using namespace std;

list<int> li[6][6];

struct Mercenary {
    int team;
    list<int>::iterator iter;
}mer[100003];

void init() {
    for (int i = 1; i <= 5; i++) for (int j = 1; j <= 5; j++) li[i][j].clear();
}

void hireMercenary(int id, int team, int score) {
    mer[id] = { team, li[team][score].insert(li[team][score].end(), id) };  // insert 반환값은 등록된 iterator

    //auto it = li[team][score].insert(li[team][score].end(), id);
    //mer[id] = { team, it };
}

void fireMercenary(int id) {
    *mer[id].iter = 0;          // 값을 0으로 변경하여 지워졌음을 표시한다
}

void updateMercenaryScore(int id, int score) {      // 기존 element는 지우고 새로운 점수 list로 고용한다
    *mer[id].iter = 0;
    hireMercenary(id, mer[id].team, score);
}

void updateTeamScore(int team, int newScore) {
    if (newScore < 0)
        for (int i = 2; i <= 5; i++) {
            int score = max(1, i + newScore);
            li[team][score].splice(li[team][score].end(), li[team][i]);
        }
    else if (newScore > 0)
        for (int i = 4; i >= 1; i--) {
            int score = min(5, i + newScore);
            li[team][score].splice(li[team][score].end(), li[team][i]);
        }
}

int bestMercenary(int team) {
    int ret = 0;
    for (int i = 5; i >= 1; i--) {
        //for (auto x : li[team][i]) ret = max(x, ret);

        for (auto it = li[team][i].begin(); it != li[team][i].end();) {
            ret = max(*it, ret);
            if (*it == 0) it = li[team][i].erase(it);
            else ++it;
        }

        if (ret) break;
    }
    return ret;
}