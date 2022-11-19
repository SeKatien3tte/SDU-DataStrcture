#include <iostream>

using namespace std;

struct SimPointer
{
    int next;
    int count;
};

void Unite(int x, int y, SimPointer* s);
int search(int a, SimPointer* s);
void initial(int a, SimPointer* s);
void equiva(SimPointer* s, int n);
void output(SimPointer* s, int n);


int main()
{
    SimPointer s[20];
    int num;
    cout << "Input" << endl;
    cin >> num;
    equiva(s, num);                    
    cout << "Output" << endl;
    output(s, num);                
    cout << "End" << endl;
    return 0;
}

void Unite(int x, int y, SimPointer* s)     
{
    if (s[x].count > s[y].count)
    {
        s[y].next = x;
        s[x].count += s[y].count;
    }
    else
    {
        s[x].next = y;
        s[y].count += s[x].count;
    }
}

int search(int a, SimPointer* s)           //一个等价类存在后，所有其他与其比较合并的等价类元素的next都会指向原来类中的某一元素，例如1，2等价类
{                                                             //1的next指向2（相当于2作父结点），其他元素不论是与1还是2比较，其next都会指向2（因为只有2的next为0）
    int i = a;                                            //最终2的count就是等价类中的元素数量
    while (s[i].next)
        i = s[i].next;
    return i;
}

void initial(int a, SimPointer* s)        
{
    s[a].next = 0;
    s[a].count = 1;
}

void equiva(SimPointer* s, int n)         
{
    int r;
    cin >> r;
    int num, j, x, y, count;
    for (num = 1; num <= n; num++)
    {
        initial(num, s);
    }
    char c1, c2, c3;


    for (count = 0; count < r; count++)
    {
        cin >> c1 >> num >> c2 >> j >> c3;
        x = search(num, s);
        y = search(j, s);
        if (x != y)
            Unite(x, y, s);
    }
}

void output(SimPointer* s, int n)        //输出数组c中的等价类， n为元素的个数
{
    int a, b = 0, c[20], m, k;
    for (a = 1; a <= n; a++)
    {
        if (s[a].next == 0)
        {
            c[b++] = a;
        }
    }
    m = b;
    int count = 0;
    for (a = 0; a < m; a++)
    {
        int bottle[1000]{};
        cout << "(";
        for (b = 1; b <= n; b++)
        {
            if (c[a] == search(b, s))
                bottle[count++] = b;
        }
        for (k = 0; k < count - 1; k++) {
            cout << bottle[k] << ",";
        }
        cout << bottle[count - 1];
        cout << ")" << endl;
        count = 0;
    }
}
//本质是模拟指针操作，实际上并没有指针，我在数组之间假设存在一个链表，其连接重点在于把下一个元素放入next
//比较1和2是否等价，若等价则可以将1的next设为2，同时再继续比较比如1和3，这时要将3加入1等价类，可以把3设为2的next，以此类推模拟指针指向下一个
