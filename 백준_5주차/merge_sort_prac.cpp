typedef int data;

void merge(data arr[], int s, int m, int e) {
	int i = s, j = m + 1, k = s;
	
	int sorted[100];

	while (i <= m && j <= e) {
		if (arr[i] < arr[j]) sorted[k++] = arr[i++];
		else sorted[k++] = arr[j++];
	}
	while (i <= m) sorted[k++] = arr[i++];
	while (j <= e) sorted[k++] = arr[j++];

	for (int l = s; l <= e; l++) {
		arr[l] = sorted[l];
	}
}


void mergeSort(data arr[], int s, int e) {
	int m;
	while (s < e) {
		m = (s + e) / 2;
		mergeSort(arr, s, m);
		mergeSort(arr, m+1, e);
		merge(arr, s, m, e);
	}
}

