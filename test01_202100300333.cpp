#include <iostream>

using namespace std;

void Swap(int element[], int a, int b)
{
	int s = element[b];
	element[b] = element[a];
	element[a] = s;
}

void SetPer(int element[], int alength, int bcur)
{
	if (alength == bcur)
	{
		for (int i = 0; i < alength; i++)
		{
			cout << element[i];		
			if (i != alength - 1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}
	else
	{
		for (int i = bcur; i < alength; i++)
		{
			Swap(element, bcur, i);
			SetPer(element, alength , bcur + 1);
			Swap(element, bcur, i);
		}
	}
}

int main()
{
	int element[20];
	int index = 0;
	int num = 0;
	cout << "Input" << endl;
	cin >> index;
	while (index != 0)
	{
		element[num] = index;
		num++;
		cin >> index;
	}
	cout << "Output" << endl;
	SetPer(element, num, 0);
	cout << "end";
	return 0;
}