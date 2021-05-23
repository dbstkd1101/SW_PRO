#include <stdio.h>

#include <stdlib.h> // rand() 함수 포함 라이브러리



int main()

{
	 FILE *fp = fopen("input.txt", "w");
	int random = 0; // 정수형 변수 선언
	int a = 500000;
	fprintf(fp, "%d\n", a);
	for (int i = 0; i < 500000; i++) { // 10번 반복

		random = rand() % 1000000000; // 난수 생성
		fprintf(fp, "%d\n", random);
	}
	fclose(fp);
}