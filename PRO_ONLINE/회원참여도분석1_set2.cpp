#include<stdio.h>
#include<set>
using namespace std;
using pii = pair<int, int>;	// operator <, <=, >, >=, ==, !=

int n, m, total;

// 1.operator overloading
//struct Data {
//	int id, freq;
//	bool operator<(const Data&r) const {
//		return freq != r.freq ? freq < r.freq : id < r.id;
//	}
//};
//set<Data> s;

// 2. function object
//struct Data { int id, freq; };
//
//struct Compare {
//	bool operator()(const Data&a, const Data&b) const {
//		return a.freq != b.freq ? a.freq < b.freq : a.id < b.id;
//	}
//}comp;
//set<Data, Compare> s;
//set<Data, decltype(comp)> s(comp);

// 3. lambda
struct Data { int id, freq; };

auto compare = [](const Data& a, const Data& b) {
	return a.freq != b.freq ? a.freq < b.freq : a.id < b.id;
};
set<Data, decltype(compare)> s(compare);


int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	int cmd, id, freq;
	while (m--) {
		scanf("%d", &cmd);
		if (cmd == 0) {
			scanf("%d%d", &id, &freq);
			s.insert({ id, freq });
			total += freq;
		}
		if (cmd == 1) {
			if (s.size()) {
				printf("%d\n", s.begin()->id);
				total -= s.begin()->freq;
				s.erase(s.begin());
			}
		}
		if (cmd == 2) {
			if (s.size()) {
				printf("%d\n", s.rbegin()->id);
				total -= s.rbegin()->freq;
				s.erase(--s.end());
			}
		}
		if (cmd == 3) {
			if (s.size() <= 2) printf("0\n");
			else printf("%d\n", total - s.begin()->freq - s.rbegin()->freq);
		}
	}
	return 0;
}