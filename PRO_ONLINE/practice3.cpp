#include <stdio.h>
#include <list>
#include <string.h>

using namespace std;

list<char> li;

int main() {
	auto it = li.begin();
	auto it2 = li.end();

	li.insert(it, 'a');
	li.insert(it, 'b');
	li.insert(it, 'c');

	it=prev(it, 1);
	li.erase(it);

	int a = 1;

	printf("it==it2 : %d", it == it2);


	return 0;
}