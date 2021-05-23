/// === user.cpp ===
#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_NAME 12
#define MAX_data_CREATE 20000
int strcmp(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}

int strncmp(const char*s, const char*t, int len) {
	if (len == 0) return 0;
	for (int i = 0; i < len && (*s) && (*s == *t) ; ++s, ++t, ++i) {
	}
	return *s - *t;
}

/// s가 t의 접두문자열이면 1을 그렇지 않다면 0을 반환
// s가 작은거
int prefix(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s == 0;
}

/// 문자열 dest에 문자열 src를 복사
void mystrcpy(char*dest, const char*src) {
	while ((*dest++ = *src++));
}

int strlen(char * str){
	int cnt = 0;
	int i= 0;
	if (str == NULL) return 0;
	else {
		while (str[i++]) cnt++;
	}
	return cnt;
}

struct data {
	char name[MAX_LEN_NAME+1];
	data * parent, * child, * prev, * next;
	
	data * alloc(char _name[MAX_LEN_NAME + 1], data * _parent, data * _next) {
		mystrcpy(name, _name), parent = _parent, next = _next;
		// 양방향이면서 && dummy node가 없으므로 prev, child 없음
		child = prev = NULL;
		// dummy node가 없으므로 prev -> this 연결 생략
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		if(prev) prev->next = next;
		else {
			// 내가 head이니까 내 부모->child 대상을 next(형제)로 변경
			parent->child = next;
		}
		if(next) next->prev = prev;
	}
} *root, *cur, buf[MAX_data_CREATE+10];

int bCnt;

void init_user() {
	bCnt = 0;
	// tmp 사실 의미 없음
	char tmp[MAX_LEN_NAME + 1] = "root";
	// 빈 노드 하나 그냥 생성, &buf[0]= buf 를 parent로 넣는 것은 자기 자신을 넣음.
	root = cur = buf[bCnt++].alloc(tmp, &buf[0], NULL);
}

void Add_child(char name[]) {
	for (data * p = cur->child; p; p = p->next) {
		if (strcmp(name, p->name) == 0) return;
	}
	// parent의 child를 신규 추가할 node(head에 위치할 예정)로 연결
	cur->child = buf[bCnt++].alloc(name, cur, cur->child);
}


/// name[]이 "root"인 경우에는 최상위(root)로 이동한다.
/// name[]이 "parent"인 경우에는 부모 노드로 이동한다.
/// name[]이 "first"인 경우에는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
/// 그렇지 않은 경우 name[]으로 시작하는 사전순으로 가장 빠른 이름을 가진 자식 노드로 이동한다.
void Move(char name[]) {
	if (!strcmp(name, "root")) cur = root;
	if (!strcmp(name, "parent")) cur = cur->parent;
	if (!strcmp(name, "first")) {
		// 밑에 else에서 한 번에 처리하기 위하여
		name[0] = NULL;
	}
	else {
		data* q = NULL;
		int len = strlen(name);
		for (data* p = cur->child; p; p = p->next) {
			if (strncmp(p->name, name, len) != 0) continue;
			if (q == NULL || strcmp(p->name, q->name) < 0) q = p;
		}
		if (q) cur = q;
	}
}

int count(data * p, char name[]) {
	
	if (p == NULL) return 0;
	int len = strlen(name);
	int cnt = count(p->child, name) + count(p->next, name);
	if (strncmp(p->name, name, len) == 0) cnt++;
	return cnt;
}

/// name[]이 "ALL"인 경우에는 현재 멤버의 자식을 포함한 모든 후손들의 수를 반환한다.
/// 그렇지 않은 경우 현재멤버의 자식을 포함한 모든 후손들 중에 name[]으로 시작하는 후손들의 수를 반환한다.
int Count(char name[]) {
	if (!strcmp(name, "ALL")) name = NULL;
	return count(cur->child, name);
}

/// name[]이 "ALL"인 경우에는 현재 멤버의 모든 자식을 그 후손들과 함께 제거하고 그 수를 반환한다.
/// 그렇지 않은 경우 name[]으로 시작하는 모든 자식을 찾아 그 후손들과 함께 제거하고 그 수를 반환한다.
int Delete(char name[]) {
	if (strcmp(name, "ALL") == 0) name[0] = NULL;
	int cnt = 0, len = strlen(name);
	char tmp[MAX_LEN_NAME + 1] = "";
	for (data* p = cur->child; p; p = p->next) {
		if (strncmp(p->name, name, len) == 0) {
			cnt += count(p->child, tmp) + 1;
			p->pop();
		}
	}

	return cnt;
}