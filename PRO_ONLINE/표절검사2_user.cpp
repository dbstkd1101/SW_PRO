#ifndef NULL
#define NULL 0
#endif 

const int SIZE = 1 << 21;

#define MAX_CNT_SOUND 10000
#define SOUND_MAX_LENGTH 200
#define NEW_SOUND_LENGTH 8
typedef unsigned long long ULL;

int sound[MAX_CNT_SOUND+1][SOUND_MAX_LENGTH +1];

struct node {
	int pos;
	int soundNum;
	node * next;
	node* alloc(int _pos, int _soundNum, node* _next) {
		pos = _pos;
		soundNum = _soundNum;
		next = _next;
		return this;
	}
}* bucket[SIZE], buf[MAX_CNT_SOUND*SOUND_MAX_LENGTH];

int bufCnt = 0;

int bit7(int sound) {
	int rst = (sound >> 8);
	int andA = ((1 << 7) - 1);
	int result = rst & andA;
	return  result;
}

// hash가 아니라 key?
int getHash(int sound1, int sound2, int sound3) {
	return ((bit7(sound1) << 14) + (bit7(sound2) << 7) + bit7(sound3)) % SIZE;
}

void addNode(int soundID, int * soundArr, int pos) {
	int hash = getHash(soundArr[pos+0], soundArr[pos+1], soundArr[pos+2]);
	bucket[hash]=buf[bufCnt].alloc(pos, soundID, bucket[hash]);
	bufCnt++;
}

void initUser(int soundNum) {
	bufCnt = 0;
	for (int i = 0; i <= SIZE; i++) {
		bucket[i] = NULL;
	}
}

void registerSound(int soundID, int soundLen, int soundArr[200]) {
	for (int i = 0; i < soundLen; i++) {
		sound[soundID][i] = soundArr[i];
		if (i <= soundLen - NEW_SOUND_LENGTH) {
			addNode(soundID, soundArr, i);
		}
	}
}

/*
원본에 -128 ~ +127을 하면, 뒤 8bit는 난장판으로 바뀌지만, 앞에 7bit는 하나 올리거나/그대로거나/내리거나 일 뿐
따라서, 반대로 -127 ~ +128하여 앞에 7bit를 하나 내리거나/올려서
(변형되어서 (뒤8자리만 변동있을 때)) 앞의 7bit가 1101100라면, +된 만큼 -이면 앞의 7bit는 그대로.
+된 만큼 더 +시키면 1101101로 되겠지.
*/
int limit[3][8] = {
	{-127, -127, -127, -127, +128, +128, +128, +128},
	{-127, -127, +128, +128, -127, -127, +128, +128},
	{-127, +128, -127, +128, -127, +128, -127, +128}
};

int chk(int* origin, int destSoundNum, int destPos) {
	int rst = 1;
	for (int i = 0; i < NEW_SOUND_LENGTH; i++) {
		if (origin[i] - 127 > sound[destSoundNum][destPos + i] || origin[i] + 128 < sound[destSoundNum][destPos + i]) {
			return rst = 0;
		}
	}
	return rst;
}

int plagiarismCheck(int newData[8])
{
	int id = 0;

	for(int i=0;i<8;i++){
		int hash=getHash(newData[0]+limit[0][i], newData[1] + limit[1][i], newData[2] + limit[2][i]);

		for (node * p = bucket[hash]; p; p = p->next) {
			if (chk(newData, p->soundNum, p->pos)) {
				return id=p->soundNum;
			}
		}
	}

	return id;
}

