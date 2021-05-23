#include <stdio.h>

int N;
int bufCnt;

#define MAX_DAYS 36531


typedef struct node {
	int ID;
	node * next;
}regit;

typedef struct bucket {
	regit * head;
	int cnt;
}BUCKET;

regit buf[10001];

BUCKET bucketYYMMDD[MAX_DAYS+1];


typedef struct id {
	int regitedDays[10001];
	int regitCnt;
}ID;

ID IDArray[10001];

regit* mAlloc(int ID, int bucketHashCode) {
	buf[bufCnt].ID = ID;
	buf[bufCnt].next = bucketYYMMDD[bucketHashCode].head;
	bucketYYMMDD[bucketHashCode].head = &buf[bufCnt];
	bucketYYMMDD[bucketHashCode].cnt++;

	return &buf[bufCnt++];
}

int getDaysOfYear(int y) {

	int rst;

	if (y % 400 == 0 || (y % 4 == 0 && y % 100)) {
		rst = 366;
	}
	else {
		rst = 365;
	}
	return rst;
}

int getDaysOfMonth(int y, int m) {
	int d[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (y % 400 == 0 || (y % 4 == 0 && y % 100)) d[2] = 29; /// ¿±≥‚¿Ã∂Û∏È
	return d[m];
}

// MAX : 36531
int getDays(int yyyymmdd) {
	// 2018 01 01 ~ 2117 12 31
	// parsing
	int year = (yyyymmdd % 100000000) / 10000;
	int month = (yyyymmdd % 10000) / 100;
	int day = (yyyymmdd % 100) / 1;

	int sumOfDays = 0;

	for (int i = 0; 2018 < (year - i); i++) {
		sumOfDays += getDaysOfYear(2018 + i);
	}

	for (int i = 1; i <= month-1; i++) {
		sumOfDays += getDaysOfMonth(year, month);
	}

	sumOfDays += day;
	
	return sumOfDays;
}



void init() {
	N = 0;
	bufCnt = 0;
}

void register1(int ID, int mode, int cycle, int startDate) {

	int days = getDays(startDate);
	
	switch (mode) {
	case 0:
		mAlloc(ID, days);
		IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days;
		break;
	case 1:
		for(int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 1);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 1;
		}
		break;
	case 2:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 2);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 2;
		}
		break;
	case 3:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 3);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 3;
		}
		break;
	case 4:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 4);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 4;
		}
		break;
	case 5:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 5);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 5;
		}
		break;
	case 6:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 6);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 6;
		}
		break;
	case 7:
		for (int i = 0; i < cycle; i++) {
			mAlloc(ID, days + i * 7);
			IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days + i * 7;
		}
		break;
	case 8:
		int year = (startDate % 100000000) / 10000;
		int month = (startDate % 10000) / 100;
		
		for (int i = 0; i < cycle; i++) {
			if (i == 0) {
				mAlloc(ID, days);
				IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days;
			}
			else {
				month++;
				if (month / 13 >= 1) {
					month = 1;
					year++;
				}
				mAlloc(ID, days += getDaysOfMonth(year, month));
				IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days;
			}
		}
	case 9 :
		int year = (startDate % 100000000) / 10000;
		
		for (int i = 0; i < cycle; i++) {
			if (i == 0) {
				mAlloc(ID, days);
				IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days;
			}
			else {
				year++;
				mAlloc(ID, days += getDaysOfYear(year));
				IDArray[ID].regitedDays[IDArray[ID].regitCnt++] = days;
			}
		}
		break;
	}
}

int cancel(int mode, int dateOrID) {

	switch (mode) {
	case 0:
		int days = getDays(dateOrID);
		if (bucketYYMMDD[days].head == NULL) {
			return;
		}
		else {
			// √π π¯¬∞ ≥
			regit* regitMember = bucketYYMMDD[days].head;
			for (int i = 0; i < IDArray[regitMember->ID].regitCnt; i++) {
				if (IDArray[regitMember->ID].regitedDays[i] == days) {
					IDArray[regitMember->ID].regitedDays[i] = -1;
					IDArray[regitMember->ID].regitCnt--;
					break;
				}
			}

			while (regitMember -> next != NULL) {
				regitMember = regitMember->next;
				for (int i = 0; i < IDArray[regitMember->ID].regitCnt; i++) {
					if (IDArray[regitMember->ID].regitedDays[i] == days) {
						IDArray[regitMember->ID].regitedDays[i] = -1;
						IDArray[regitMember->ID].regitCnt--;
						break;
					}
				}
			}
			bucketYYMMDD[days].head=NULL;
			bucketYYMMDD[days].cnt=0;
		}
		break;

	case 1:
		int days = getDays(dateOrID);
		if (bucketYYMMDD[days].head == NULL) {
			return;
		}
		else {
			// √π π¯¬∞ ≥
			regit* regitMember = bucketYYMMDD[days].head;
			cancel(2, regitMember->ID);

			while (regitMember->next != NULL) {
				regitMember = regitMember->next;
				cancel(2, regitMember->ID);
			}
			bucketYYMMDD[days].head = NULL;
		}
		break;

	case 2:
		int ID = getDays(dateOrID);

		int originRegitCnt = IDArray[ID].regitCnt;
		for (int i = 0; i < originRegitCnt; i++) {
			int days = IDArray[ID].regitedDays[i];
			
			if (bucketYYMMDD[days].head == NULL) {
				return -1;
			}
			else {
				regit* regitMember = bucketYYMMDD[days].head;



			}


		}

		if (bucketYYMMDD[days].head == NULL) {
			return;
		}
		else {
			

		}

		break;
	}

	return 1;
}


int main() {

	printf("%d\n", getDays(21171231));

	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	int mode=-1;
	for (int i = 0; i < N; i++) {
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
			int ID, int mode, int cycle, int startDate;
			scanf(" %d %d %d %d", &ID, &mode, &cycle, &startDate);
			register1(ID, mode, cycle, startDate);
			break;

		case 2:
			int mode, int dateOrID;
			scanf(" %d %d", &mode, &dateOrID);

			break;

		case 3:

			break;

		default:
			printf("mode error!!\n");
			break;
		}
	}

	return 0;

}