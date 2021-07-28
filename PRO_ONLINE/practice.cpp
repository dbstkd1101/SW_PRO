#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

list<int> li{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

int main() {
	
	// 鉴规氢 立辟
	for (auto it = li.begin(); it != li.end(); it++) {
		printf("%d, ", *it);
	}

	// 开规氢 立辟
	for (auto it = li.end(); it!=li.begin(); it--) {
		--it;
	} 
	auto it = li.begin();
	// return X
	advance(it, 3);
	puts("");
	printf("advaned 3 : %d\n", *it);

	// return it
	list<int>::iterator it2 = next(it, 2);
	printf("next 2 : %d\n", *it2);

	// return it
	list<int>::iterator it3 = prev(it2, 1);
	printf("prev 1 : %d\n", *it3);
	
	auto it4 = li.begin();
	(*it4)=0;
	printf("it value change : %d\n", *it4);

	return 0;
}

