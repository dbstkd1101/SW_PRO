#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

const int LM = (int)(1e6) + 3;

int K;
char input[LM];


struct Data {
	int dna[4];
	
	bool operator==(const Data& r) const {
		return (dna[0] == r.dna[0] && dna[1] == r.dna[1] && dna[2] == r.dna[2] && dna[3] == r.dna[3]);
	}
}dna;

struct MyHash {
	size_t operator()(const Data& a) const{
		return a.dna[0] * 1001 * 1001 * 1001 + a.dna[1] * 1001 * 1001 + a.dna[2] * 1001 + a.dna[3];
	}
};

// ACGT
void update(Data& _dna, int idx, int mode) {
	if (mode == -1) _dna.dna[idx]--;
	if (mode == 1) _dna.dna[idx]++;
}

int idxDNA(char input) {
	int rst = -1;
	if (input == 'A') rst = 0;
	if (input == 'C') rst = 1;
	if (input == 'G') rst = 2;
	if (input == 'T') rst = 3;
	return rst;
}

unordered_map<Data, int, MyHash> hTab;

int main() {
	freopen("input.txt", "r", stdin);
	int maxRst = -1;
	scanf("%d", &K);
	scanf("%s", input);
	for (int i = 0; *(input + i); i++) {
		if (i + 1 >= K) {
			if (i + 1 > K) {
				update(dna, idxDNA(input[i - K]), -1);
			}
			update(dna, idxDNA(input[i]), 1);
			if(maxRst < ++hTab[dna]) maxRst= hTab[dna];
		}
	}
	printf("%d", maxRst);

	return 0;
}