/// ===== user.cpp  =====
#ifndef NULL
#define NULL 0
#endif 

typedef unsigned int UI;
const int ROW = 10005;
const int COL = 105;
const int LM = 1000003;
const int SIZE = 1 << 16; /// 65536
int N, bCnt;
int mat[ROW][COL];
struct Node {
	int row, col;
	Node*next;
	Node* alloc(int nr, int nc, Node*nn) {
		row = nr, col = nc, next = nn;
		return this;
	}
}buf[LM], *htab[SIZE];

void initUser(int dataN) {
	// N�ʱ�ȭ, hash table �ʱ�ȭ ���
	N = dataN;
	bCnt = 0;
	for (int i = 0; i < SIZE; ++i) htab[i] = NULL;
}

//UI getHash(int*arr) {
//  UI h = 5381;
//  for (int i = 0; i < 8; ++i) {
//      h = h * 33 + (arr[i] & 255);
//  }
//  return h;
//}

UI getHash(int*arr) {
	// ���� -128���� ���� �� �־, �������� 8��Ʈ �Űܼ� �ڿ� ���̸�. �ΰ� �ٿ��� �ϳ��� ��    // ��. 2�� ���� -128�� �տ��� 1�� �̳� ����. ���⼭ ��ȿ�� ����(255)�� ���� �����ϰ� ��  // ��ȭ ��Ű�� 0~127�� ��ġ�� ����
	return (((arr[0] & 255) << 8) + (arr[1] & 255)) % SIZE;
}

void registerData(int dataID, int dataLen, int dataArr[100]) {
	/// ID�� ���� backup, �ؽ��ڵ� �����Ͽ�  hash table�� ����
	for (int i = 0; i < dataLen; ++i) {
		mat[dataID][i] = dataArr[i];
	}
	for (int i = 0; i <= dataLen - 8; ++i) {
		int hidx = getHash(dataArr + i);
		htab[hidx] = buf[bCnt++].alloc(dataID, i, htab[hidx]);
	}
}

int check(int*arr, int*args) {
	for (int i = 0; i < 8; ++i) {
		if (arr[i] != args[i]) return 0;
	}
	return 1;
}

int findID(int args[8]) {
	int id = 0;
	/// args�� �ش��ϴ� id���Ͽ� ��ȯ
	int hidx = getHash(args) % SIZE;
	Node*p = htab[hidx];
	for (; p; p = p->next) {
		if (check(&mat[p->row][p->col], args)) return p->row;
	}
	return id;
}