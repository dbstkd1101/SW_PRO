/*
* vector 6932ms
* list   9068ms
*/
#include<stdio.h>
#include<list>
#include<vector>
using namespace std;
using pii = pair<int, int>;

const int LM = 4003;
const int SIZE = 1 << 24;
//vector<pii> htab[SIZE];
list<pii> htab[SIZE];
int A[LM], B[LM], C[LM], D[LM];

int probing(int key, bool ins = 1) {
	int hidx = (unsigned int)key % SIZE;
	for (auto& p : htab[hidx]) {
		if (p.first == key) {
			if (ins) p.second++;
			return p.second;
		}
	}
	if (ins) htab[hidx].push_back({ key, 1 });
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