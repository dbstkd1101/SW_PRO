#ifndef NULL
#define NULL 0
#endif

#include<unordered_map>
#include<string>

using namespace std;

const int LN = (int)(1e3);
const int LM = 20;

int N, M;
 
int map[LM][LM];

void init(int n, int ap[][1000], int m){
    N = n, M = m;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = ((map[i][j - 1] << 1) | (ap[i][j]&1));
            if ((i + 1 >= M) && (j + 1 >= M)) {

            }
        }
    }
}
 
int query(int bp[][20]){
    int row = 0, col = 0;
 
    return row * N + col;
}