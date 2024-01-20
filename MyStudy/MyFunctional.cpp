#include "MyFunctional.h"
#include <functional>
#include <iostream>
namespace MyFunctional {
	using namespace std;
	void anyfunc1() {
		cout << "anywork"<<endl;
	}
	class anyclass {
	public:
		int localvalue = 0;
		anyclass():localvalue(0) {}
		anyclass(int value) :localvalue(value) {}
		anyclass(const anyclass& value) {
			cout << "call copy constructor " << endl;
			this->localvalue = value.localvalue;
		}
		anyclass& operator=(const anyclass& value) {
			localvalue = value.localvalue;
			return *this;
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

		anyclass(anyclass&& value) noexcept{
			cout << "call move constructor" << endl;
			this->localvalue = value.localvalue;
		}
	};

	void Main() {
		//case1();
		//case2();
		case3();
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
	void anyfunc3(int value1, int value2) {
		cout << "1st arg : " << value1 << " 2st arg : " << value2 << endl;
	}

	void case2() {
		function<void(int)> func1 = bind(anyfunc2,1, placeholders::_1);
		func1(2);
		
		//auto ������ ��� �ش�Ǵ� ���� �̿ܿ��� ��� ���õȴ�.
		auto func2 = bind(anyfunc2, placeholders::_1, 2);
		func2(3,4,5);

		//placeholders�� ���ڴ� �Ķ������ ������ �����Ѵ�.
		auto func3 = bind(anyfunc3, placeholders::_2, placeholders::_1);
		func3(1, 2);

	}

	void anyfunc4(anyclass& c1, const anyclass& c2) {
		c1.localvalue = c2.localvalue;

	}

	void case3() {
		anyclass c1{1}, c2{ 5 };
		const anyclass c3{ 10 };
		auto func1 = bind(anyfunc4, c1, placeholders::_1);
		func1(c2);
		//c1�� ����� ��ü�� ���޵Ǿ� �Լ��� �����.
		//�׷��� �Ʒ� c1�� ����ϴ� �ڵ�� ������ ���� ����.
		cout <<"��ü�� �� " << c1.localvalue << endl << endl;



		//reference_wrapper�� �̿��Ͽ� c1�� ����� �� �ְ��� �� ����.
		auto func2 = bind(anyfunc4, std::ref(c1), placeholders::_1);
		func2(c2);
		cout << "��ü�� �� " << c1.localvalue << endl<<endl;
		


		//�Ʒ� �ڵ�� �Լ� ȣ�� ������ ��ü ���¿� ���� ���� �޶����� �� �� ����.
		c2.localvalue = 5;
		auto func3 = bind(anyfunc4, placeholders::_1, std::ref(c2));
		c2.localvalue = 10;
		func3(c1);
		cout << "��ü�� �� " << c1.localvalue << endl<<endl;



		//��ü�� ���¿� ���� ���� �ٲ�� ���� ���� �ʹٸ� ��ü�� �����Ͽ� �����ϸ� ��.
		//������ �̴� ���� c2���� ������ ��ġ�� ����.
		c2.localvalue = 10;
		auto func4 = bind(anyfunc4, placeholders::_1, c2);
		c2.localvalue = 5;
		func3(c1);
		cout << "��ü�� �� " << c1.localvalue << endl;

		//std::cref�� const�� �����ϴ� reference wrapper�� ��ȯ��.
	}
	

}