/*
* user chaining
* 2634ms
*/
#include<stdio.h>
using namespace std;

const int LM = 4003;
const int SIZE = 1 << 24;
int A[LM], B[LM], C[LM], D[LM];

struct Node {
	int key, cnt;
	Node* next;
	Node* alloc(int _key, Node* _next) {
		key = _key, cnt = 1, next = _next;
		return this;
	}
}hbuf[LM * LM], * htab[SIZE];
int hcnt;

int probing(int key, bool ins = 1) {
	int hidx = (unsigned int)key % SIZE;
	for (Node* p = htab[hidx]; p; p = p->next) {
		if (p->key == key) {
			if (ins) p->cnt++;
			return p->cnt;
		}
	}
	if (ins) htab[hidx] = hbuf[hcnt++].alloc(key, htab[hidx]);
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
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