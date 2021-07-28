#include <list>
#include <unordered_map>

using namespace std;
using ull = unsigned long long;

const int LN = 1e4 + 3;
const int LF = 5e4 + 3;
const int LD = 5e3 + 3;
const int LL = 5e3 + 3;

enum DIRECTION{
	EAST, WEST, SOUTH, NORTH
};

struct rail {
	int r, c, isCFront, mDirection;
	int lastDir;
};

struct myHash {
	size_t operator()(const rail &r) const{
		return (ull)((ull)(r.r * (ull)LN) + r.c);
	}
};

struct myEqual {
	bool operator()(const rail& r1, const rail& r2) const {
		return (r1.r==r2.r && r1.c == r2.c);
	}
};

bool isCycle=false;

list<rail> li;

int r[4] = { 0, 0, 1, -1 };
int c[4] = { 1, -1, 0, 0 };

unordered_map<rail, list<rail>::iterator, myHash, myEqual> hTab;

DIRECTION getLastDir(int beforeLastDir, int _mDirection){
	DIRECTION rst;
	switch (beforeLastDir) {
	case EAST : 
		if (_mDirection == 0) rst = NORTH;
		if (_mDirection == 1) rst = EAST;
		if (_mDirection == 2) rst = SOUTH;
		break;

	case WEST : 
		if (_mDirection == 0) rst = SOUTH;
		if (_mDirection == 1) rst = WEST;
		if (_mDirection == 2) rst = NORTH;
		break;

	case SOUTH : 
		if (_mDirection == 0) rst = EAST;
		if (_mDirection == 1) rst = SOUTH;
		if (_mDirection == 2) rst = WEST;
		break;

	case NORTH : 
		if (_mDirection == 0) rst = WEST;
		if (_mDirection == 1) rst = NORTH;
		if (_mDirection == 2) rst = EAST;
		break;
	}
	return rst;
}

void init(int N)
{
	isCycle = false;
	li.clear();
	li.insert(li.begin(), { N, N, -1, -1, -1 });
	hTab.clear();
}

void addRail(int mFront, int mDirection)
{

}

int delRail(int mRow, int mCol)
{
	return 0;
}