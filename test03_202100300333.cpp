#include <iostream>
using namespace std;

template<class T>
struct chainNode
{
public:
	T element;
	chainNode<T>* next;

	chainNode() {}
	chainNode(const T& theElement) { element = theElement; next = NULL; }
	chainNode(const T& theElement, chainNode<T>* Next)
	{
		element = theElement;
		next = Next;
	}
};

template<class T>
class ChainList
{
public:
	ChainList() { firstNode = NULL; listSize = 0; }
	//ChainList(const ChainList<T>&);
	~ChainList();

	int size() const { return listSize; }
	void Insert(const T&);
	int SearchIndexOf(const T&) const;
	//void Output(ostream& out) const;

//protected:
	int listSize;
	chainNode<T>* firstNode;
};



template <class T>
ChainList<T> :: ~ChainList()
{
	while (firstNode != NULL)
	{
		chainNode<T>* target = firstNode;
		target = target->next;
		delete firstNode;
		firstNode = target;
	}
}

template <class T>
void ChainList<T> :: Insert(const T& element)
{
	if (firstNode == NULL || element <  firstNode->element)
	{
		firstNode = new chainNode<T>(element, firstNode);
		listSize++;
	}
	else
	{
		chainNode<T>* p = firstNode;
		while (p->next != NULL)
		{
			if (element < p->next->element)
			{
				chainNode<T>* saveNode = new chainNode<T>(element, p->next);
				p->next = saveNode;
				listSize++;
				return;
			}
			else
				p = p->next;
		}
		p->next = new chainNode<T>(element);
		listSize++;
	}
}

template <class T>
int ChainList<T> ::SearchIndexOf(const T& element) const
{
	int ind = 0;
	chainNode<T>* p = firstNode;
	while (p->next != NULL)
	{
		if (p->element != element)
		{
			p = p->next;
			ind++;
		}
		else
			return ind + 1;
	}
	if (p == NULL || p->element != element)
		return 0;
	else
		return ind + 1;
}



int main()
{
	int num = 0;
	ChainList<int> chain1, chain2;



	cout << "Input1" << endl;
	int data = 0;
	cin >> data;
	while (data != 0)
	{
		chain1.Insert(data);
		cin >> data;
	}
	cout << "Output1" << endl;
	chainNode<int>* out = chain1.firstNode;
	while (out != NULL && out->next != NULL)
	{
		cout << out->element << ",";
		out = out->next;
	}
	if (out->next == NULL)
		cout << out->element << endl;



	cout << "Input2" << endl;
	cin >> data;
	chain1.Insert(data);
	out = chain1.firstNode;
	cout << "Output2" << endl;
	while (out != NULL && out->next != NULL)
	{
		cout << out->element << ",";
		out = out->next;
	}
	if (out->next == NULL)
		cout << out->element << endl;



	cout << "Input3" << endl;
	cin >> data;
	cout << "Output3\n" << chain1.SearchIndexOf(data) << endl;



	cout << "Input4" << endl;
	cin >> data;
	cout << "Output4\n" << chain1.SearchIndexOf(data) << endl;



	cout << "Input5" << endl;
	cin >> data;
	while (data != 0)
	{
		chain2.Insert(data);
		cin >> data;
	}
	cout << "Output5" << endl;
	chainNode<int>* out2 = chain2.firstNode;
	while (out2 != NULL && out2->next != NULL)
	{
		cout << out2->element << ",";
		out2 = out2->next;
	}
	if (out2->next == NULL)
		cout << out2->element << endl;



	chainNode<int>* bp = chain2.firstNode;
	while (bp != NULL)
	{
		chain1.Insert(bp->element);
		bp = bp->next;
	}
	out = chain1.firstNode;
	while (out != NULL && out->next != NULL)
	{
		cout << out->element << ",";
		out = out->next;
	}
	if (out->next == NULL)
		cout << out->element << endl;
	cout << "End0";
	return 0;
}