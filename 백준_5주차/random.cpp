#include <stdio.h>

#include <stdlib.h> // rand() �Լ� ���� ���̺귯��



int main()

{
	 FILE *fp = fopen("input.txt", "w");
	int random = 0; // ������ ���� ����
	int a = 500000;
	fprintf(fp, "%d\n", a);
	for (int i = 0; i < 500000; i++) { // 10�� �ݺ�

		random = rand() % 1000000000; // ���� ����
		fprintf(fp, "%d\n", random);
	}
	fclose(fp);
}