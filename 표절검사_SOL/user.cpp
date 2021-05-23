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
	// N초기화, hash table 초기화 등등
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
	// 음수 -128까지 나올 수 있어서, 왼쪽으로 8비트 옮겨서 뒤에 붙이면. 두개 붙여서 하나로 다    // 룸. 2의 보수 -128은 앞에가 1이 겁나 많다. 여기서 유효한 범위(255)에 대해 추출하고 양  // 수화 시키면 0~127와 겹치지 않음
	return (((arr[0] & 255) << 8) + (arr[1] & 255)) % SIZE;
}

void registerData(int dataID, int dataLen, int dataArr[100]) {
	/// ID별 정보 backup, 해시코드 생성하여  hash table에 저장
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
	/// args에 해당하는 id구하여 반환
	int hidx = getHash(args) % SIZE;
	Node*p = htab[hidx];
	for (; p; p = p->next) {
		if (check(&mat[p->row][p->col], args)) return p->row;
	}
	return id;
}