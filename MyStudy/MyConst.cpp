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
		//const로 인수를 받는 경우 실제 파라미터가 const가 아니라면 아레와 같이 값이 변경되는 경우가 생길 수 있다.
		int num = 1;
		anyfunc1(num, num);
		cout <<"결과 값 " << num << endl;
	}
}