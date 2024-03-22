#include "Myint2type.h"
#include <iostream>
namespace Myint2type {
	using namespace std;
	template<int n>
	class anyclass1 {
		static constexpr int value = n;
		/*
		constexpr�ܿ��� �Ʒ�ó�� enum�� ����� �� �� ������, ���� �� ������.
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
		//������ Ÿ�� ������ ����� ������ ������ Ÿ������ ����� ���
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
		
		// valueType���� ĳ���� �� ȣ��Ǵ� ��ȯ ������.
		operator valueType() {
			return v;
		}
		valueType operator()(){
			return v;
		}

		/* int�� ĳ���� �� ȣ��Ǵ� ��ȯ �������� �� �ٸ� ��.
		operator int() {
			return 1;
		}
		*/
	};

	void case2() {
		//integral_constant
		//int2type�� Ȯ���Ͽ� ���� ����� Ÿ������ ���� �� �ְ� �ϴ� ���ø�
		anyclass2<int, 1> c;
		// c++20 ���ʹ� ���ø� ���ڰ� ������ �μ�(double, class ����)�� ��� �����ϴ�.
		// c++20 �� �����Ϸ��� �Ʒ� double�� ��� �Ұ�.
		// anyclass2<double, 2.0> c1;
		cout << c << endl;
		cout << c() << endl;
	}

	void main() {
		//case1();
		case2();
	}

}