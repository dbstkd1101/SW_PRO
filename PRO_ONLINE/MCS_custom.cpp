/*
* 부분 문자열 길이가 고정이므로 a,c,g 세개의 빈도수가 같으면 t는 당연히 같으므로
* a,c,g 의 개수로만 처리해도 된다.
*/
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

struct Data {
	int a, c, g;
	//bool operator==(const Data&r) const {
	//	return a == r.a && c == r.c && g == r.g;
	//}
};

struct MyHash {
	size_t operator()(const Data& d) const {
		return d.a * 1001 * 1001 + d.c * 1001 + d.g;
	}
};
struct MyEqual {
	bool operator()(const Data& l, const Data& r) const {
		return l.a == r.a && l.c == r.c && l.g == r.g;
	}
};

unordered_map<Data, int, MyHash, MyEqual> htab; // a,c,g ºóµµ¼ö / cnt
// unordered_map<Data, int, MyHash> htab; // KeyEqual : operator overloading
int K;
Data cur;

void update(char c, int p) {
	if (c == 'A') cur.a += p;
	if (c == 'C') cur.c += p;
	if (c == 'G') cur.g += p;
}

int main() {
	freopen("input.txt", "r", stdin);
	string str;
	int ret = 0;
	cin >> K >> str;
	for (int i = 0; i < str.size(); i++) {
		update(str[i], 1);
		if (i >= K) update(str[i - K], -1);
		if (i + 1 >= K) ret = max(ret, ++htab[cur]);
	}
	cout << ret << endl;
	return 0;
}