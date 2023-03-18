#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//�����Ĳ���������غ���
namespace Quadtree
{
	template <typename T>
	struct Grid
	{
		T element;
		int count;			//��ʶ�ϲ�����

		Grid(T e) :element(e), count(0) {}
	};

	int digit2(int num)		//����ʮ������������λ��
	{
		int count = 0;
		while (num != 0)
		{
			num = num / 2;
			count++;
		}
		return count;
	}

	int min_Morton(int rows, int columns)			//�����������Ҫ��2^k*2^k������С k ֵ
	{
		int count = 0;
		int max_num = rows > columns ? rows : columns;

		while ((1 << count) < max_num)
		{
			count++;
		}
		return count;
	}

	template <typename T>
	bool count_judge(int row, int column, int i, vector<vector<Grid<T>>>& v)	//���ĸ�դ��ϲ�������Ϊi�����true
	{
		int num = v[row][column].count;
		bool b1 = v[row][column].count == i;
		bool b2 = v[row + (1 << num)][column].count == i;
		bool b3 = v[row][column + (1 << num)].count == i;
		bool b4 = v[row + (1 << num)][column + (1 << num)].count == i;
		return b1 && b2 && b3 && b4;

	}

	template <typename T>
	bool char_judge(int row, int column, vector<vector<Grid<T>>>& v)			//���ĸ��ַ���ͬ���true
	{
		int num = v[row][column].count;
		bool b1 = v[row][column].element == v[row + (1 << num)][column].element;
		bool b2 = v[row + (1 << num)][column].element == v[row][column + (1 << num)].element;
		bool b3 = v[row][column + (1 << num)].element == v[row + (1 << num)][column + (1 << num)].element;
		return b1 && b2 && b3;
	}

	template <typename T>
	int max_column_size(vector<vector<T>>& v)		//���������
	{
		int maxsize = 0;
		for (int i = 0;i < v.size();i++)
		{
			maxsize = maxsize > v[i].size() ? maxsize : v[i].size();
		}
		return maxsize;
	}

	int toM(int row, int column)		//�������кż����ӦMorton��
	{
		int digit = digit2(row > column ? row : column);
		//cout << digit << endl;
		int Morton = 0;
		for (int i = 0;i < digit;i++)
		{
			int m_r = (row & (1 << i)) << (i + 1);
			int m_c = (column & (1 << i)) << i;
			//cout<<"#"<<i<<" "<< m_r << " " << m_c << endl;
			Morton += m_r + m_c;
		}
		return Morton;
	}

	vector<int> toRC(int Morton)		//����Morton������Ӧ���кţ������������������Ϊ�кţ�����Ϊ�кţ�
	{
		vector<int> row_column;

		int digit = digit2(Morton);
		//cout << digit << endl;
		int row = 0;
		int column = 0;

		for (int i = 0;i < digit / 2 + 1;i++)
		{
			row += (Morton & (1 << (2 * i + 1))) >> (i + 1);
			column += (Morton & (1 << 2 * i)) >> i;
			//cout<<"#"<<i<<" "<< row << " " << column << endl;
		}

		row_column.push_back(row);
		row_column.push_back(column);

		return row_column;
	}
}		

using namespace Quadtree;

template <typename T>
class Geo_Encoding
{
private:
	vector<vector<T>> Data;

	void file_input(string filename)			//�ļ�����
	{
		ifstream infile;
		infile.open(filename);
		if (!infile.is_open())
		{
			cout << "open wrong!" << endl;
			return;
		}

		int rows, columns;
		infile >> rows >> columns;
		Data.resize(rows);

		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < columns;j++)
			{
				Data[i].resize(columns);
				infile >> Data[i][j];
				//cout << "Data[i][j]: " << Data[i][j] << " ";
			}
			//cout << endl;
		}

		infile.close();
	}
	void file_output(string filename)			//�ļ����
	{
		ofstream outfile;
		outfile.open(filename);
		if (!outfile.is_open())
		{
			cout << "open wrong!" << endl;
			return;
		}

		for (int i = 0;i < Data.size();i++)
		{
			outfile << "row #" << i << " columns= " << Data[i].size() << "   ";
			for (int j = 0;j < Data[i].size();j++)
			{
				outfile << Data[i][j] << " ";
				//cout << "Data[i][j]: " << Data[i][j] << " ";
			}
			outfile << endl;
			//cout << endl;
		}

		cout << "output successful !!" << endl;
		outfile.close();
	}

