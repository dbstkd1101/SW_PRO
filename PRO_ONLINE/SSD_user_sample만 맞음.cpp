#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef NULL
#define NULL 0
#endif

#define FILE_SIZE 512
#define BLOCK_SIZE 256
#define PAGE_SIZE 256
#define FUNC_CNT 12800
#define FILE_ID 10000

extern int readPage(int bid, int pid);
extern void writePage(int bid, int pid, int data);
extern int removeBlock(int bid);

struct fileNode;

int blkSize, pageSize;

struct blkNode {
	int fId, st, size;
	blkNode * prev, * next;
	fileNode * fileNodeP;
	blkNode * alloc(int _fId, int _st, int _size, blkNode * _prev, blkNode * _next) {
		fId = _fId, st = _st, size = _size, prev = _prev, next = _next;
		if(prev) prev->next = this;
		if(next) next->prev = this;
		return this;
	}
	blkNode* pop() {
		prev->next = next;
		if (next) next->prev = prev;
		return this;
	}
}blkBuf[FUNC_CNT * 3],* blkStk[BLOCK_SIZE];

int gSumArr[BLOCK_SIZE];

int gMaxIdx;
int emptyBlk[2];
int blkBCnt;

struct fileNode {
	int blkId, st, size;
	fileNode * prev, *next;
	blkNode * blkNodeP;
	fileNode * alloc(int _blkId, int _st, int _size, fileNode * _prev, fileNode * _next) {
		blkId = _blkId, st = _st, size = _size, prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	fileNode* pop() {
		prev->next = next;
		if (next) next->prev = prev;
		return this;
	}
}fileBuf[FUNC_CNT * 3], *fileStk[FILE_ID];
//fileBuf[0]은 empty 전용

int fileBCnt;

int findGMax() {
	int temp = 0;
	for (int i = 1; i < blkSize; i++) {
		if (gSumArr[temp] < gSumArr[i]) {
			temp = i;
		}
	}
	return temp;
}

void init(int blockSize, int pagesize) {
	blkSize = blockSize, pageSize = pagesize;
	blkBCnt = fileBCnt = 0;
	gMaxIdx = -1;

	for (int i = 0; i < blockSize; i++) {
		blkStk[i]= blkBuf[blkBCnt++].alloc(NULL, NULL, NULL, NULL, NULL);
		gSumArr[i] = 0;
	}

	//fileStk[0] dummy Node
	fileStk[0] = fileBuf[fileBCnt++].alloc(-1, NULL, NULL, NULL, NULL);
	// BlockId별 empty Node 추가
	for (int k = blockSize -1; k >= 0; k--) {
		fileBuf[fileBCnt++].alloc(k, 0, pagesize, fileStk[0], fileStk[0]->next);
	}
	
	//dummy Node
	for (int j = 1; j <= FILE_ID; j++) {
		fileStk[j]=fileBuf[fileBCnt++].alloc(-1, NULL, NULL, NULL, NULL);
	}
}

void blkNodeMoveAll(int s, int e) {
	blkNode * tmp = NULL;
	while (tmp = blkStk[s]->next->pop()) {
		writePage(e, tmp->st, tmp->fId);
		tmp->next = blkStk[e]->next;
		blkStk[e]->next = tmp;
		tmp->fileNodeP->blkId = e;
	}
}

void fileNodeMove(int s, int e) {
	fileNode * tmp = fileStk[s]->pop();
	tmp->next = fileStk[e];
	fileStk[e] = tmp;
}

void writeFile(int fId, int len, int pages[FILE_SIZE]) {
	int writedSum = 0;
	
	for(int i=0;i<16 && writedSum < len;i++){
	//while (writedSum < len) {
		if (fileStk[0]->next) {
			fileNode * popFileNode = fileStk[0]->next->pop();
			
			int remainArea = (writedSum + popFileNode->size) - len;
			int writedArea;

			// 남는 부분 넘치면 split
			if (remainArea > 0) {
				writedArea = popFileNode->size - remainArea;
				//남는거 추가
				fileBuf[fileBCnt++].alloc(popFileNode->blkId, popFileNode->st + writedArea, remainArea, fileStk[0], fileStk[0]->next);
			}
			else {
				writedArea = popFileNode->size;
			}
			// writedArea 추가
			fileNode * addedFileNode = fileBuf[fileBCnt++].alloc(popFileNode->blkId, popFileNode->st, writedArea, fileStk[fId], fileStk[fId]->next);
			blkNode * addedBlkNode = blkBuf[blkBCnt++].alloc(fId, popFileNode->st, writedArea, blkStk[popFileNode->blkId], blkStk[popFileNode->blkId]->next);
			addedBlkNode->fileNodeP = addedFileNode;
			addedFileNode->blkNodeP = addedBlkNode;	
			for (int i = 0; i < writedArea; i++) {
				writePage(popFileNode->blkId, popFileNode->st + i, pages[writedSum+i]);
			}
			writedSum += writedArea;
		}
		else {
			int dataArr[FILE_SIZE];
			gMaxIdx = findGMax();
			for (blkNode * p = blkStk[gMaxIdx]->next; p; p = p->next) {
				for (int i = 0; i < p->size; i++) {
					dataArr[i] = readPage(gMaxIdx, p->st + i);
				}
			}
			removeBlock(gMaxIdx);

			// Valid한 data는 다시 원위치에 write
			
			for (blkNode * p = blkStk[gMaxIdx]->next; p; p = p->next) {
				for (int j = 0; j < p->size; j++) {
					writePage(gMaxIdx, p->st + j, dataArr[j]);
				}
			}
			
			//emptyNode chk후 push
			int before = -1, cur = -1;
			int firstEmptyIdx = -1, curIdx = -1;
			for (int k = 0; k < pageSize; k++, before = cur) {
				cur = readPage(gMaxIdx, k);
				curIdx = k;
				if (before == 0 && cur > 0) {
					//emptyNode Push
					fileBuf[fileBCnt++].alloc(gMaxIdx, firstEmptyIdx, curIdx - firstEmptyIdx, fileStk[0], fileStk[0]->next);

				}
				if (before != 0 && cur == 0) firstEmptyIdx = k;
			}
			gSumArr[gMaxIdx] = 0;
		}
	}
}

void removeFile(int fId) {
	for (fileNode * p = fileStk[fId]->next; p; p = p->next) {
		p->blkNodeP->pop();
		gSumArr[p->blkId] += p->size;
		p->pop();
	}
}

void modifyFile(int fId, int len, int pages[FILE_SIZE]) {
	removeFile(fId);
	writeFile(fId, len, pages);
}

int readFile(int fId, int bids[FILE_SIZE], int pids[FILE_SIZE]) {
	int sizeRst = 0;
	fileNode * p = fileStk[fId];
	// 맨 끝으로 이동
	while (p->next) {
		p = p->next;
	}

	int j = 0, k = 0;
	for (; p && p->blkId!=-1; p = p->prev) {
		sizeRst += p->size;
		for (int i = 0; i < p->size; i++) {
			bids[j++] = p->blkId;
			pids[k++] = p->st + i;
		}
	}
	return sizeRst;
}