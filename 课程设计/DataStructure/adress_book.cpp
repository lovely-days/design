
#include "address_book.h"

int main()
{
	int m,n;
	address_book a_book;

	int id, relation;
	string name, number;

	cout << "�뽨��ͨѶ��" << endl << endl;
	cout << "������ͨѶ�������� 0 " << endl;
	cout << "���ļ�����ͨѶ������ 1 " << endl;
	cout << "���������ݽ���ͨѶ������ 2 " << endl;

	cin >> m;

	if (m==0){}
	else if(m==1)
	{
		string filename;
		cout << "�������ļ���ַ" << endl;
		cout << "�ļ���ʽ����һ��Ϊ���ݸ�����������ÿ��Ϊһ�����ݣ����ݸ����ţ���������ϵ�������������У��Կո�ָ�" << endl;
		cin >> filename;
		address_book a_b(filename);
		a_book = a_b;
	}
	else if(m==2)
	{
		int count;
		vector<contact> s;
		cout << "������ͨѶ�����ݸ���" << endl;
		cin >> count;
		cout << "������������ţ���������ϵ�� 1Ϊ�����ˡ���2Ϊ�����ѡ���3Ϊ��ͬ�¡� �����绰����" << endl;
		for (int i = 0;i < count;i++)
		{
			cout << "������� " << i + 1 << " ����ϵ��" << endl;
			cin >> id >> name >> relation >> number;
			contact c(id, name, relation, number);
			s.push_back(c);
		}
		address_book a_b(s);
		a_book = a_b;
	}
	else
	{
		cout << "�������룬������ֹ" << endl;
		return 0;
	}

	cout << "��ѡ������Ҫ��ͨѶ������ (���� t �˳�)" << endl;
	cout << "��ѡ�������" << endl << endl;
	
	cout << "�������ϵ����Ϣ���� 0 " << endl;
	cout << "��ѯָ����ϵ�˺������� 1 " << endl;
	cout << "�޸�ָ����ϵ����Ϣ���� 2 " << endl;
	cout << "ɾ��ָ����ϵ����Ϣ���� 3" << endl;
	cout << "���ͬһ��ϵ��ϵ����Ϣ���� 4 " << endl;
	cout << "���������ϵ����Ϣ���� 5 " << endl;

	while (cin >> n)
	{
		if (n == 0)
		{
			cout << "��������������ϵ����ţ���������ϵ�� 1Ϊ�����ˡ���2Ϊ�����ѡ���3Ϊ��ͬ�¡� �����绰����" << endl;
			cin >> id >> name >> relation >> number;
			a_book.addition(id, name, relation, number);
		}
		else if (n == 1)
		{
			cout << "�����������ѯ��ϵ������" << endl;
			cin >> name;
			cout << a_book.Find(name) << endl;
		}
		else if (n == 2)
		{
			int k;
			cout << "�����������޸ĵ������ ���������� 0 ����ϵ������ 1 ��������޸����� 2��" << endl;
			cin >> k;
			if (k==0)
			{
				cout << "������ָ����ϵ���������޸ĺ����" << endl;
				cin >> name >> number;
				a_book.change(name, number);
			}
			else if(k==1)
			{
				cout << "������ָ����ϵ���������޸ĺ��ϵ" << endl;
				cin >> name >> relation;
				a_book.change(name, relation);
			}
			else if (k == 3)
			{
				cout << "������ָ����ϵ���������绰������޸ĺ��ϵ" << endl;
				cin >> name >>number>> relation;
				a_book.change(name, number);
				a_book.change(name, relation);
			}
			else
			{
				cout << "�������룬������" << endl;
				continue;
			}
		}
		else if (n == 3)
		{
			cout << "����������ɾ����ϵ������" << endl;
			cin >> name;
			a_book.remove(name);
		}
		else if (n == 4)
		{
			cout << "���������������ϵ��" << endl;
			cin >> relation;
			a_book.print(relation);
		}
		else if (n == 5)
		{
			a_book.print();
		}
		else
		{
			cout << "�������룬������"<<endl;
			continue;
		}
		
		cout << "��ѡ������Ҫ��ͨѶ������ (���� t �˳�)" << endl;

	}
	return 0;
}
