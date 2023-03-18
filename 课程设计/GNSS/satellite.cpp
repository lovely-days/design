#include<regex>
#include<fstream>
#include<iostream>
#include<iomanip>

#include<vector>
#include<string>
#include<cmath>

using namespace std;

const double U = 3.986004418e+14;		// ������������
const double E = 7.292115e-5;			// ����ƽ�����ٶ�
const double C = 299792458;				// ����
const double PI = 3.14159265;			// Բ����

// ʱ��ṹ
struct Time
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	double second;

	Time(int y, int m, int d, int h, int min, int s):year(y),month(m),day(d),hour(h),min(min),second(s){}
};

// ÿһ�������
int year_days(int year)
{
	int count = 0;
	if (year == 1980)	count = 360;													// ���� 1980 ��Ļ��������㷨 360 ��
	else if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))	count = 366;	// �������꣬�� 1 ���� 366 ��
	else	count = 365;																// ��ƽ���꣬�� 1 ���� 365 ��
	return count;
}

// ÿ���µ�����
int month_days(int year, int month)
{
	int count = 0;																			// �洢ÿ���µ�����
	if (year == 1980 && month == 1) count = 25;												// �����㷨��1980 �� 1 ������ 25 ��
	else if (month == 4 || month == 6 || month == 9 || month == 11) count = 30;				// �����Ŷ� 30 ��
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) count = 31;
	else
	{
		if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))	count = 29;			// �������꣬�� 2 ���� 29 ��
		else count = 28;
	}
	return count;
}

// GPS������
long double get_seconds(Time& t)
{											
	int days = t.day;
	for (int i = 1980; i < t.year; i++)	days += year_days(i);							// ����������
	for (int i = 1; i < t.month; i++)	days += month_days(t.year, i);					// ����������
	return (days % 7) * 86400 + (t.hour * 3600) + (t.min * 60) + t.second;
}

// �滯ʱ��
long double t_k(Time& t, long double toe)
{
	long double ts = get_seconds(t) - toe;
	if (ts > 302400)
	{
		ts -= 604800;
	}
	if (ts < -302400)
	{
		ts += 604800;
	}
	return ts;
}

// ƽ�����
long double m_k(long double m0, long double n, long double tk)
{
	long double mk = m0 + (n * tk);
	while (mk < 0)
	{
		mk += 2 * PI;
	}
	while (mk > 0)
	{
		mk -= 2 * PI;
	}
	return mk;
}

// ƫ�����
long double e_k(long double mk, long double e)
{
	long double ek = mk;									//	ƫ�����	ek
	long double temp = 0;
	while (fabs(ek - temp) > 0.10e-12)
	{
		temp = ek;
		ek = mk + (e * sin(temp));
	}
	return ek;
}

// ������
long double Nu_k(long double ek, long double e)
{
	long double cos_Nuk = (cos(ek) - e) / (1 - e * cos(ek));
	long double sin_Nuk = (sqrt(1 - pow(e, 2)) * sin(ek)) / (1 - e * cos(ek));
	long double Nuk;
	if (cos_Nuk == 0)
	{
		Nuk = sin_Nuk > 0 ? PI / 2 : -PI / 2;
	}
	else
	{
		Nuk = atan(sin_Nuk / cos_Nuk);
	}

	if (cos_Nuk < 0)
	{
		Nuk += sin_Nuk > 0 ? PI : -PI;
	}
	return Nuk;
}

// ��������
void data_input(string ifile, vector<vector<long double>>& vt)
{
	ifstream infile;
	infile.open(ifile);
	if (!infile.is_open())
	{
		cout << "File " << ifile << " opening failed!! " << endl;
	}

	string s;
	int i = 0;
	smatch data_match;
	vector<long double> vi;

	regex segment("\^([ ]|\\d){20}[.]\\d");
	regex segment_time("(\\d{1,2}[.]\\d{1,2})|(\\d{1,2})");
	regex pattern("[+-| ]\\d[.]\\d{12}[D][+-]\\d{2}");

	while (getline(infile, s))
	{
		//if (vt.size() > 100) { break; }
		if (regex_search(s, data_match, segment))
		{
			string s_time = data_match.str();
			vt.push_back(vi);
			vi.clear();

			while (regex_search(s_time, data_match, segment_time))		//ƥ��������ż�ʱ����Ϣ
			{
				vi.push_back(stold(data_match.str()));
				//cout << data_match.str() << " ";
				s_time = data_match.suffix();
			}

			while (regex_search(s, data_match, pattern))				//ƥ������������Ϣ
			{
				vi.push_back(stold(data_match.str().substr(0, 14)) * pow(10, stold(data_match.str().substr(16, 18))));
				//cout << data_match.str() << " ";
				s = data_match.suffix();
			}

		}
		while (regex_search(s, data_match, pattern))					//ƥ������������Ϣ
		{
			vi.push_back(stold(data_match.str().substr(0, 14)) * pow(10, stold(data_match.str().substr(16, 18))));
			//cout << data_match.str() << " ";
			s = data_match.suffix();
		}

	}

	vt.push_back(vi);
	infile.close();
}

