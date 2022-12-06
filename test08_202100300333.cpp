#include <iostream>
#include <string>
#include <queue>

using namespace std;

class GraphM
{
public:
	GraphM() { n = 0;  memset(matrix, 0, sizeof(matrix)); }
	void BFSSearch(int, int[]);
	void DFSSearch(int, int[]);
	void insertEdge(int, int, int);
	void DJ(int, int[], int[]);
	int matrix[10][10];
	int n;
	int edge;
};

void GraphM::insertEdge(int s, int e, int weight)
{
	matrix[s][e] = weight;
	matrix[e][s] = weight;
}

void GraphM::BFSSearch(int s, int reach[])
{
	int flag = 0;
	queue<int> q;
	reach[s] = 1;
	q.push(s);
	cout << s;
	while (!q.empty())
	{
		int f = q.front();
		q.pop();

		for (int i = 1; i <= n; i++)
		{
			if (matrix[f][i] != 0 && reach[i] == 0)
			{				
				cout << ",";
				q.push(i);
				reach[i] = 1;
				cout << i;
			}
		}
	}
}

void GraphM::DFSSearch(int s, int reach[])
{
	int flag = 0;
	reach[s] = 1;
	cout << s;
	for (int i = 1; i <= n; i++)
	{
		if (matrix[s][i] != 0 && reach[i] == 0)
		{
			flag++;
			if (flag < n)
				cout << ",";
			DFSSearch(i, reach);
		}
	}
}

void GraphM :: DJ(int s, int reach[], int dist[])
{
	queue<int> qs;
	reach[s] = 1;
	qs.push(s);
	while (!qs.empty()) 
	{
		int f = qs.front();
		qs.pop();
		reach[f] = 1;
		for (int i = 1; i <= n; i++) 
		{
			if (matrix[f][i] != 0 && reach[i] == 0) 
			{
				qs.push(i);
				if (matrix[f][i] + dist[f] < dist[i]) 
				{
					dist[i] = matrix[f][i] + dist[f];
				}
			}
		}
	}
}

int main()
{
	GraphM a;
	int start = 0;
	int end = 0;
	int weight = 0;
	char pass;
	int r[10];
	int d[10];
	d[1] = 0;
	for (int i = 2; i <= 9; i++)
	{
		d[i] = 9999;
	}
	memset(r, 0, sizeof(r));
	cout << "Input" << endl;
	cin >> a.n;
	cin >> pass;
	cin >> a.edge;
	for (int i = 1; i <= a.edge; i++)
	{
		cin >> start;
		cin >> pass;
		cin >> end;
		cin >> pass;
		cin >> weight;
		a.insertEdge(start, end, weight);
	}
	cout << "Output" << endl;
	a.BFSSearch(1, r);
	cout << endl;
	memset(r, 0, sizeof(r));
	a.DFSSearch(1, r);
	cout << endl;
	memset(r, 0, sizeof(r));
	a.DJ(1, r, d);
	if (d[a.n] != 9999)
		cout << d[a.n] << endl;
	else
		cout << 0 << endl;
	cout << "End";
	return 0;
}
