#include "MyConst.h"
#include <iostream>
using namespace std;
namespace MyConst {
	void anyfunc1(int& n1, const int& n2) {
		n1 = n2 * 2;
	}
	void Main() {
		case1();
	}
	void case1() {
		//const�� �μ��� �޴� ��� ���� �Ķ���Ͱ� const�� �ƴ϶�� �Ʒ��� ���� ���� ����Ǵ� ��찡 ���� �� �ִ�.
		int num = 1;
		anyfunc1(num, num);
		cout <<"��� �� " << num << endl;
	}
}