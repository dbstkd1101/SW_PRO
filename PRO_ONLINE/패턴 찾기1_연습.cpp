#ifndef NULL
#define NULL 0
#endif

#include<unordered_map>
#include<string>

using namespace std;

const int LN = (int)(1e3);
const int LM = 20;

int N, M;
 
int map[LN][LN];

struct pos {
    int r, c;
}posTmp;

unordered_map<int, pos > hTab(LN*LN);

void init(int n, int ap[][1000], int m){
    N = n, M = m;
    hTab.clear();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == 0) map[i][j] = ap[i][j] & 1;
            else {
                map[i][j] = ((map[i][j - 1] << 1) | (ap[i][j] & 1));
                if ((i + 1 >= M) && (j + 1 >= M)) {
                    int key = 0;
                    for (int k = 0; k < 5; k++) {
                        key = ((key << 5) | (map[i - k][j] & (32 - 1)));
                    }
                    posTmp = { i - M + 1, j - M + 1 };
                    hTab.insert({ key, posTmp });
                }
            }
        }

    }
}
 
int query(int bp[][20]){
    int bpTmp[LM][LM] = {0};
    int key = 0;
    pos rst;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (j == 0) bpTmp[i][j] = bp[i][j];
            else {
                bpTmp[i][j] = ((bpTmp[i][j-1]<<1) | (bp[i][j]&1));
                if ((i + 1 == M) && (j + 1 == M)) {
                    for (int k = 0; k < 5; k++) {
                        key=( (key<<5)| (bpTmp[i-k][j]&(32-1)));
                    }
                    rst = hTab[key];
                }
            }
        }
    }

    return (rst.r * N + rst.c);
}