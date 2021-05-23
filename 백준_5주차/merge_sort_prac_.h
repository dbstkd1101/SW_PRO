#pragma once


typedef int data;


void merge(data arr[], int s, int m, int e) {
	int i = s, j = m + 1, k = s;

	data sorted[100];
}

void mergeSort(data arr[], int s, int e) {
	int m;
	if (s < e) {
		int m = (s + e) / 2;
		mergeSort(arr, s, m);
		mergeSort(arr, m + 1, e);
		merge(arr, s, m, e);
	}
}