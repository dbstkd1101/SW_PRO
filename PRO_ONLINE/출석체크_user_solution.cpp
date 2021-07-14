/*


* @ file: [H2119] 출석체크


* @brief: 샘플 답안 * @copyright: All rights reserved (c) 2021 Samsung Electronics, Inc.


* @copyright: All rights reserved (c) 2021 Samsung Electronics, Inc.


*/


const int days_per_month[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int days_per_month_sum_before[14] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };


struct SClassTime
{
    int id;
    int start;
    int end;
    int ratio;
    int len;
    int minTime;
};


SClassTime ClassTime[100001] = {};


int StrToInt(char* str)
{
    int ret = 0;
    while (*str >= '0' && *str <= '9') {
        ret *= 10;
        ret += *str - '0';
        str++;
    }
    return ret;
}
int HourToInt(char* str)
{
    return StrToInt(str) * 3600;
}
int MinToInt(char* str)
{
    return StrToInt(str) * 60;
}
int SecToInt(char* str)
{
    return StrToInt(str);
}


int TimeToInt(char* str)
{
    return HourToInt(str) + MinToInt(str + 3) + SecToInt(str + 6);
}


int YearToInt(char* str)
{
    int year = (StrToInt(str) - 2019);
    int sec = year * 31536000; // 365 * 24 * 60 * 60;
    return sec;
}


int MonthToInt(char* str)
{
    int mon = StrToInt(str);
    int day = days_per_month_sum_before[mon];
    int sec = day * 86400; // 24 * 60 * 60;    
    return sec;
}


int DayToInt(char* str)
{
    int day = StrToInt(str);
    int sec = (day - 1) * 86400; // 24 * 60 * 60;    // 0 일부터 
    return sec;
}


void newClass(int mClassId, char mClassBegin[], char mClassEnd[], int mRatio) {
    SClassTime& classtime = ClassTime[mClassId];
    classtime.id = mClassId;
    classtime.start = TimeToInt(mClassBegin);
    classtime.end = TimeToInt(mClassEnd);
    classtime.len = classtime.end - classtime.start + 1;
    classtime.ratio = mRatio;
    // 99 왜 더하지??
    classtime.minTime = (classtime.len * classtime.ratio + 99) / 100;
}


int RecordToInt(char* str)
{
    return YearToInt(str) + MonthToInt(str + 5) + DayToInt(str + 8) + HourToInt(str + 11) + MinToInt(str + 14) + SecToInt(str + 17);
}


int DateToInt(char* str)
{
    return YearToInt(str) + MonthToInt(str + 5) + DayToInt(str + 8);
}


struct SNode
{
    int recordId;
    struct SNode* pre;
    struct SNode* next;
};


int BufferCur = 0;
SNode Buffer[100000] = {};


SNode* MyAlloc()
{
    return &Buffer[BufferCur++];
}


struct SRecord
{
    int mRecordId;
    int mClassId;
    int start;
    int end;
    struct SNode* pnode;
};


SRecord Record[100001] = {};


struct SList
{
    SNode* pHead;
    SNode* pTail;


    SList() {
        pHead = nullptr;
        pTail = nullptr;
    }


    void Reset()
    {
        pHead = MyAlloc();
        pTail = MyAlloc();
        pHead->pre = nullptr;
        pHead->next = pTail;
        pTail->pre = pHead;
        pTail->next = nullptr;
    }


    int Compare(SNode* node1, SNode* node2)
    {
        return Record[node1->recordId].start - Record[node2->recordId].start;
    }


    void Push(int recordId)
    {
        SNode* newNode = MyAlloc();
        newNode->recordId = recordId;
        newNode->pre = nullptr;
        newNode->next = nullptr;
        Record[recordId].pnode = newNode;


        SNode* pNode = pHead;
        while (pNode->next != pTail)
        {
            if (Compare(newNode, pNode->next) <= 0) {
                break;
            }
            pNode = pNode->next;
        }


        SNode* pre = pNode;
        SNode* next = pNode->next;
        pre->next = newNode;
        newNode->pre = pre;
        newNode->next = next;
        next->pre = newNode;
    }


    void Del(int recordId)
    {
        SNode* pDel = Record[recordId].pnode;
        if (pDel == nullptr) return;
        Record[recordId].pnode = nullptr;
        SNode* pre = pDel->pre;
        SNode* next = pDel->next;
        pre->next = next;
        next->pre = pre;
    }
};


SList RecordList;


void newRecord(int mRecordId, int mClassId, char mRecordBegin[], char mRecordEnd[])
{
    SRecord& record = Record[mRecordId];
    record.mRecordId = mRecordId;
    record.mClassId = mClassId;
    record.start = RecordToInt(mRecordBegin);
    record.end = RecordToInt(mRecordEnd);


    RecordList.Push(mRecordId);
}


void changeRecord(int mRecordId, char mNewBegin[], char mNewEnd[]) {
    RecordList.Del(mRecordId);


    SRecord& record = Record[mRecordId];
    record.start = RecordToInt(mNewBegin);
    record.end = RecordToInt(mNewEnd);


    RecordList.Push(mRecordId);
}


int IsAttend(int classId, int startTime, int endTime, int minTime)
{
    SNode* pNode = RecordList.pHead->next;
    int cur = startTime;
    int end;
    int sum = 0;
    while (pNode != RecordList.pTail) {
        SRecord& record = Record[pNode->recordId];
        if (record.mClassId != classId) {
            pNode = pNode->next;
            continue;
        }
        if (endTime < record.start) break;
        end = endTime < record.end ? endTime : record.end;
        if (cur < record.start) {
            cur = record.start;
        }
        if (cur <= end) {
            sum += end - cur + 1;
            cur = end + 1;
            if (sum >= minTime) return 1;
        }
        pNode = pNode->next;
    }
    return 0;
}


int checkAttendance(int mClassId, char mDate[]) {
    SClassTime& classtime = ClassTime[mClassId];
    int dateInt = DateToInt(mDate);
    int classTimeStart = dateInt + classtime.start;
    int classTimeEnd = dateInt + classtime.end;
    return IsAttend(mClassId, classTimeStart, classTimeEnd, classtime.minTime);
}


int checkCheating() {
    SNode* pNode = RecordList.pHead->next;


    for (SNode* iter1 = RecordList.pHead->next; iter1->next != RecordList.pTail; iter1 = iter1->next) {
        for (SNode* iter2 = iter1->next; iter2 != RecordList.pTail; iter2 = iter2->next) {
            SRecord& record1 = Record[iter1->recordId];
            SRecord& record2 = Record[iter2->recordId];


            if (record1.mClassId == record2.mClassId) continue;


            int time0 = record2.end - record1.start + 1;
            int time1 = record1.end - record1.start + 1;
            int time2 = record2.end - record2.start + 1;
            if (time0 < time1 + time2) {
                return 1;
            }
        }
    }
    return 0;
}


void init() {
    BufferCur = 0;
    RecordList.Reset();
}


void destroy() {
}