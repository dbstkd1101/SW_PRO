#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif 

#include<stdio.h > 

#define DATA_MAX_LENGTH (100) 
#define EXTRACT_DATA_LENGTH (8) 

static int randomSeed, dataNum, lengthLimit, queryCount;
static int data[10005][DATA_MAX_LENGTH];
static int dataLength[10005];

extern void initUser(int dataN);
extern void registerData(int dataID, int dataLen, int dataArr[DATA_MAX_LENGTH]);
extern int  findID(int args[EXTRACT_DATA_LENGTH]);


static int getRand(void) {
	randomSeed = randomSeed * 0x343FD + 0x296EC3;
	return (randomSeed >> 16) & 0x7FFF;
}

static void makeData() {
	int args[DATA_MAX_LENGTH];
	int data_len;
	for (int id = 1; id <= dataNum; id++) {
		data_len = dataLength[id] = getRand() % lengthLimit + 1;

		if (dataLength[id] < EXTRACT_DATA_LENGTH)
			data_len = dataLength[id] = EXTRACT_DATA_LENGTH;

		for (int i = 0; i < dataLength[id]; i++) {
			args[i] = data[id][i] = (getRand() & 255) - 128;
		}

		registerData(id, data_len, args);
	}
}

static bool extractData() {
	int args[EXTRACT_DATA_LENGTH];

	//int dataID = getRand() % dataNum + 1;
	int dataID = 1;
	int stIdx = 0;
	//int stIdx = getRand() % dataLength[dataID];

	if (stIdx + EXTRACT_DATA_LENGTH >= dataLength[dataID]) {
		stIdx = dataLength[dataID] - EXTRACT_DATA_LENGTH;
	}

	for (int i = 0; i < EXTRACT_DATA_LENGTH; i++) {
		args[i] = data[dataID][i + stIdx];
	}

	int return_val = findID(args);

	return return_val == dataID;
}

int main() {
	setbuf(stdout, NULL);
	int testCase, totalScore = 0;

	freopen("input.txt", "r", stdin);

	scanf("%d", &testCase);

	for (int tc = 1; tc <= testCase; tc++) {
		scanf("%d%d%d%d", &randomSeed, &dataNum, &lengthLimit, &queryCount);

		int correctCount = 0;

		initUser(dataNum);
		makeData();

		for (int query = 0; query < queryCount; query++) {
			if (extractData())
				correctCount++;
		}
		if (correctCount == queryCount) {
			printf("#%d 100\n", tc);
			totalScore += 100;
		}
		else {
			printf("#%d 0\n", tc);
		}
	}
	printf("Total Score : %d\n", totalScore / testCase);

	return 0;
}