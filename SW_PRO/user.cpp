/// ===== user.cpp  =====
#ifndef NULL
#define NULL 0
#endif 

#define MAX_EXTRACT_NUM 8
#define MAX_DATA_NUM (10000*100)
#define MAX_BUCKET_NUM 15000000

typedef unsigned int UI;

typedef struct node {
	int startIDX;
	int args[MAX_EXTRACT_NUM];
	int ID;
	node * next;
}NODE;

NODE buf[MAX_DATA_NUM];
int bufN;

NODE * bucket[MAX_BUCKET_NUM];

int getHashCode(int * arr) {
	UI sum = 5831;
	for (int i = 0; i<8; i++) {
		sum = (sum << 8) + arr[i];
	}
	return (sum%MAX_BUCKET_NUM);
}

NODE * mAlloc(int startIDX, int * args, int ID, int hash_code) {
	buf[bufN].startIDX = startIDX;
	for (int i = 0; i < MAX_EXTRACT_NUM; i++) {
		buf[bufN].args[i] = args[i];
	}
	buf[bufN].ID = ID;
	buf[bufN].next = bucket[hash_code];
	return &buf[bufN++];
}

void addNode(int startIDX, int * args, int ID, int hash_code) {
	bucket[hash_code] = mAlloc(startIDX, args, ID, hash_code);
}


void initUser(int dataN) {
	bufN = 0;
	for (int i = 0; i < MAX_BUCKET_NUM; i++) {
		bucket[i] = NULL;
	}
}

void registerData(int dataID, int dataLen, int dataArr[100]) {
	for (int i = 0; i + MAX_EXTRACT_NUM <= dataLen; i++) {
		int hashCode = getHashCode(&dataArr[i]);
		addNode(i, &dataArr[i], dataID, hashCode);
	}
}

int findID(int args[8]) {
	int id = 0;	int hash_code = getHashCode(args);

	int rst = -1;

	for (NODE * pos = bucket[hash_code]; pos != NULL; pos = pos->next) {
		if ((pos->args[0]) == args[0])
		{
			for (int i = 1; i < MAX_EXTRACT_NUM; i++) 
			{
				if ((pos->args[i]) != args[i]) 
				{
					rst = 0;
					break;
				}
			}
			// 모든 문자열이 같으면
			if (rst == -1) 
			{
				id = pos->ID;
				return id;
			}
			else 
			{
				if (pos->next != NULL) {
					continue;
				}
				else {
					break;
				}
			}
		}
		else {
			// 다음꺼 있으면
			if (pos->next != NULL) {
				continue;
			}
			// 없으면 exit
			else {
				break;
			}
		}
	}
	return id;
}