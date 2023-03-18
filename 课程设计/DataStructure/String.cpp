#include"String.h"
using namespace std;

int main()
{
	const char* p = "hello ";
	const char* q = "Stephen Curry of Golden State Warriors ";
	String test;
	String test1(p);
	String test2(q);

	cout << "�ַ���1Ϊ�� " << test1 << "�䳤��Ϊ:" << test1.Length() << endl;
	cout << "�ַ���2Ϊ�� " << test2 << "�䳤��Ϊ:" << test2.Length() << endl << endl;

	cout << "�ַ���1�и��ַ�����Ƶ��Ϊ��" << endl;
	test1.frequency();
	cout << "�ַ���2�и��ַ�����Ƶ��Ϊ��" << endl;
	test2.frequency();

	cout << "���ַ���2�������ַ���1��" << endl;
	test1 += test2;

	cout << "���Ӻ��ַ���1Ϊ�� " << test1 << "�䳤��Ϊ:" << test1.Length() << endl;

	cout << "\n���غ�[]���������" << endl << endl;

	cout << "�ַ���1�е�4��Ԫ��Ϊ�� " << test1[3] << endl;
	cout << "�ַ���2�е�5��Ԫ��Ϊ�� " << test2[4] << endl;

	cout << "\n���غ�ֵ���������" << endl << endl;

	test = test1;
	cout << test << endl;

	cout << "\n���غ����ϵ���������" << endl << endl;

	cout << (test1 == test2) << " " << (test1 != test2)<<" "<< !test1 << endl;

	cout << "\n�ַ���ƥ�����" << endl << endl;

	const char* r = "Curry";
	String find(r);
	cout << test1.Find(find, 2) << endl;

	return 0;
}