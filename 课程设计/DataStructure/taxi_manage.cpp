#include "taxi_manage.h"

int main()
{
	int num;
	map<string, list<taxi>> ta;

	cout << "�뿪ʼ���⳵����ϵͳ�ĳ�ʼ��" << endl;
	cout << "��������⳵�ͺ��� ";
	cin >> num;
	for (int i = 0;i < num;i++)
	{
		int nums,costs,forfeits;
		string s;
		cout << "��������⳵���������������������𻵷��� ";
		cin >> s >> nums >> costs >> forfeits;

		list<taxi> l_list;
		for (int i = 0;i < nums;i++)
		{
			taxi t;
			t.id = i;
			t.type = s;
			t.status = 1;
			t.cost = costs;
			t.forfeit = forfeits;

			l_list.push_back(t);
		}
		ta[s] = l_list;
	}
	taxi_manage t_manage(ta);

	cout << "\n��ѡ������Ҫ����(���� t ����)�� " << endl;
	cout << "�⳵���� 1" << endl;
	cout << "�������� 2" << endl;
	cout << "��ѯ���� 3" << endl;
	cout << "ά������ 4" << endl<<endl;

	int k;
	while (cin >> k)
	{
		if (k == 1)
		{
			t_manage.print_type();
			cout << "\n�������������������賵������" << endl;
			string n, t;
			vector<int> d(3);
			cin >> n >> t;
			cout << "�������������(�꣬�£���)" << endl;
			cin >> d[0] >> d[1] >> d[2];

			t_manage.rent_car(n, t, d);
		}
		else if (k == 2)
		{
			cout << "�����������������кż�����" << endl;
			int i;
			bool s;
			string t;
			cin >> i >> t;
			cout << "���⳵�Ƿ��𻵣�������0��δ������1��" << endl;
			cin >> s;
			t_manage.return_car(i, t, s);
		}
		else if (k == 3)
		{
			t_manage.enquiries();
		}
		else if (k == 4)
		{
			t_manage.service();
		}
		else
		{
			cout << "��������,������" << endl;
		}

		cout << "\n��ѡ����һ������(���� t ����) " << endl;
	}
}