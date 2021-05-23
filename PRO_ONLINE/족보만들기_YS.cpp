#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_NAME 12
#define MAX_CRT_NODE 20000

int strcmp(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}

/// s가 t의 접두문자열이면 1을 그렇지 않다면 0을 반환
int prefix(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s == 0;
}

/// 문자열 dest에 문자열 src를 복사
void mystrcpy(char*dest, const char*src) {
	while ((*dest++ = *src++));
}

void init_user() {

}

void Add_child(char name[]) {

}

/// name[]이 "ALL"인 경우에는 현재 멤버의 모든 자식을 그 후손들과 함께 제거하고 그 수를 반환한다.
/// 그렇지 않은 경우 name[]으로 시작하는 모든 자식을 찾아 그 후손들과 함께 제거하고 그 수를 반환한다.
int Delete(char name[]) {

	return 0;
}

/// name[]이 "root"인 경우에는 최상위(root)로 이동한다.
/// name[]이 "parent"인 경우에는 부모 노드로 이동한다.
/// name[]이 "first"인 경우에는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
/// 그렇지 않은 경우 name[]으로 시작하는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
void Move(char name[]) {

}

/// name[]이 "ALL"인 경우에는 현재 멤버의 자식을 포함한 모든 후손들의 수를 반환한다.
/// 그렇지 않은 경우 현재멤버의 자식을 포함한 모든 후손들 중에 name[]으로 시작하는 후손들의 수를 반환한다.
int Count(char name[]) {

	return 0;
}
