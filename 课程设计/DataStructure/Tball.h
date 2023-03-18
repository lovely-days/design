#ifndef TBALL_H
#define TBALL_H


#include <iostream>
using namespace std;

const double PI = 3.14159;

struct Tpoint
{
	double x,y,z;

	Tpoint():x(0), y(0), z(0){}
	Tpoint(double x0, double y0, double z0) :x(x0), y(y0), z(z0){}
};


class Tball
{
public:

	Tball() :center(), radius(0){}
	Tball(double x, double y, double z, double r) :center(x, y, z), radius(r){}
	~Tball(){}

	Tball(Tball& m)
	{
		center.x = m.center.x;
		center.y = m.center.y;
		center.z = m.center.z;
		radius = m.radius;

	}
	Tball& operator=(Tball& m)
	{
		center.x = m.center.x;
		center.y = m.center.y;
		center.z = m.center.z;
		radius = m.radius;
		return *this;
	}

	double volume()
	{
		return 4 * PI * radius * radius * radius / 3;
	}
	double area()
	{
		return 4 * PI * radius * radius;
	}
	void print()
	{
		cout << "�������Ϊ�� �� " << center.x << "," << center.y << "," << center.z << " )" << endl;
		cout << "��İ뾶Ϊ�� " << radius << endl;
	}

	friend ostream& operator<< (ostream& os, Tball& m)
	{
		os << "�������Ϊ�� �� " << m.center.x << "," << m.center.y << "," << m.center.z << " )" << endl;
		os << "��İ뾶Ϊ�� " << m.radius << endl;

		return os;
	}
	friend istream& operator>> (istream& is, Tball& m)
	{
		cout << "�������������ĵ���ά���꼰��뾶" << endl;
		double x, y, z, r;
		cin >> x >> y >> z >> r;
		m.center.x=x;
		m.center.y=y;
		m.center.z=z;
		m.radius=r;

		return is;
	}

private:
	Tpoint center;
	double radius;
};


#endif