public:
	Geo_Encoding()
	{
		string filename;
		cout << "�����������ļ���" << endl;
		cin >> filename;

		file_input(filename);
	}
	Geo_Encoding(string &filename)
	{
		file_input(filename);
	}
	Geo_Encoding(vector<vector<T>> &v)
	{
		Data.resize(v.size());
		for (int i = 0;i < v.size();i++)
		{
			Data[i].resize(v[i].size());
			for (int j = 0;j < v[i].size();j++)
			{
				Data[i][j] = v[i][j];
				//cout << "Data[i][j]: " << Data[i][j] << " ";
			}
			//cout << endl;
		}
	}		

	//��ֵ��������ؼ����ƹ��캯��
	Geo_Encoding(Geo_Encoding& rhs)
	{
		*this = rhs;
	}
	Geo_Encoding& operator=(Geo_Encoding& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->Data = rhs.Data;
		return *this;
	}

	//�ļ������������
	void f_show(string filename)				//դ���ļ����
	{
		file_output(filename);
	}
	void c_show()								//դ����������
	{
		for (int i = 0;i < Data.size();i++)
		{
			cout << "row #" << i << " columns= " << Data[i].size() << "   ";
			for (int j = 0;j < Data[i].size();j++)
			{
				cout << Data[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	//�г̱���
	void RL_Encoding(string filename)
	{
		ofstream outfile;
		outfile.open(filename);
		if (!outfile.is_open())
		{
			cout << "open wrong!" << endl;
			return;
		}

		for (int i = 0;i < Data.size();i++)
		{
			int count = 0;
			T first_element = Data[i][0], other_element;

			for (int j = 0;j < Data[i].size();j++)
			{
				other_element = Data[i][j];

				if (other_element != first_element)
				{
					outfile << " (" << first_element << "," << count << ") ";
					first_element = other_element;
					count = 0;
				}
				count++;
			}
			outfile << " (" << first_element << "," << count << ") ";
			outfile << endl;
		}
		cout << "successful running !!" << endl;
		outfile.close();
	}			
	//�����Ĳ�������
	void Quadtree_Encoding(string filename)
	{
		ofstream outfile;
		outfile.open(filename);
		if (!outfile.is_open())
		{
			cout << "open wrong!" << endl;
			return;
		}

		int num = min_Morton(Data.size(), max_column_size(Data));		// 2^k*2^k kֵ
		vector<vector<Grid<T>>> Grid_Data(1 << num, vector<Grid<T>>(1 << num, '#'));

		//cout << num;

		for (int i = 0;i < Data.size();i++)
		{
			for (int j = 0;j < Data[i].size();j++)
			{
				Grid_Data[i][j].element = Data[i][j];
				//cout << "element: " << Grid_Data[i][j].element << " " << "count: " << Grid_Data[i][j].count << "  ";
			}
			//cout << endl;
		}

		for (int i = 0;i < num;i++)
		{
			//cout << i << endl;
			for (int j = 0;j < 1 << (2 * num);j += 4 << (2 * i))
			{
				int row = toRC(j)[0];
				int column = toRC(j)[1];

				//cout << "j: " << j << " " << "row: " << row << " " << "column " << column
					//<< " count: " << Grid_Data[row][column].count << " element: " << Grid_Data[row][column].element << endl; 

				if (!count_judge(row, column, i, Grid_Data))
				{
					continue;
				}

				if (char_judge(row, column, Grid_Data))
				{
					Grid_Data[row][column].count++;
				}
			}
		}

		int i = 0;
		while (i < 1 << (2 * num))
		{
			int row = toRC(i)[0];
			int column = toRC(i)[1];

			outfile << " Morton: " << i << " " << "value: " << Grid_Data[row][column].element << endl;
			i += 1 << (2 * Grid_Data[row][column].count);
		}
		cout << "successful running !!" << endl;
		outfile.close();
	}	   

};