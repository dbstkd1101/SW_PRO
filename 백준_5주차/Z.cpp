#include <stdio.h>

int N;
int r, c;

int dr[4] = {0, 0, 1, 1};
int dc[4] = {0, 1, 0, 1};
int ans = -1;
int find = 0;

void DFS(int Dim, int startR, int startC) {
	
	if (find) {
		return ;
	}

	if (Dim == 1) {
		for (int i = 0; i < 4; i++) {
			ans++;
			if(startR + dr[i]==r && startC + dc[i]==c){
				find = 1;
				return ;
			}
		}
		return;
	}

	DFS(Dim - 1, startR, startC);
	DFS(Dim - 1, startR, startC + (2 << (Dim - 2)));
	DFS(Dim - 1, startR+(2<<(Dim-2)), startC);
	DFS(Dim - 1, startR + (2 << (Dim - 2)), startC + (2 << (Dim - 2)));

	return;
}
int main() {

	freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &N, &r, &c);

	DFS(N, 0, 0);

	printf("%d\n", ans);	


	return 0;
}