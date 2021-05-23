// === main.cpp  ===

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

enum {
	Add = 1,
	Del = 2,
	Mov = 3,
	Cnt = 4
};

extern void init_user();
extern void Add_child(char name[]);
extern int Delete(char name[]);
extern void Move(char name[]);
extern int Count(char name[]);

int main()
{
	freopen("input.txt", "r", stdin);
	int T, N, order;
	char name[15];
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		init_user();
		while (N--) {
			if (N == 8) {
				int a = 1;
			}
			scanf("%d", &order);
			switch (order) {
			case Add:
				scanf("%s", name);
				Add_child(name);
				break;
			case Del:
				scanf("%s", name);
				printf("%d\n", Delete(name));
				break;
			case Mov:
				scanf("%s", name);
				Move(name);
				break;
			case Cnt:
				scanf("%s", name);
				printf("%d\n", Count(name));
			}
		}
	}
	return 0;
}