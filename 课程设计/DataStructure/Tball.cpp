 #include "Tball.h"

int main()
{
    Tball test1, test2;
    
    cout << " >> << ��������ز��� " << endl;
    
    cin >> test1;
    cout << test1;

    Tball test3(1, 2, 3, 4);

    cout << "\n = ��������ز���" << endl;

    cout << test3;
    test2 = test3;
    cout << test2;

    cout << "\n �����������������������" << endl;

    test3.print();
    cout << "�������Ϊ�� " << test3.volume() << endl;
    cout << "��������Ϊ�� " << test3.area() << endl;

    return 0;
}