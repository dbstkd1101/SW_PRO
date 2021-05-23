#include "string.h"
#include <stdio.h>

int main() {

	char str1[10];
	char str2[10];

	printf("input str1 :");
	scanf("%s", str1);

	printf("input str2 :");
	
	scanf("%s", str2);

	printf("rst of cmp : %d\n", strcmp(str1, str2));

	printf("str2->str1 copy !!\n");
	strcpy(str1, str2);

	printf("rst of copy :%s\n", str1);

	return 0;
}





