#include <stdio.h>

struct Node

{

	char ID[13]; //

	bool isLogin; //char size와 동일

	bool isReg; //가입 or 탈퇴 여부

	Node *next; //8Byte

}; //24Byte

Node buf[550000]; //12.58 MB

int bufN;

Node *bucket[60459978]; //(512MB - 12.58 ) / 포인터8Byte = 6500만.

Node *findID(char *ID);

int validate(char* ID);

int activate(char* ID);

int signup(char*ID);

int close(char*ID);

int login(char*ID);

int logout(char*ID);

int loginCount, regCount;

void strcpy(char *a, char *b)

{

	int n;

	for (n = 0; b[n] != '\0'; n++);



	for (int x = 0; x < n; x++)

	{

		a[x] = b[x];

	}

}

Node *myAlloc(char *id, bool isLogin, bool isReg, Node *next)

{

	strcpy(buf[bufN].ID, id);

	buf[bufN].isLogin = isLogin;

	buf[bufN].isReg = isReg;

	buf[bufN].next = next;

	return &buf[bufN++];

}

int hash(char *key)

{

	unsigned int sum = 5381;

	for (int i = 0; key[i] != '\0'; i++)

	{

		sum = sum * 33 + key[i];

	}

	return sum % 60459978;

}

void addNode(int from, char *ID, bool isLogin, bool isReg)

{

	bucket[from] = myAlloc(ID, isLogin, isReg, bucket[from]);

}

int strcmp(char *a, char *b)

{

	int n1;

	int n2;

	for (n1 = 0; a[n1] != '\0'; n1++);

	for (n2 = 0; a[n2] != '\0'; n2++);

	if (n1 != n2) return -1;

	for (int i = 0; i < n1; i++)

	{

		if (a[i] != b[i]) return -1;

	}

	return 0;

}

Node *findID(char *ID)

{

	int code = hash(ID);

	Node *p = NULL;

	for (p = bucket[code]; p != NULL; p = p->next)

	{

		if (strcmp(ID, p->ID) == 0)

		{

			return p;

		}

	}

	return p;

}

int signup(char*ID)

{

	Node *p = findID(ID);

	int code = hash(ID);

	if (p == NULL)

	{

		addNode(code, ID, false, true); //로그인 OFF, 가입 ON

		regCount++;

	}

	else if (p->isReg == 0)

	{

		p->isReg = 1;

		regCount++;

	}

	return regCount;

}

int validate(char* ID)

{

	Node *p = findID(ID);



	if (p != NULL && p->isReg == 1) return 1;

	return 0;

}

int activate(char* ID)

{

	Node *p = findID(ID);

	if (p != NULL && p->isLogin == 1) return 1;

	return 0;

}

int login(char*ID)

{

	Node *p = findID(ID);

	if (p != NULL && p->isLogin == 0 && p->isReg == 1)

	{

		p->isLogin = 1;

		loginCount++;

	}

	return loginCount;

}

int logout(char*ID)

{

	Node *p = findID(ID);

	if (p != NULL && p->isLogin == 1 && p->isReg == 1)

	{

		p->isLogin = 0;

		loginCount--;

	}

	return loginCount;

}

int close(char*ID)

{

	Node *p = findID(ID);

	if (p != NULL && p->isLogin == 1 && p->isReg == 1)

	{

		p->isLogin = 0;

		loginCount--;

		p->isReg = 0;

		regCount--;

	}

	else if (p != NULL && p->isLogin == 0 && p->isReg == 1)

	{

		p->isReg = 0;

		regCount--;

	}

	return regCount;

}

int main()

{

	//freopen("Text.txt", "r", stdin);

	int n;



	char name[13];

	int command;

	int ret;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)

	{

		scanf("%d %s", &command, name);

		if (command == 1)

		{

			ret = validate(name);

		}

		else if (command == 2)

		{

			ret = activate(name);

		}

		else if (command == 3)

		{

			ret = signup(name);

		}

		else if (command == 4)

		{

			ret = close(name);

		}

		else if (command == 5)

		{

			ret = login(name);

		}

		else if (command == 6)

		{

			ret = logout(name);

		}

		printf("%d\n", ret);

	}

}