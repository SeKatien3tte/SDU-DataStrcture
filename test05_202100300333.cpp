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

//��Ҫ������calculate���ж�������ţ�calculating��ִ�г�ջ����������ջ
//����˼·������������ջ�����ջ�ڼ��ţ��µ��ǼӺŻ��߼��ţ�����ų�ջֱ�������·�����ջ
//�����ջ�Ƕ������� �µ��ǵ�һ�����㣬����������ջ���·�����ջ
//���ڻ���������ջ�ķ��ţ�����ÿ����ջ����������񶼵���ɨ��һ������+***/-,��Ҫһֱѭ�������еĶ���������Ŷ���ջ
// Ŀǰ��bug�Ƕ�λ����ɨ����bug
//���⣬ƽ̨�����������Ǹ��˲�
