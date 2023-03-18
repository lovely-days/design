#ifndef TAXI_MANAGE_H
#define TAXI_MANAGE_H

#include <list>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "interval_days.h"                           //��������֮����
using namespace std;


struct taxi
{
    int id;           //���⳵���
    string type;      //���⳵�ͺ�
    bool status;      //���⳵״̬ (1,0�ֱ������⳵���뻵)
    string name;      //�˿�����
    vector<int> date; //�������� (����ǰ����Ԫ�طֱ��ʾ�꣬�£���)
    int cost;         //������
    int forfeit;      //�𻵷���

};

class taxi_manage
{
public:
    taxi_manage(){}
    taxi_manage(map<string, list<taxi>>& l_list);

    taxi_manage(taxi_manage& rhs);                    //���ƹ��캯��
    taxi_manage operator=(taxi_manage& rhs);          //��ֵ���������

    void rent_car(string n, string t, vector<int> d); //�⳵
    void return_car(int i, string t, bool s);         //����
    void enquiries();                                 //��ѯ���⳵��Ϣ
    void service();                                   //���⳵ά��
    void print_type();                                //���ϵͳ���������ĳ��⳵����

private:
    map<string, list<taxi>> lend_list;                //ʹ��ɢ�н���ͬ���ͳ��⳵�����ڲ�ͬ�����дӶ�ʵ�ֿ��ٲ�ȡ
    list<taxi> rented_list;
};

taxi_manage::taxi_manage(map<string, list<taxi>>& l_list)
{
    lend_list = l_list;
}

taxi_manage::taxi_manage(taxi_manage& rhs)
{
    lend_list.clear();
    rented_list.clear();

    lend_list = rhs.lend_list;
    rented_list = rhs.rented_list;
}
taxi_manage taxi_manage::operator=(taxi_manage& rhs)
{
    lend_list.clear();
    rented_list.clear();

    lend_list = rhs.lend_list;
    rented_list = rhs.rented_list;
    return *this;
}

void taxi_manage::rent_car(string n, string t, vector<int> d)
{
    if (!lend_list.count(t))
    {
        cout << "��ָ�����⳵���ͣ�����������" << endl;
        return;
    }

    taxi r_taxi;
    r_taxi.date = d;
    r_taxi.name = n;
    r_taxi.type = t;
    r_taxi.status = 1;

    for (auto m = lend_list[t].begin(); m != lend_list[t].end(); m++)
    {
        if (m->status)
        {
            r_taxi.id = m->id;
            r_taxi.cost = m->cost;
            r_taxi.forfeit = m->forfeit;
            lend_list[t].erase(m);
            break;
        }
    }
    rented_list.push_back(r_taxi);

    cout << "�����⳵�������Ϊ�� " << r_taxi.id << endl;
}
void taxi_manage::return_car(int i, string t, bool s)
{
    taxi l_taxi;
    vector<int> old_date;
    int year, month, day;

    for (auto m = rented_list.begin(); m != rented_list.end(); m++)
    {
        if (m->id == i && m->type == t)
        {
            l_taxi.id = m->id;
            l_taxi.cost = m->cost;
            l_taxi.type = t;
            l_taxi.forfeit = m->forfeit;
            l_taxi.status = s;
            old_date = m->date;
            rented_list.erase(m);
            lend_list[t].push_back(l_taxi);
            break;
        }
    }

    if (l_taxi.cost == 0)
        cout << "�޴�������Ϣ������������Ϣ�Ƿ�����" << endl;
    
    cout << "�������������(�꣬�£���) " << endl;
    cin >> year >> month >> day;
    int days = caldays(old_date[0], old_date[1], old_date[2], year, month, day);
    cout << "������Ϊ: " << days * l_taxi.cost << endl;
    if (s == 0)
    {
        cout << "���⳵���𻵣������⳥���Ϊ�� " << l_taxi.forfeit << endl;
        cout << "�ܼƣ�" << (days * l_taxi.cost + l_taxi.forfeit) << " Ԫ" << endl;
    }
    else
    {
        cout << "�ܼƣ�" << days * l_taxi.cost << " Ԫ" << endl;
    }
}
void taxi_manage::enquiries()
{ 
    for (auto m = lend_list.begin(); m != lend_list.end(); m++)
    {
        int count = 0;
        int f_count = 0;
        int t_count = 0;
        for (auto n = m->second.begin(); n != m->second.end(); n++)
        {
            if (n->status == 0)
                f_count++;
            else
                t_count++;
        }
        cout << m->first << " ���ͳ��⳵ʣ�� " << f_count + t_count << " ��" << endl;
        cout << "������ " << f_count << " �� , "<< "��� " << t_count << " ��" << endl;
    }

    cout << "����Ϊ�ѳ�����������: " << endl;
    for (auto m = rented_list.begin(); m != rented_list.end(); m++)
    {
        cout << "���⳵��: " << m->id << " ���⳵����: " << m->type << " ����������: " << m->name
            << " �������ڣ� " << m->date[0] << " " << m->date[1] << " " << m->date[2] << endl;
    }
}
void taxi_manage::service()
{
    for (auto m = lend_list.begin(); m != lend_list.end(); m++)
    {
        int count = 0;
        for (auto n = m->second.begin(); n != m->second.end(); n++)
        {
            if (n->status == 0)
            {
                n->status = 1;
                count++;
            }
        }
        cout << m->first << " ���ͳ��⳵��" << count << "��" << endl;
    }
    cout << "�����𻵳��⳵��ά�����" << endl;
}
void taxi_manage::print_type()
{
    cout << "����Ϊ�����ó��⳵�嵥" << endl;
    for (auto m = lend_list.begin(); m != lend_list.end(); m++)
    {
        int t_count = 0;
        for (auto n = m->second.begin(); n != m->second.end(); n++)
        {
            if (n->status == 1)
                t_count++;
        }
        cout << m->first << " �ͳ��⳵  " << t_count << " ��"<<endl;
    }
}

#endif