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

// from 을 시작 정점으로 하여 BFS 수행 
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
			if (!visited[i] && adjMatrix[v][i]) // i 정점은 큐에 담긴적이 없고 v와 i가 연결되있다면 true                    
			{
				que.push(i); // v에 연결된 정점의 번호를 큐에 담음
				visited[i] = 1; // 큐에 정점을 담았으므로 중복 방문하지 않기 위해 visited 배열 갱신
			}
		}
	}

}


int main()
{

	BFS(2);
	return 0;
}

