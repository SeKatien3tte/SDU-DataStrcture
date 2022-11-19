#include <iostream>
#include <string>

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

template <class T>
class linkStack
{
public:
	linkStack()
	{
		stackFirst = NULL; stackLength = 0;
	}
	~linkStack();
	void push(const T& data)
	{
		stackFirst = new chainNode<T>(data, stackFirst);
		stackLength++;
	}
	T& GetTop() { return stackFirst->element; }
	void delete2()
	{
		chainNode<T>* p = stackFirst->next;
		delete stackFirst;
		stackFirst = p;
		stackLength--;
	}
	void calculating(int);
	void calculate(char& );
	chainNode<T>* stackFirst;
	int stackLength;
};

template<class T>
linkStack<T>::~linkStack()
{
	if (stackFirst != NULL)
	{
		chainNode<T>* Next = stackFirst->next;
		delete stackFirst;
		stackFirst = Next;
	}
}

void linkStack<int>:: calculating(int number)
{
	delete2();
	delete2();
	push(number);
}

void linkStack<int> :: calculate(char& x)
{
	int n;
	if (stackLength == 1)
		return;
	switch (x)
	{
	case '+':
		n = stackFirst->next->element + stackFirst->element;
		calculating(n);
		break;
	case '-':
		n = stackFirst->next->element - stackFirst->element;
		calculating(n);
		break;
	case '*':
		n = stackFirst->next->element * stackFirst->element;
		calculating(n);
		break;
	case '/':
		n = stackFirst->next->element / stackFirst->element;
		calculating(n);
		break;
	}
}

int main()
{
	int r;
	int n;
	linkStack<int> num; linkStack<char> op;
	string str;
	cout << "Input" << endl;
	getline(cin, str);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(') {
			op.push(str[i]);
		}
		else if (str[i] >= '0' && str[i] <= '9') {
			num.push(str[i] - '0');
		}
		else if (str[i] == ')') {
			while (op.stackFirst != NULL && op.stackFirst->element != '(') {
				num.calculate(op.GetTop());
				op.delete2();
			}
			op.delete2();
		}
		else {
			while (op.stackFirst != NULL && (op.stackFirst->element == '*' || op.stackFirst->element == '/') && (str[i] == '+' || str[i] == '-'))
			{
				num.calculate(op.GetTop());
				op.delete2();
			}
			while (op.stackFirst != NULL && op.stackFirst->element == '-' && (str[i] == '+' || str[i] == '-')) {
				num.calculate(op.GetTop());
				op.delete2();
			}
			op.push(str[i]);
		}
	}

	while (num.stackLength != 1)
	{
		num.calculate(op.GetTop());
		op.delete2();
	}
	cout << "Output" << endl;
	cout << num.stackFirst->element << endl;
	cout << "End";
	return 0;
}

//主要方法：calculate，判断运算符号，calculating，执行出栈运算与结果入栈
//基本思路：数字依次入栈。如果栈内减号，新的是加号或者减号，则减号出栈直接运算新符号入栈
//如果入栈是二级运算 新的是低一级运算，则二级运算出栈，新符号入栈
//由于会有连续入栈的符号，所以每次入栈进行运算与否都得再扫描一次例如+***/-,需要一直循环把所有的二级运算符号都出栈
// 目前的bug是多位数字扫描有bug
//另外，平台开发者你真是个人才
