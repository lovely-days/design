#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct contact
{
    int id;        //���
    string name;   //����
    int relation;  //��ϵ��1Ϊ�����ˡ���2Ϊ�����ѡ���3Ϊ��ͬ�¡���
    string number; //�绰����

    contact() : id(0), name("\0"), relation(0), number("\0") {}
    contact(int i, string na, int r, string nu) : id(i), name(na), relation(r), number(nu) {}
};

class address_book
{
public:
    address_book();
    address_book(vector<contact>& a);                       //�������齨��ͨѶ��
    address_book(string& file_name);                        //�����ļ����ݽ���ͨѶ��

    address_book(address_book& rhs);                        //���ƹ��캯��
    address_book operator=(address_book& rhs);              //��ֵ���������


    ~address_book() {}
    string Find(string& name);                              //��ѯ��ϵ��
    void addition(int i, string na, int r, string& nu);     //�����ϵ��
    void change(string& name, int r);                       //�޸���ϵ�˹�ϵ
    void change(string& name, string& nu);                  //�޸���ϵ�˵绰����
    void remove(string& name);                              //ɾ����ϵ��
    void print(int r);                                      //����ϵ�����ϵ��
    void print();                                           //���ȫ����ϵ��

private:
    vector<contact> address;
};

address_book::address_book() {}
address_book::address_book(vector<contact>& a) : address(a.size())
{
    for (int i = 0; i < a.size(); i++)
    {
        address[i].id = a[i].id;
        address[i].relation = a[i].relation;
        address[i].name = a[i].name;
        address[i].number = a[i].number;
    }
}
address_book::address_book(string& file_name)
{
    int address_nums;
    ifstream in_file(file_name);
    if (!in_file)
    {
        cout << "���ļ�ʧ��" << endl;
        return;
    }

    in_file >> address_nums;
    if (!address.empty())
    {
        address.clear();
    }
    for (int i = 0; i < address_nums; i++)
    {
        int id, relation;
        string name, number;
        in_file >> id >> name >> relation >> number;
        contact m(id, name, relation, number);
        address.push_back(m);
    }
}

address_book::address_book(address_book& rhs)
{
    if (rhs.address.empty())
    {
        address.clear();
    }
    else
    {
        address = rhs.address;
    }
}
address_book address_book::operator=(address_book& rhs)
{
    if (rhs.address.empty())
    {
        address.clear();
        return *this;
    }
    else
    {
        address = rhs.address;
        return *this;
    }
}


string address_book::Find(string& name)
{
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i].name == name)
        {
            return address[i].number;
        }
    }
    cout << "δ�ҵ�" << endl;
    return string(0);
}
void address_book::addition(int i, string na, int r, string& nu)
{
    contact m(i, na, r, nu);
    address.push_back(m);
}
void address_book::change(string& name, int r)
{
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i].name == name)
        {
                address[i].relation = r;
                return;
        }
    }
    cout << "��ƥ����ϵ��" << endl;
}
void address_book::change(string& name, string& nu)
{
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i].name == name)
        {
            address[i].number = nu;
            return;
        }
    }
    cout << "��ƥ����ϵ��" << endl;
}
void address_book::remove(string& name)
{
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i].name == name)
        {
            address.erase(address.begin() + i);
            return;
        }
    }
    cout << "��ƥ����ϵ��" << endl;
}
void address_book::print(int r)
{
    string relation;
    switch (r)
    {
    case 1:
        relation = "����";
        break;
    case 2:
        relation = "����";
        break;
    case 3:
        relation = "ͬ��";
        break;
    default:
        cout << "��������" << endl;
        return;
    }

    for (int i = 0; i < address.size(); i++)
    {
        if (address[i].relation == r)
        {
            cout << address[i].id << " " << address[i].name << " " << relation << " " << address[i].number << endl;
        }
    }
}
void address_book::print()
{
    for (int i = 0; i < address.size(); i++)
    {
        cout << address[i].id << " " << address[i].name << " " << address[i].relation << " " << address[i].number << endl;
    }
}

#endif