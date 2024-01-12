#include "MyFunctional.h"
#include <functional>
#include <iostream>
#include<vector>
#include <algorithm>
namespace MyFunctional {
	using namespace std;
	void anyfunc1() {
		cout << "anywork"<<endl;
	}
	class anyclass {
	public:
		int localvalue = 0;
		anyclass():localvalue(0) {
			
		}
		anyclass(const anyclass& value) {
			cout << "copy" << endl;
			this->localvalue = value.localvalue;
		}

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		void anyfunc(int value) {
			cout << "int data" << value + localvalue << endl;
		}

		/// <summary>
		/// ��� �Լ�
		/// </summary>
		void anyconstfunc(int value) const {
			cout << "int data" << value + localvalue << endl;
		}
	};

	void Main() {
		//case1();
		case2();
	}

	void case1() {
		function<void()> work1 = anyfunc1;
		
		//��� �Լ��� ��쿡�� �� �ڵ�ó�� �Լ� �̸��� �Լ��� �ּҰ����� �Ͻ��� ��ȯ�� ���� ����.(c++ ��� ��Ģ)
		//�׷��Ƿ� &�� ���� ��������� �ּҰ��� �����ؾ���.
		//anyclass ���� &�� �ٴ� ������ Ŭ������ ���纻�� ����� �������� �ʵ���, Ŭ������ ������ �����Ͽ� �����ϱ� ����.
		function<void(anyclass&, int)> work2 = &anyclass::anyfunc;
		function<void(const anyclass&, int)> work3 = &anyclass::anyconstfunc;

		
		anyclass class1;
		class1.localvalue = 1;
		work1();
		work2(class1, 1);
		work3(class1, 2);
	}

	void anyfunc2(int value1, int value2) {
		cout << "sum result " << value1 + value2 << endl;
	}

	void case2() {
		function<void(int)> func1 = bind(anyfunc2,1, placeholders::_1);
		
		func1(2);

	}
}