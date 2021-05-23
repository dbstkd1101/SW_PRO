#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_NAME 12
#define MAX_CRT_NODE 20000

int strcmp(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}

/// s�� t�� ���ι��ڿ��̸� 1�� �׷��� �ʴٸ� 0�� ��ȯ
int prefix(const char*s, const char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s == 0;
}

/// ���ڿ� dest�� ���ڿ� src�� ����
void mystrcpy(char*dest, const char*src) {
	while ((*dest++ = *src++));
}

void init_user() {

}

void Add_child(char name[]) {

}

/// name[]�� "ALL"�� ��쿡�� ���� ����� ��� �ڽ��� �� �ļյ�� �Բ� �����ϰ� �� ���� ��ȯ�Ѵ�.
/// �׷��� ���� ��� name[]���� �����ϴ� ��� �ڽ��� ã�� �� �ļյ�� �Բ� �����ϰ� �� ���� ��ȯ�Ѵ�.
int Delete(char name[]) {

	return 0;
}

/// name[]�� "root"�� ��쿡�� �ֻ���(root)�� �̵��Ѵ�.
/// name[]�� "parent"�� ��쿡�� �θ� ���� �̵��Ѵ�.
/// name[]�� "first"�� ��쿡�� ���������� ���� ���� �̸��� ���� �ڽ� ���� �̵��Ѵ�.
/// �׷��� ���� ��� name[]���� �����ϴ� ���������� ���� ���� �̸��� ���� �ڽ� ���� �̵��Ѵ�.
void Move(char name[]) {

}

/// name[]�� "ALL"�� ��쿡�� ���� ����� �ڽ��� ������ ��� �ļյ��� ���� ��ȯ�Ѵ�.
/// �׷��� ���� ��� �������� �ڽ��� ������ ��� �ļյ� �߿� name[]���� �����ϴ� �ļյ��� ���� ��ȯ�Ѵ�.
int Count(char name[]) {

	return 0;
}
