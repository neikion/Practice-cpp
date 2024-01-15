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
		anyclass():localvalue(0) {}
		anyclass(int value) :localvalue(value) {}
		anyclass(const anyclass& value) {
			cout << "call copy constructor " << endl;
			this->localvalue = value.localvalue;
		}

		/// <summary>
		/// 비상수 함수
		/// </summary>
		void anyfunc(int value) {
			cout << "int data" << value + localvalue << endl;
		}

		/// <summary>
		/// 상수 함수
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
		
		//멤버 함수의 경우에는 위 코드처럼 함수 이름이 함수의 주소값으로 암시적 변환이 되지 않음.(c++ 언어 규칙)
		//그러므로 &를 통해 명시적으로 주소값을 전달해야함.
		//anyclass 옆의 &가 붙는 이유는 클래스의 복사본을 만들고 실행하지 않도록, 클래스를 참조로 전달하여 실행하기 위함.
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
		
		//auto 변수에 경우 해당되는 인자 이외에는 모두 무시된다.
		auto func2 = bind(anyfunc2, placeholders::_1, 2);
		func2(3,4,5);

		//placeholders의 숫자는 파라미터의 순서에 대응한다.
		auto func3 = bind(anyfunc3, placeholders::_2, placeholders::_1);
		func3(1, 2);

	}

	void anyfunc4(anyclass& c1, const anyclass& c2) {
		c1.localvalue = c2.localvalue;
	}

	void case3() {
		anyclass c1{1}, c2{ 5 };
		auto func1 = bind(anyfunc4, c1, placeholders::_1);
		func1(c2);
		//c1의 복사된 객체가 전달되어 함수가 실행됨.
		//그래서 아레 c1을 출력하는 코드는 변경이 되지 않음.
		cout << c1.localvalue << endl<<endl;

		//reference_wrapper를 이용하여 c1도 변경될 수 있게할 수 있음.
		auto func2 = bind(anyfunc4, std::ref(c1), placeholders::_1);
		func2(c2);
		cout << c1.localvalue << endl;
	}
}