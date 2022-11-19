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

int search(int a, SimPointer* s)           //һ���ȼ�����ں�������������ȽϺϲ��ĵȼ���Ԫ�ص�next����ָ��ԭ�����е�ĳһԪ�أ�����1��2�ȼ���
{                                                             //1��nextָ��2���൱��2������㣩������Ԫ�ز�������1����2�Ƚϣ���next����ָ��2����Ϊֻ��2��nextΪ0��
    int i = a;                                            //����2��count���ǵȼ����е�Ԫ������
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

void output(SimPointer* s, int n)        //�������c�еĵȼ��࣬ nΪԪ�صĸ���
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
//������ģ��ָ�������ʵ���ϲ�û��ָ�룬��������֮��������һ�������������ص����ڰ���һ��Ԫ�ط���next
//�Ƚ�1��2�Ƿ�ȼۣ����ȼ�����Խ�1��next��Ϊ2��ͬʱ�ټ����Ƚϱ���1��3����ʱҪ��3����1�ȼ��࣬���԰�3��Ϊ2��next���Դ�����ģ��ָ��ָ����һ��
