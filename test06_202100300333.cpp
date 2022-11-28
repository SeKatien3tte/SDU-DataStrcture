#include <iostream>
#include <queue>
#include <string>
#include <list>

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
		data(theData);
		leftpart = rightpart = NULL;
	}
	BinaryTreeNode(const T& theData, BinaryTreeNode* theLeft, BinaryTreeNode* theRight)
	{
		data(theData);
		leftpart = theLeft;
		rightpart = theRight;
	}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; size = 0; }
	void CreateL(int, const T*);
	int GetHeight(BinaryTreeNode<T>*);
	int GetNodesNum(BinaryTreeNode<T>*);
	void LevelOrder(BinaryTreeNode<T>*);
	void preOrder(BinaryTreeNode<T>*);
	void midOrder(BinaryTreeNode<T>*);
	void backOrder(BinaryTreeNode<T>*);
	void visitNode(BinaryTreeNode<T>*);
	BinaryTreeNode<T>* GetRoot() { return root; }
	BinaryTreeNode<T>* CreateByPreorIn(const T*, const T*, int);

private:
	BinaryTreeNode<T>* root;
	int size;
};

template <class T>
void BinaryTree<T> :: CreateL(int length,const T* string)
{
	queue<BinaryTreeNode<T>*> pointers;
	size = length;
	int count = 1;
	BinaryTreeNode<T>* pointer = new BinaryTreeNode<T>();
	pointer->data = string[0];
	root = pointer;
	if (size == 1)
		return;
	while (count != size)
	{
		if (pointer->leftpart == NULL)
		{
			BinaryTreeNode<T>* left = new BinaryTreeNode<T>();
			left->data = string[count];
			pointer->leftpart = left;
			pointers.push(left);
			count++;
			if (count == size)
				break;
		}
		if (pointer->rightpart == NULL)
		{
			BinaryTreeNode<T>* right = new BinaryTreeNode<T>();
			right->data = string[count];
			pointer->rightpart = right;
			pointers.push(right);
			count++;
			if (count == size)
				break;
		}
		pointer = pointers.front();
		pointers.pop();
	}
}

template <class T>
void BinaryTree<T> ::LevelOrder(BinaryTreeNode<T>* p)
{
	queue<BinaryTreeNode<T>*> pointers;
	while (p != NULL)
	{
		visitNode(p);
		if (p->leftpart != NULL)
			pointers.push(p->leftpart);
		if (p->rightpart != NULL)
			pointers.push(p->rightpart);
		if (pointers.empty())
			return;
		else
		{
			p = pointers.front();
			pointers.pop();
		}
	}
}

template <class T>
void BinaryTree<T> :: visitNode(BinaryTreeNode<T>* p)
{
	cout << p->data;
	if (op != size)
		cout << ",";
	op++;
}

template <class T>
void BinaryTree<T> :: preOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		visitNode(root);
		preOrder(root->leftpart);
		preOrder(root->rightpart);
	}
}

template <class T>
void BinaryTree<T>:: midOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		midOrder(root->leftpart);
		visitNode(root);
		midOrder(root->rightpart);
	}
}

template <class T>
void BinaryTree<T> :: backOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		backOrder(root->leftpart);
		backOrder(root->rightpart);
		visitNode(root);
	}
}

template <class T>
int BinaryTree<T> :: GetHeight(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return 0;
	else
	{
		int lefth = GetHeight(root->leftpart);
		int righth = GetHeight(root->rightpart);
		if (lefth > righth)
			return ++lefth;
		else
			return ++righth;
	}
}

template <class T>
int BinaryTree<T> ::GetNodesNum(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return 0;
	else
	{
		int n = 1;
		int lefth = GetNodesNum(root->leftpart);
		int righth = GetNodesNum(root->rightpart);
		n += (lefth + righth);
		return n;
	}
}

template <class T>
BinaryTreeNode<T>* BinaryTree<T>:: CreateByPreorIn(const T* preorder, const T* midorder, int length) 
{
	int num = 0;
	if (length == 0)
		return NULL;	
	while (preorder[0] != midorder[num])
		num++;
	BinaryTreeNode<T>* p = new BinaryTreeNode<T>();
	p->data = preorder[0];
	p->leftpart = CreateByPreorIn(preorder + 1, midorder, num);
	p->rightpart = CreateByPreorIn(preorder + num + 1, midorder + num + 1, length - num - 1);
	root = p;
	size = length;
	return p;
}

int main()
{
	int num = 0;
	BinaryTree<char> theTree;
	BinaryTree<char> input;
	cout << "Input1" << endl;
	string str;
	string str1;
	string str2;
	getline(cin, str);
	cout << "Output1" << endl;
	theTree.CreateL(str.length(), str.data());
	theTree.preOrder(theTree.GetRoot());
	op = 1;
	cout << endl;
	theTree.midOrder(theTree.GetRoot());
	op = 1;
	cout << endl;
	theTree.backOrder(theTree.GetRoot());
	cout << endl;
	num = theTree.GetNodesNum(theTree.GetRoot());
	cout << num << endl;
	num = theTree.GetHeight(theTree.GetRoot());
	cout << num << endl;
	cout << "Input2" << endl;
	getline(cin, str1);
	getline(cin, str2);
	op = 1;
	input.CreateByPreorIn(str1.data(), str2.data(), str1.length());
	cout << "Output2" << endl;
	input.backOrder(input.GetRoot());
	op = 1;
	cout << endl;
	input.LevelOrder(input.GetRoot());
	op = 0;
	cout << endl;
	cout << "End0";
	return 0;
}
