const int FILESIZE = 512;

extern int readPage(int bid, int pid);
extern void writePage(int bid, int pid, int data);
extern int removeBlock(int bid);

void init(int blockSize, int pageSize) {

}

void writeFile(int fid, int len, int pages[FILESIZE]) {

}

void removeFile(int fid) {

}

void modifyFile(int fid, int len, int pages[FILESIZE]) {

}

int readFile(int fid, int bids[FILESIZE], int pids[FILESIZE]) {

	return 0;
}