#define MAX_N			5
#define MAX_NAME_LEN	7
#define MAX_TYPE_LEN	3
#define MAX_TAG_LEN		4
#define MAX_TYPE_CNT	5
#define MAX_ADD			50000
#define MAX_SECTION_CNT	100
void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

extern struct book;

struct bNode {
	char name[MAX_NAME_LEN];
	bNode* prev, * next;
	bNode* alloc(char _name[], bNode* _prev, bNode* _next) {
		mstrcpy(name, _name);
		prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
};

struct book {
	char name[MAX_NAME_LEN];
	int section;
	bNode* typeAddr[MAX_TYPE_CNT];
	book* next;
	book* alloc(char* _name, int _section, int typeNum, bNode* _typeAddr[], book* _next) {
		mstrcpy(name, _name);
		section = _section;
		for (int i = 0; i < typeNum; i++) {
			typeAddr[i] = _typeAddr[i];
		}
		next = _next;
		return this;
	}
}bBuf[MAX_ADD+100], bBucket[MAX_ADD];

int bBufCnt;

struct type {
	char tName[MAX_TYPE_LEN+1];
	type* next;
	type* alloc(char _tName[], type* _next) {
		mstrcpy(tName, _tName);
		next = _next;
		return this;
	}
}tBuf[MAX_SECTION_CNT*500+100], *section[MAX_SECTION_CNT+1];

int tBufCnt;

void init(int M)
{
	bBufCnt = tBufCnt = 0;


}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{

}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	return 0;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{

}

void deleteName(char mName[MAX_NAME_LEN])
{

}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
	return 0;
}