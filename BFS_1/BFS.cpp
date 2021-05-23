#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

int visited[6];
int adjMatrix[6][6] = {
{ 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 2, 0 },
{ 0, 0, 2, 0, 0, 4 },
{ 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, }
};

// from �� ���� �������� �Ͽ� BFS ���� 
void BFS(int from)
{
	queue<int> que;
	que.push(from);
	visited[from] = 1;

	while (!que.empty())
	{
		int v = que.front();
		que.pop();

		cout << v << " ";
		for (int i = 1; i <= 5; i++)
		{
			if (!visited[i] && adjMatrix[v][i]) // i ������ ť�� ������� ���� v�� i�� ������ִٸ� true                    
			{
				que.push(i); // v�� ����� ������ ��ȣ�� ť�� ����
				visited[i] = 1; // ť�� ������ ������Ƿ� �ߺ� �湮���� �ʱ� ���� visited �迭 ����
			}
		}
	}

}


int main()
{

	BFS(2);
	return 0;
}

