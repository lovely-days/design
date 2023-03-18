#include"BinaryTree.h"
using namespace std;

int main()
{
	BinarySearchTree<int> test;
	cin >> test;
	//cout << test;
	
	cout << "\nǰ�����\n";
	test.pre_order();
	cout << "\n�������\n";
	test.in_order();
	cout << "\n�������\n";
	test.post_order();

	cout << "\n�������Ϊ�� " << test.depth();
	cout << "\n����Ҷ�ӽ����Ϊ�� " << test.leafcount();
	cout << "\n���Ľ����ΪΪ�� " << test.nodecount();

	cout << "\n�������ֵ: ";
	cout << test.findMax();
	cout << "\n������Сֵ: ";
	cout << test.findMin();

	cout << endl;
	cout << test.isEmpty();
	test.makeEmpty();
	cout << endl;
	cout << test.isEmpty();
	return 0;
}