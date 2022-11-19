#include <iostream>
#include <stdio.h>

using namespace std;

void Swap(int element[], int a, int b)
{
	int s = element[b];
	element[b] = element[a];
	element[a] = s;
}

void BubbleOnce(int element[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (element[i] > element[i + 1])
		{
			Swap(element, i,i + 1);
		}
	}
}

void SortInBubble(int element[], int num)
{
	for (int i = num; i > 1; i--)
	{
		BubbleOnce(element, i);
	}
}

void InsertOnce(int element[], int tail, const int& a)
{
	int i = tail - 1;
	while (element[i] > a && i >= 0)
	{
		element[i + 1] = element[i];
		i--;
	}
	element[i + 1] = a;
}

void SortInInsert(int element[], int num)
{
	for (int i = 1; i < num; i++)
	{
		int start = element[i];
		InsertOnce(element, i, start);
	}
}

void MergeSorting(int a[], int left, int mid, int right) {
	int*	element = new int[right - left + 1];
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right) {
		element[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
	}

	while (i <= mid) {
		element[k++] = a[i++];
	}

	while (j <= right) {
		element[k++] = a[j++];
	}

	for (k = left; k <= right; k++) {
		a[k] = element[k - left];
	}

	delete[] element;
}

void DivideProcess(int arr[], int L, int R) {
	if (L == R)
		return;
	int mid = L + ((R - L) / 2);
	DivideProcess(arr, L, mid);
	DivideProcess(arr, mid + 1, R);
	MergeSorting(arr, L, mid, R);
}


int main()
{
	int num = 0;
	int element[18];
	int index = 0;
	cout << "Input" << endl;
	cin >> index;
	while (index != 0)
	{
		element[num] = index;
		num++;
		if (num == 18)
			break;
		cin >> index;
	}
	cout << "1-Bubble Sort, 2-InsertSort, 3-MergeSort" << endl;
	cin >> index;
	switch (index)
	{
	case 1: SortInBubble(element, num);
		break;
	case 2: SortInInsert(element, num);
		break;
	case 3:DivideProcess(element, 0, num - 1);
		break;
	}
	cout << "Output" << endl;
	switch (index)
	{
	case 1: cout << "BubbleSort" << endl;
		break;
	case 2: cout << "InsertSort" << endl;
		break;
	case 3:cout << "MergeSort" << endl;
		break;
	}
	for (int i = 0; i < num; i++)
	{
		if (i == num - 1)
			cout << element[num - 1];
		else
			cout << element[i] << ", " ;
	}
	cout << endl << "End0";
	return 0;
}
