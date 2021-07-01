#pragma once
#ifndef NULL
#define NULL 0
#endif

#define MAX_HEAP_LEN 1000
typedef int data;

//왼쪽이 더 나은거(등호는 문제마다 다름)
bool MAX(data a, data b) {
	return a > b;
}
bool MIN(data a, data b) {
	return a < b;
}

void swap(data &a, data &b) {
	data t = a; a = b; b = t;
}

struct PQ {
	int hn;
	bool (*comp)(data, data);
	data heap[MAX_HEAP_LEN];

	void init(bool (*_comp)(data, data)) {
		hn = 0;
		comp = _comp;
	}

	data top() {
		return hn > 0 ? heap[0] : NULL;
	}
	bool empty() {return hn == 0;}
	int size() {return hn;}

	void push(data input) {
		heap[++hn] = input;
		// 자식이 더 낫다면
		//특이점 가운데
		for (int cur = hn; cur > 1 && comp(heap[cur], heap[cur / 2]); cur /= 2) {
			swap(heap[cur], heap[cur / 2]);
		}
	}
	data pop() {
		if (hn == 0) return NULL;

		data ret = heap[1];
		swap(heap[1], heap[hn--]);
		//  처음 2개, 마지막이 2개
		int p = 1;
		for (int cur = 2;cur<=hn; p=cur, cur*=2) {
			// 형이 있으면서
			if (cur+1<=hn && comp(heap[cur + 1], heap[cur])) cur += 1;
			if (comp(heap[p], heap[cur])) break;
			else swap(heap[p], heap[cur]);
		}
		return ret;
	}
}maxpq, minpq;