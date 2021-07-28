#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

const int LM = (int)(1e6) + 3;

int k;
char str[LM];
int cnt[4];

struct Data {
	int a, c, g, t;
};

struct myHash {
	size_t operator()(const Data &d) const{
		return d.a * (1000) * (1000) * (1000) + d.c * (1000) * (1000) + d.g * (1000) + d.t;
	}
};

struct myEqual {
	size_t operator()(const Data& d1, const Data&d2) const {
		return (d1.a == d2.a) && (d1.c == d2.c) && (d1.g == d2.g) && (d1.t == d2.t);
	}
};

unordered_map<Data, int, myHash, myEqual> htab;


void update(Data & _cur, char c, int param) {
	if (c == 'A') _cur.a += param;
	if (c == 'C') _cur.c += param;
	if (c == 'G') _cur.g += param;
	if (c == 'T') _cur.t += param;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &k);
	scanf("%s", str);
	int rst = -1;
	Data cur{ 0, 0, 0, 0 };

	for (int i = 0; str[i]; i++) {
		update(cur, str[i], 1);
		if (i >= k) update(cur, str[i - k], -1);
		rst=max(rst, ++htab[cur]);
	}
	printf("%d\n", rst);

	return 0;
}