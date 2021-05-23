// 512 MB
#include <stdio.h>

#define MAX_MEMBER_SIZE 500000
#define MAX_BUCKET_SIZE 64000000
#define UI unsigned int

/// 문자열 dest에 문자열 src를 복사
void strcpy(char*dest, const char*src) {
	while ((*dest++ = *src++));
	return;
}

int strcmp(char*s, char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}


// 16 + 4 + 4 + 4(32 bit일 때?) = 28Bite
typedef struct member {
	char ID[13];
	int sign;
	int login;
	member * next;
}MEMBER;

MEMBER buf[MAX_MEMBER_SIZE + 1];
MEMBER * bucket[MAX_BUCKET_SIZE];
int bufCnt;
int memberCnt;
int loginCnt;

UI getHashCode(char * ID) {
	UI sum = 5831;
	for (int i = 0; ID[i] != 0; i++) {
		int temp;
		if ('a' <= ID[i] && ID[i] <= 'z') {
			temp = ID[i] - 'a' + 10;
		}
		if ('0' <= ID[i] && ID[i] <= '9') {
			temp = ID[i] - '0';
		}
		// temp가 가질 수 있는 표현 최대 6bit
		sum = (sum << 6) + temp;
	}
	return sum % MAX_BUCKET_SIZE;
}

MEMBER * mAlloc(char * ID, UI hashCode) {
	strcpy(buf[bufCnt].ID, ID);
	buf[bufCnt].next = bucket[hashCode];
	return &buf[bufCnt++];
}

void addNode(int hashCode, char * ID, int sign, int login) {
	MEMBER * temp = mAlloc(ID, hashCode);
	temp->sign = sign;
	temp->login = login;
	bucket[hashCode] = temp;
}


void init() {
	bufCnt = 0;
	memberCnt = 0;
	loginCnt = 0;
}

MEMBER * find(char * ID) {
	UI hashCode = getHashCode(ID);
	MEMBER * p;
	for (p = bucket[hashCode]; p != NULL; p = p->next) {
		if (strcmp(ID, p->ID) == 0)
		{
			return p;
		}
	}
	return p;
}

int validate(char* ID) {

	MEMBER *temp = find(ID);
	int result = 0;

	if (temp!=NULL && temp->sign) {
		result = 1;
	}
	else {
		result = 0;
	}

	return result;
}

int activate(char* ID) {

	MEMBER *temp = find(ID);
	int result = 0;

	if (temp != NULL && temp->login) {
		result = 1;
	}
	else {
		result = 0;
	}

	return result;
}

int signup(char*ID) {

	if (!validate(ID)) {
		UI hashCode = getHashCode(ID);

		addNode(hashCode, ID, 1, 0);
		memberCnt++;
	}
	int result = memberCnt;

	return result;
}

int close(char*ID) {

	if (validate(ID)) {
		MEMBER * temp = find(ID);
		temp->sign = 0;
		temp->login = 0;
		memberCnt--;
	}
	int result = memberCnt;
	return result;
}

int login(char*ID) {

	if (validate(ID)) {
		if (!activate(ID)) {
			MEMBER * temp = find(ID);
			temp->login = 1;
			loginCnt++;
		}
	}
	
	int result = loginCnt;

	return result;
}

int logout(char*ID) {
	
	if (activate(ID)) {
		MEMBER * temp = find(ID);
		temp->login = 0;
		loginCnt--;
	}
	int result = loginCnt;

	return result;
}

int N;

int main() {

	//freopen("input.txt", "r", stdin);

	scanf("%d", &N);

	int command;

	for (int i = 0; i < N; i++) {
		char str[13];
		scanf("%d %s", &command, str);
		switch (command) {
		case 1:
			printf("%d\n", validate(str));
			break;
		case 2:
			printf("%d\n", activate(str));
			break;
		case 3:
			printf("%d\n", signup(str));
			break;
		case 4:
			printf("%d\n", close(str));
			break;
		case 5:
			printf("%d\n", login(str));
			break;
		case 6:
			printf("%d\n", logout(str));
			break;
		}
	}

	return 0;
}