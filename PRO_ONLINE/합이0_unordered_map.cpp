/*
* unordered_map
* Time limit exceed
*/
#include<stdio.h>
#include<unordered_map>
using namespace std;

const int LM = 4003;
unordered_map<int, int> htab;	// a+b , cnt
int A[LM], B[LM], C[LM], D[LM];



int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d%d", &A[i], B + i, C + i, D + i);

	// a+b µî·Ï
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		htab[A[i] + B[j]]++;
	}

	// -c-d °Ë»ö
	long long ret = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		if (htab.count(-C[i] - D[j])) ret += htab[-C[i] - D[j]];
	}

	printf("%lld\n", ret);

	return 0;
}