#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

const int defaultSize = 128;

class String
{
public:
    String(int sz = defaultSize);
    String(const char* init);
    ~String();

    String(const String& ob);                       //���ƹ��캯��
    String& operator=(String& ob);                  //��ֵ���캯������

    int Length() const;                             //���ַ�������
    String& operator()(int pos, int len);           //��pos��len���ַ���ɵ��Ӵ�
    bool operator==(String& ob) const;
    bool operator!=(String& ob) const;
    bool operator!() const;                         //�ж��Ƿ�մ�
    String& operator+=(String& ob);                 //��δ����������ַ�������
    char& operator[](int i);                        //ȡ��i���ַ�
    int Find(String& pat, int k) const;             //�ӵ�k���ַ�������ַ���ƥ��
    void frequency();                               //ͳ���ַ����и��ַ�����Ƶ��

    //������������������

    friend ostream& operator<<(ostream& os, String& s)
    {
        for (int i = 0;i < s.Length();i++)
        {
            os << s[i];
        }
        return os;
    }
    friend istream& operator>>(istream& is, String& s)
    {
        char ch[100];
        cout << "�������ַ��� (С�� 100 ���ַ�)" << endl;
        is.getline(ch, 100);
        String str((const char*)ch);
        s = str;
        return is;
    }


private:
    char* ch;
    int curLength;
    int maxSize;
};

String::String(int sz)
{
    maxSize = sz;
    ch = new char[maxSize + 1];
    if (ch == nullptr)
    {
        cerr << "Allocation Error\n";
        exit(1);
    }
    curLength = 0;
    ch[0] = '\0';

}
String::String(const char* init)
{
    int len = strlen(init);
    maxSize = (len > defaultSize) ? len : defaultSize;
    ch = new char[maxSize + 1];
    if (ch == nullptr)
    {
        cerr << "Allocation Error\n";
        exit(1);
    }
    curLength = len;
    strcpy(ch, init);
}
String::~String() { delete[] ch; }

String::String(const String& ob)
{
    maxSize = ob.maxSize;
    ch = new char[maxSize + 1];
    if (ch == nullptr)
    {
        cerr << "Allocation Error\n";
        exit(1);
    }
    curLength = ob.curLength;
    strcpy(ch, ob.ch);
}
String& String::operator=(String& ob)
{
    if (&ob != this)
    {
        delete[] ch;
        ch = new char[ob.maxSize];
        if (ch == nullptr)
        {
            cerr << "Allocation Error\n";
            exit(1);
        }
        curLength = ob.curLength;
        strcpy(ch, ob.ch);
    }
    else
    {
        cout << "�ַ�������ֵ����\n";
    }
    return *this;
}

int String::Length() const
{
    return curLength;
}
String& String::operator()(int pos, int len)
{
    String temp;
    if (pos < 0 || pos + len - 1 >= maxSize || len < 0)
    {
        temp.curLength = 0;
        temp.ch[0] = '\0';
    }
    else
    {
        if (pos + len - 1 > curLength)
            len = curLength - pos;
        temp.curLength = len;
        for (int i = 0, j = pos; i < len;i++, j++)
            temp.ch[i] = ch[i];
        temp.ch[len] = '\0';
    }
    return temp;
}
bool String::operator==(String& ob) const
{
    return strcmp(ch, ob.ch) == 0;
}
bool String::operator!=(String& ob) const
{
    return strcmp(ch, ob.ch) != 0;
}
bool String::operator!() const
{
    return curLength == 0;
}
String& String::operator+=(String& ob)
{
    char* temp = ch;
    int n = curLength + ob.curLength;
    int m = (maxSize >= n) ? maxSize : n;
    ch = new char[m];
    if (ch == nullptr)
    {
        cerr << "�洢�������\n";
        exit(1);
    }
    maxSize = m;
    curLength = n;
    strcpy(ch, temp);
    strcat(ch, ob.ch);
    delete[] temp;
    return *this;
}
char& String::operator[](int i)
{
    if (i<0 || i>curLength)
    {
        cout << "�ַ����±곬�磡\n";
        exit(1);
    }
    return ch[i];
}
int String::Find(String& pat, int k) const
{
    int i, j;
    for (i = k; i < curLength - pat.curLength;i++)
    {
        for (j = 0; j < pat.curLength;j++)
        {
            if (ch[i + j] != pat.ch[j])
                break;
        }
        if (j == pat.curLength)
            return i;
    }
    return -1;
}
void String::frequency()
{
    map<char, int> m_count;
    String str=*this;

    for (int i = 0;i < str.Length();++i)
    {
        m_count[str[i]]++;
    }

    map<char, int>::iterator iter;
    for (iter = m_count.begin(); iter != m_count.end();++iter)
    {
        cout << "�ַ� " << iter->first << " ���� " << iter->second << " ��" << endl;
    }
    cout << endl;

}



#endif