#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#ifndef NULL 
#define NULL 0
#endif

#define MAX_CNT_N 10000
#define MAX_LEN_ID 10000
#define MAX_CNT_RESV 100
#define MAX_DAYS 100*365

int cnt[MAX_DAYS + 1000], table[100 + 1][13], bn;

struct dat {
	int id, dn;
	dat* id_prev, *id_next, *dn_prev, *dn_next;

	dat* alloc(int _id, int _dn, dat* idp, dat * idn, dat* dnp, dat* dnn) {
		id = _id, dn = _dn;
		
		// 내 기준 다른 node를 연결
		id_prev = idp, id_next = idn, dn_prev = dnp, dn_next = dnn;

		// 다른 node 기준 나를 연결
		if(id_prev) id_prev->id_next = this;
		if(dn_prev) dn_prev->dn_next= this;
		if(id_next) id_next->id_prev = this;
		if(dn_next) dn_next->dn_prev = this;

		return this;
	}

	void pop() {
		cnt[dn]--;
		if (id_prev) id_prev->id_next = id_next;
		if (dn_prev) dn_prev->dn_next = dn_next;
		if (id_next) id_next->id_prev = id_prev;
		if (dn_next) dn_next->dn_prev = dn_prev;
		return;
	}
}* mem[MAX_LEN_ID+10], * dat[MAX_DAYS+100], buf[MAX_CNT_N * MAX_CNT_RESV + MAX_DAYS + MAX_LEN_ID + 1000];

void init() {
	bn = 0;
	for (int i = 1; i < MAX_LEN_ID + 10; i++) {
		mem[i] = buf[bn++].alloc(NULL, NULL, NULL, NULL, NULL, NULL);
	}
	for (int i = 0; i < MAX_DAYS + 100; i++) {
		dat[i] = buf[bn++].alloc(NULL, NULL, NULL, NULL, NULL, NULL);
		cnt[i] = 0;
	}
	return;
}


int days(int y, int m) {
	int d[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (y % 400 == 0 || (y % 4 == 0 && y % 100)) d[2] = 29;
	return d[m];
}

// getDays()를 매번 호출해서 발생하는 중복 계산 부분을 최적화(누적합)
// YYYY, MM은 DD와 진법이 다르므로, 별도 정리
void table_fill() {
	int i, j, y;
	for (i = 2018; i < 2118; i++) {
		y = i - 2018;
		for (j = 1; j <= 12; j++) {
			table[y][j] = table[y][j - 1] + days(i, j);
		}
		table[y + 1][0] = table[y][12];
	}
	return;
}

int encode(int y, int m, int d) {
	return table[y - 2018][m - 1] + d;
}

void reserve() {
	int id, method, repeat, y, m, d, dn, i;
	scanf("%d %d %d", &id, &method, &repeat);
	scanf("%4d%2d%2d", &y, &m, &d);
	dn = encode(y, m, d);
	if (method == 0) repeat = 1;
	for (int i = 0; i < repeat; i++) {
		cnt[dn]++;
		// 필요할 때만 node 추가하는 LinkedList의 장점
		buf[bn++].alloc(id, dn, mem[id], mem[id]->id_next, dat[dn], dat[dn]->dn_next);
		if (method == 8) {
			if (++m > 12) y++, m = 1;
			dn = encode(y, m, d);
		}
		else if (method == 9) {
			dn = encode(++y, m, d);
		}
		else dn += method;

		if (y > 2117 || dn > table[99][12]) break;
	}
	return;
}

void del_id(int id) {
	while (mem[id]->id_next) mem[id]->id_next->pop();
	return;
}

void cancel() {
	int method, id, y, m, d, dn;
	scanf("%d", &method);
	if (method == 2) {
		scanf("%d", &id);
		del_id(id);
	}
	else {
		scanf("%4d%2d%2d", &y, &m, &d);
		dn = encode(y, m, d);
		while (dat[dn]->dn_next) {
			if (method == 0) dat[dn]->dn_next->pop();
			else del_id(dat[dn]->dn_next->id);
		}
	}
	return;
}

void output() {
	int y, m, d, dn, sum = 0;
	scanf("%4d%2d%2d", &y, &m, &d);
	dn = encode(y, m, d);
	for (int i = 0; i < 30; i++) {
		sum += cnt[dn + i];
	}
	printf("%d\n", sum);
	return;
}

int main() {
	freopen("input.txt", "r", stdin);
	int TC, N, cmd;
	table_fill();
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d", &N);
		init();
		while (N--) {
			scanf("%d", &cmd);
			switch (cmd) {
			case 1: 
				reserve();
				break;
			case 2:
				cancel();
				break;
			case 3:
				output();
				break;
			}
		}
	}

	return 0;
}


