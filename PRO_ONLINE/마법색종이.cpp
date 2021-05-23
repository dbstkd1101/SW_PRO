#include <stdio.h>

int H, W, N;
int maxAns = 0, minAns = 2e9, bCnt;

struct node {
	int sx, sy, ex, ey, color;
	node* left, *right;
	node* mAlloc(int _sx, int _sy, int _ex, int _ey, int _color) {
		sx = _sx, sy = _sy, ex = _ex, ey = _ey, color = _color;
		return this;
	}
	void push(int x, int y, node buf[]) {
		// leaf, (항상 2개씩 만드는 이진완성(?) 트리
		if (left == 0) {
			if (color == 1) {
				left = buf[bCnt++].mAlloc(sx, sy, x, ey, 0);
				right = buf[bCnt++].mAlloc(x, sy, ex, ey, 0);
				return;
			}
			if (color == 0) {
				left = buf[bCnt++].mAlloc(sx, sy, ex, y, 1);
				right = buf[bCnt++].mAlloc(sx, y, ex, ey, 1);
				return;
			}
		}
		if (x < left->ex && y < left->ey) left->push(x, y, buf);
		else right->push(x, y, buf);
	}
	void area() {
		// leaf이면
		if (left == 0) {
			int area = (ex - sx)*(ey - sy);
			if (maxAns < area) maxAns = area;
			if (minAns > area) minAns = area;
			return;
		}
		left->area();
		right->area();
	}

}buf[600100], *root;

int main() {
	scanf("%d %d %d", &H, &W, &N);
	root = buf[bCnt++].mAlloc(0, 0, H, W, 0);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		root->push(x, y, buf);
	}
	root->area();
	printf("%d %d\n", maxAns, minAns);
	return 0;
}