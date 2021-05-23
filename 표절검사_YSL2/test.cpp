#include <stdio.h>

struct Node
{

	char ID[13]; //

	bool isLogin; //char size¿Í µ¿ÀÏ

    bool isReg; //°¡ÀÔ or Å»Åð ¿©ºÎ

	Node *next; //8Byte

}; //24Byte

void strcpy(char*dest, const char*src) {
	while ((*dest++ = *src++));
	return;
}

char str1[20];

int main() {

	//char str2[10] = "hello";

	//strcpy(str1, str2);

	//printf("str1 : %s\n", str1);
	//printf("str2 : %s\n", str2);

	struct Node temp1;
	printf("size of Member : %d\n", sizeof(temp1));

	return 0;
}


