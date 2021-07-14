/*
* linear probing
*/
#include<stdio.h>
#include<algorithm>
using namespace std;
using pii = pair<int, int>; // key , cnt

const int LM = 4003;
const int SIZE = 1 << 25;
int A[LM], B[LM], C[LM], D[LM];
pii htab[SIZE];

int probing(int key, bool ins = 1) {
    int hidx = (unsigned int)key % SIZE;
    while (htab[hidx].second) {
        if (htab[hidx].first == key) {
            if (ins) htab[hidx].second++;
            return htab[hidx].second;
        }
        hidx = (hidx + 1) % SIZE;
    }
    if (ins) htab[hidx] = { key, 1 };
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d%d", &A[i], B + i, C + i, D + i);

    // a+b µî·Ï
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        probing(A[i] + B[j]);
    }

    // -c-d °Ë»ö
    long long ret = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        ret += probing(-C[i] - D[j], 0);
    }

    printf("%lld\n", ret);

    return 0;
}