typedef int data;


void merge(data arr[], int s, int m, int e) {
	int i = s, j = m+1, k = s;

	data sorted[100];

	while (i <= m && j <= e) {
		if (arr[i] <= arr[j]) sorted[k++] = arr[i++];
		else sorted[k++] = arr[j++];
	}

	while (i <= m) sorted[k++] = arr[i++];
	while (j <= m) sorted[k++] = arr[j++];

	for (int l = s; l <= e; l++) {
		arr[l] = sorted[l];
	}
}



void mergeSort(data arr[], int s, int e) {
	if (s < e) {
		int mid = (s + e) / 2;
		mergeSort(arr, s, mid);
		mergeSort(arr, mid+1, e);
		merge(arr, s, mid, e);
	}
}
