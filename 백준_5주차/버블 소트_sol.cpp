#include <iostream>

using namespace std;



const int MAX = 500000;



int arr[MAX], arr2[MAX];



long long func(int start, int end)

{

	//탈출 조건

	if (start == end)

		return 0;



	int mid = (start + end) / 2;

	//반으로 분할하여 탐색

	long long result = func(start, mid) + func(mid + 1, end);



	int i = start;

	int j = mid + 1;

	int idx = 0;

	while (i <= mid || j <= end)

	{

		//순서대로 잘 있다면 그냥 추가해주고

		if (i <= mid && (j > end || arr[i] <= arr[j]))

			arr2[idx++] = arr[i++];

		//mid를 기준으로 왼쪽의 inversion 개수 파악

		else

		{

			result += (mid - i + 1) * 1LL;

			arr2[idx++] = arr[j++];

		}

	}

	//배열 업데이트

	for (int k = start; k <= end; k++)

		arr[k] = arr2[k - start];

	return result;

}



int main(void)
{

	freopen("input.txt", "r", stdin);

	int N;

	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}


	long long result = func(1, N);

	cout << result << "\n";

	return 0;

}