// ���ݼ��㼰���
void data_process(vector<long double> &data, ofstream& os)
{
	// �꣬�£��գ�ʱ���֣���

	int satellites_num = data[0];
	int year = data[1] + 2000;
	int month = data[2];
	int day=data[3];
	int hour = data[4];
	int min = data[5];
	double second = data[6];


	long double af0 = data[7];							// �����Ӳ�
	long double af1 = data[8];							// ��������
	long double af2 = data[9];                          // �������ٱ���

	long double IODE = data[10];						// ��������
	long double Crs = data[11];							// ����뾶���ҵ�������������
	long double a_poor = data[12];						// ƽ�����ٶ�֮��
	long double m0 = data[13];							// ƽ�����

	long double Cuc = data[14];							// γ�ȷ��ǵ����ҵ�������������
	long double e = data[15];							// ���ƫ����
	long double Cus = data[16];							// γ�ȷ��ǵ����ҵ�������������
	long double sqrtA = data[17];						// ������뾶��ƽ����

	long double toe = data[18];							// ��������Ĳο�ʱ��
	long double Cic = data[19];							// �����ǵ����ҵ�������������
	long double Ra0 = data[20];							// ������ྭ
	long double Cis = data[21];							// �����ǵ����ҵ�������������

	long double i0 = data[22];							// ������
	long double Crc = data[23];							// ����뾶�����ҵ�������������
	long double w = data[24];							// ���ص�Ǿ�
	long double Ra = data[25];							// ������ྭ�仯��

	long double idot = data[26];						// ��Ǳ仯��
	long double L2 = data[27];							// L2�ϵ���
	long double g_week = data[28];						// GPS ����
	long double L2P = data[29];							// L2�ϵ�P��

	long double acc = data[30];							// ���Ǿ���
	long double state = data[31];						// ����״̬
	long double Tgd = data[32];							// �����ʱ�ӳٲ�
	long double IODC = data[33];						// ���ӵ���������

	long double s_time = data[34];						// ���ķ���ʱ��
	long double f_val = data[35];						// �������

	Time t(year, month, day, hour, min, second);
	//cout <<year_days(year)<<" "<<month_days(year,month)<<" "<<get_seconds(t) << " " << toe << endl;

	//����

	long double n = (sqrt(U / pow(sqrtA, 3)) + a_poor) * pow(10, -6);		//	У�����ƽ�����ٶ� n
	long double tk = t_k(t, toe);											//	�滯ʱ�� tk
	long double mk = m_k(m0, n, tk);										//	ƽ����� mk
	long double ek = e_k(mk, e);											//	ƫ�����	ek
	long double Nuk = Nu_k(ek, e);											//  ������ Nuk
	long double Phik = Nuk + w;												//  ������Ǿ� Phik
	long double r0 = pow(sqrtA, 2) * (1 - e * cos(ek));						//  r0
	long double uk = (Cuc * cos(2 * Phik)) + (Cus * sin(2 * Phik)) + Phik;						//  �㶯У����������Ǿ� u_k
	long double rk = (Crc * cos(2 * Phik)) + (Crs * sin(2 * Phik)) + r0;						//  �㶯������ʸ������ r_k
	long double ik = (Cic * cos(2 * Phik)) + (Cis * sin(2 * Phik)) + i0 + idot * tk;			//  �㶯������� i_k

	long double xk = rk * cos(uk);																//  ƽ��ֱ������ϵ�е�����
	long double yk = rk * sin(uk);
	long double zk = 0;
	long double Rak = Ra0 + (Ra - E) * tk - E * toe;											//  ������ྭ Rak

	long double Xk = xk * cos(Rak) - yk * cos(ik) * sin(Rak);									//  WGS84����ϵ����������
	long double Yk = xk * sin(Rak) + yk * cos(ik) * cos(Rak);
	long double Zk = yk * sin(ik);

	long double F = -2 * sqrt(U) / pow(C, 2);													//  ���� F
	long double dtr = F * e * sqrtA * sin(ek);													//  ����������� dtr
	long double Tk = af0 + af1 * tk + af2 * pow(tk, 2) + dtr;									//  �����Ӳ� Tk
	long double dts = af1 + 2 * af2 * tk + F * e * sqrtA * cos(ek);								//  ������Ư dts

	//���

	os << fixed << setprecision(8) << "PG" << satellites_num << " " << year << "/" << month << "/" << day << " " << hour << ":" << min << ":" << second
		<< " " << Xk / 1000 << " " << Yk / 1000 << " " << Zk / 1000 << " " << Tk * pow(10, 6) << endl;
	
}

// ���ݹ㲥������������λ�ã��Ӳ��Ư
void satellite(string ifile, string ofile)
{
	vector<vector<long  double>> vt;

	data_input(ifile, vt);

	ofstream outfile;
	outfile.open(ofile);
	if (!outfile.is_open())
	{
		cout << "File " << ofile << " opening failed!! " << endl;
	}

	outfile << "nums  year/month/day  hour:min:second  X  Y  Z  T" << endl;		//

	for (int i = 1;i < vt.size();i++)
	{
		data_process(vt[i], outfile);
	}

	outfile.close();
}


int main()
{
	//string ifile = "C:\\Users\\Ok\\Desktop\\brdc2850.20n";
	//string ofile = "C:\\Users\\Ok\\Desktop\\GPS5.txt";

	for (int i = 1;i < 12;i++)
	{
		string ifile = "C:\\Users\\Ok\\Desktop\\�γ��ļ�\\GNSS\\�㲥��������\\brdc\\brdc" + to_string(2800 + 10 * (i + 3)) + ".20n";
		string ofile = "C:\\Users\\Ok\\Desktop\\�γ��ļ�\\GNSS\\�㲥��������\\position\\GPS" + to_string(i)+".txt";
		satellite(ifile, ofile);
		cout << "file GPS" << i << " running successful!!" << endl;
	}
	//satellite(ifile, ofile);

	return 0;
}