#include "Myint2type.h"
#include <iostream>
namespace Myint2type {
	using namespace std;
	template<int n>
	class anyclass1 {
		static constexpr int value = n;
		/*
		constexpr외에도 아레처럼 enum을 사용할 수 도 있으나, 위가 더 간결함.
		enum {
			value = n
		};
		*/
	};
	void anywork1(anyclass1<1> value) {
		cout << "1 function" << endl;
	}
	void anywork1(anyclass1<2> value) {
		cout << "2 function" << endl;
	}
	void case1() {
		//int2type
		//컴파일 타임 정수형 상수를 각각의 독립된 타입으로 만드는 기술
		anyclass1<1> c1;
		anyclass1<2> c2;

		anywork1(c1);
		anywork1(c2);

	}
	template<typename t,t v>
	class anyclass2{
	public:
		using valueType = t;
		static constexpr valueType value = v;
		
		// valueType으로 캐스팅 시 호출되는 변환 연산자.
		operator valueType() {
			return v;
		}
		valueType operator()(){
			return v;
		}

		/* int로 캐스팅 시 호출되는 변환 연산자의 또 다른 예.
		operator int() {
			return 1;
		}
		*/
	};

	void case2() {
		//integral_constant
		//int2type을 확대하여 정적 상수를 타입으로 만들 수 있게 하는 템플릿
		anyclass2<int, 1> c;
		// c++20 부터는 템플릿 인자가 비유형 인수(double, class 같은)도 사용 가능하다.
		// c++20 전 컴파일러는 아레 double이 사용 불가.
		// anyclass2<double, 2.0> c1;
		cout << c << endl;
		cout << c() << endl;
	}

	void main() {
		//case1();
		case2();
	}

}