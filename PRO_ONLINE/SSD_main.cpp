#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define WRITE  100
#define MODIFY 200
#define DELETE 300
#define READ   400

#define POOL_SIZE    100000
#define MAX_FILE_ID   10000

#define MAX_BLOCK       256
#define MAX_PAGE        256

#define MAX_FILE_SIZE   512

extern void init(int blocks, int pages);
extern void writeFile(int fid, int len, int arr[MAX_FILE_SIZE]);
extern void removeFile(int fileid);
extern void modifyFile(int fileid, int len, int arr[MAX_FILE_SIZE]);
extern int  readFile(int id, int bids[MAX_FILE_SIZE], int pids[MAX_FILE_SIZE]);

static int ssd[MAX_BLOCK][MAX_PAGE];
static int written[MAX_BLOCK][MAX_PAGE];

static int erase_cnt = 0;
static int ing_read_file = 0;

static int score;

static int poolsize = POOL_SIZE;

static int filepool[POOL_SIZE];
static int file[MAX_FILE_ID + 1][MAX_FILE_SIZE];

static int nblock, npage, maxcall;

int readPage(int blockid, int pageid)
{
	if (blockid < 0 || blockid >= nblock || pageid < 0 || pageid >= npage) {
		score = 0;
		return 0;
	}

	return ssd[blockid][pageid];
}

void writePage(int blockid, int pageid, int data)
{
	if (blockid < 0 || blockid >= nblock || pageid < 0 || pageid >= npage
		|| written[blockid][pageid] == 1 || ing_read_file > 0) {
		score = 0;
		return;
	}

	written[blockid][pageid] = 1;
	ssd[blockid][pageid] = data;
}

int removeBlock(int blockid)
{
	++erase_cnt;

	if (blockid < 0 || blockid >= nblock || erase_cnt > 16) {
		score = 0;
		return erase_cnt;
	}

	for (register int i = 0; i < npage; ++i)
		ssd[blockid][i] = written[blockid][i] = 0;

	return erase_cnt;
}

static unsigned int seed = 1;

static int pseudo_rand(void)
{
	seed = seed * 0x343fd + 0x269ec3;
	return (seed / 16) & 0x00ffffff;
}

static void makeFilePool(int poolopt, int mod)
{
	if (poolopt == 0)
		return;

	poolsize = poolopt == 100 ? 500 : POOL_SIZE;

	if (mod > 0) {
		for (register int i = 0; i < poolsize; ++i)
			filepool[i] = pseudo_rand() % mod;
	}
	else {
		for (register int i = 0; i < poolsize; ++i)
			filepool[i] = pseudo_rand();
	}
}

static void makeFileData(int *data, int size, int offset)
{
	for (register int i = 0; i < size; ++i)
		data[i] = filepool[offset + i];
}

static void run()
{
	for (int i = 0; i < nblock; ++i)
		for (int j = 0; j < npage; ++j)
			ssd[i][j] = written[i][j] = 0;

	int poolopt, mod;

	if (scanf("%d %d %d %d %d %d", &seed, &nblock, &npage, &maxcall, &poolopt, &mod) != 6) {
		score = 0;
		return;
	}

	init(nblock, npage);

	makeFilePool(poolopt, mod);

	int cmd, id, size, offset;
	int usize;

	int data[MAX_FILE_SIZE] = { 0, };
	int blockids[MAX_FILE_SIZE] = { 0, };
	int pageids[MAX_FILE_SIZE] = { 0, };

	for (int call = 0; call < maxcall; ++call) {
		erase_cnt = 0;

		scanf("%d %d", &cmd, &id);
		switch (cmd) {
		case WRITE:
			scanf("%d %d", &size, &offset);
			makeFileData(file[id], size, offset);
			for (int idx = 0; idx < size; ++idx)
				data[idx] = file[id][idx];
			writeFile(id, size, data);
			break;
		case MODIFY:
			scanf("%d %d", &size, &offset);
			makeFileData(file[id], size, offset);
			for (int idx = 0; idx < size; ++idx)
				data[idx] = file[id][idx];
			modifyFile(id, size, data);
			break;
		case DELETE:
			removeFile(id);
			break;
		case READ:
			for (register int i = 0; i < npage * 2; i++)
				blockids[i] = pageids[i] = 0;

			ing_read_file = 1;
			usize = readFile(id, blockids, pageids);
			ing_read_file = 0;

			scanf("%d", &size);

			if (size != usize) {
				score = 0;
			}
			else {
				for (int i = 0; i < size; ++i)
					if (blockids[i] < 0 || blockids[i] >= nblock
						|| pageids[i] < 0 || pageids[i] >= npage
						|| file[id][i] != ssd[blockids[i]][pageids[i]]) {
						score = 0;
						break;
					}
			}
			break;
		}
	}
}

int main()
{
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; ++tc) {
		score = MARK;
		run();
		printf("#%d %d\n", tc, score);
	}

	return 0;
}