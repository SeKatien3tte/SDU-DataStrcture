#include <iostream>

using namespace std;

static int op = 1;

template <class T>
struct BinaryTreeNode
{
	T data;
	BinaryTreeNode<T>* leftpart;
	BinaryTreeNode<T>* rightpart;

	BinaryTreeNode() { leftpart = rightpart = NULL; }
	BinaryTreeNode(const T& theData)
	{
		data = theData;
		leftpart = rightpart = NULL;
	}
};

template <class T>
class SearchBinaryTree
{
public:
	SearchBinaryTree() { root = NULL; size = 0; }
	void visitNodes(BinaryTreeNode<T>*);
	void preOrder(BinaryTreeNode<T>*);
	void midOrder(BinaryTreeNode<T>*);
	BinaryTreeNode<T>* GetRoot() { return root; }
	void SearchBinaryTrees(T*, int);

private:
	BinaryTreeNode<T>* root;
	int size;
};

template <class T>
void SearchBinaryTree<T> ::visitNodes(BinaryTreeNode<T>* p)
{
	cout << p->data;
	if (op != size)
		cout << ",";
	op++;
}

template <class T>
void SearchBinaryTree<T> ::preOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		visitNodes(root);
		preOrder(root->leftpart);
		preOrder(root->rightpart);
	}
}

template <class T>
void SearchBinaryTree<T>::midOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		midOrder(root->leftpart);
		visitNodes(root);
		midOrder(root->rightpart);
	}
}

template<class T>
void SearchBinaryTree<T> :: SearchBinaryTrees(T* a, int n)
{
	BinaryTreeNode<T>* p = new BinaryTreeNode<T>(a[1]);
	root = p;
	size = 1;
	BinaryTreeNode<T>* ps = NULL;
	ps = p;
	for (int i = 2; i <= n; i++)
	{
		p = root;
		while (p != NULL) {
			if (a[i] < p->data) 
			{
				ps = p;
				p = p->leftpart;
			}
			else {
				if (a[i] > p->data) 
				{
					ps = p;
					p = p->rightpart;
				}
				else 
				{
					i++;
					break;
				}
			}
		}
		if (i > n)
			break;
		BinaryTreeNode<T>* input = new BinaryTreeNode<T>(a[i]);
		size++;
		if (a[i] < ps->data)
			ps->leftpart = input;
		else 
		{
			if (a[i] > ps->data)
				ps->rightpart = input;
			else
				break;
		}			
	}
}

template <class T>
class MaxHeapTree
{
public:
	MaxHeapTree() { length = 0; num = 0; }
	void pop();
	void SortHeap(T*, int);
	void InitializeHeap(T*, int);
	T* heap = new T[21];                                  //T heap[21]是静态，不能给静态指针赋值
	int length;
	int num;
};



template <class T>
void MaxHeapTree<T> ::pop()                                 //删除根之后我们需要把第二大的值定为根，这个时候取最后一个数出来
{																				 //让他在根节点一级一级往下比较并交换更大的值上来，由于本来子树就是大根堆
	if (num == 0)														//所以当把最后一个元素排序好之后得到的还是一个大根堆
		return;
	heap[1].~T();
	T lastdata = heap[num--];
	int cvalue = 1;
	int childvalue = 2;
	while(childvalue <= num)
	{
		if (childvalue < num && heap[childvalue] < heap[childvalue + 1])
			childvalue++;
		if (lastdata < heap[childvalue])
		{
			heap[cvalue] = heap[childvalue];
			cvalue = childvalue;
			childvalue *= 2;
		}
		else
			break;
	}
	heap[cvalue] = lastdata;
}

template <class T>
void MaxHeapTree<T> ::InitializeHeap(T* theH, int theS)
{
	delete[] heap;
	heap = theH;
	num = theS;

	for (int rootvalue = num / 2; rootvalue >= 1; rootvalue--)
	{
		T rootdata = heap[rootvalue];
		int childvalue = rootvalue * 2;
		while (childvalue < num)
		{
			if (childvalue < num && heap[childvalue] < heap[childvalue + 1])
				childvalue++;
			if (heap[rootvalue] < heap[childvalue])
			{
				heap[childvalue / 2] = heap[childvalue];
				childvalue *= 2;
			}
			else
				break;
		}
		heap[childvalue / 2] = rootdata;
	}
}

template <class T>
void MaxHeapTree<T> ::SortHeap(T* a,int n)
{
	for (int i = n; i >= 1; i--) 
	{
		T data = heap[1];
		pop();
		a[i] = data;
	}
}

int main()
{
	int s[21];
	s[0] = 0;
	int n = 0;
	int input = 0;
	SearchBinaryTree<int> tree;
	MaxHeapTree<int> heap;
	cout << "Input" << endl;
	cin >> input;
	while (input != 0)
	{
		n++;
		s[n] = input;
		cin >> input;
	}
	tree.SearchBinaryTrees(s, n);
	heap.InitializeHeap(s, n);
	cout << "Output" << endl;
	for (int i = 1; i <= heap.num; i++)
	{
		cout << heap.heap[i];
		if (i < heap.num)
			cout << ",";
	}
	cout << endl;
	n = heap.num;
	heap.SortHeap(s, heap.num);
	for (int j = 1; j <= n; j++)
	{
		cout << s[j];
		if (j < n)
			cout << ",";
	}
	cout << endl;
	tree.preOrder(tree.GetRoot());
	op = 1;
	cout << endl;
	tree.midOrder(tree.GetRoot());
	op = 1;
	cout << endl;
	cout << "End";
	return 0;
}

