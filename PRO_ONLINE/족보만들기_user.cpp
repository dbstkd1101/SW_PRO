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

/// s�� t�� ���ι��ڿ��̸� 1�� �׷��� �ʴٸ� 0�� ��ȯ
// s�� ������
int prefix(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s == 0;
}

/// ���ڿ� dest�� ���ڿ� src�� ����
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
		// ������̸鼭 && dummy node�� �����Ƿ� prev, child ����
		child = prev = NULL;
		// dummy node�� �����Ƿ� prev -> this ���� ����
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		if(prev) prev->next = next;
		else {
			// ���� head�̴ϱ� �� �θ�->child ����� next(����)�� ����
			parent->child = next;
		}
		if(next) next->prev = prev;
	}
} *root, *cur, buf[MAX_data_CREATE+10];

int bCnt;

void init_user() {
	bCnt = 0;
	// tmp ��� �ǹ� ����
	char tmp[MAX_LEN_NAME + 1] = "root";
	// �� ��� �ϳ� �׳� ����, &buf[0]= buf �� parent�� �ִ� ���� �ڱ� �ڽ��� ����.
	root = cur = buf[bCnt++].alloc(tmp, &buf[0], NULL);
}

void Add_child(char name[]) {
	for (data * p = cur->child; p; p = p->next) {
		if (strcmp(name, p->name) == 0) return;
	}
	// parent�� child�� �ű� �߰��� node(head�� ��ġ�� ����)�� ����
	cur->child = buf[bCnt++].alloc(name, cur, cur->child);
}


/// name[]�� "root"�� ��쿡�� �ֻ���(root)�� �̵��Ѵ�.
/// name[]�� "parent"�� ��쿡�� �θ� ���� �̵��Ѵ�.
/// name[]�� "first"�� ��쿡�� ���������� ���� ���� �̸��� ���� �ڽ� ���� �̵��Ѵ�.
/// �׷��� ���� ��� name[]���� �����ϴ� ���������� ���� ���� �̸��� ���� �ڽ� ���� �̵��Ѵ�.
void Move(char name[]) {
	if (!strcmp(name, "root")) cur = root;
	if (!strcmp(name, "parent")) cur = cur->parent;
	if (!strcmp(name, "first")) {
		// �ؿ� else���� �� ���� ó���ϱ� ���Ͽ�
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

/// name[]�� "ALL"�� ��쿡�� ���� ����� �ڽ��� ������ ��� �ļյ��� ���� ��ȯ�Ѵ�.
/// �׷��� ���� ��� �������� �ڽ��� ������ ��� �ļյ� �߿� name[]���� �����ϴ� �ļյ��� ���� ��ȯ�Ѵ�.
int Count(char name[]) {
	if (!strcmp(name, "ALL")) name = NULL;
	return count(cur->child, name);
}

/// name[]�� "ALL"�� ��쿡�� ���� ����� ��� �ڽ��� �� �ļյ�� �Բ� �����ϰ� �� ���� ��ȯ�Ѵ�.
/// �׷��� ���� ��� name[]���� �����ϴ� ��� �ڽ��� ã�� �� �ļյ�� �Բ� �����ϰ� �� ���� ��ȯ�Ѵ�.
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