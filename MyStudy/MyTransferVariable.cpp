#include"MyTransferVariable.h"
#include <iostream>
namespace TransferVariable {
	using namespace std;
	class anyclass1 {
	public:
		anyclass1() {
			cout << "default constructor\n";
		}
		anyclass1(const anyclass1& value) {
			cout << "copy constructor\n";
		}
		anyclass1(anyclass1&& value) noexcept {
			cout << "move constructor\n";
		}
		~anyclass1() {
			cout << "destructor\n";
		}
		anyclass1& operator=(const anyclass1& value) {
			cout << "copy value assignment\n";
		}
		anyclass1& operator=(anyclass1&& value) noexcept {
			cout << "move value assignemt\n";
		}
	};
	class anyclass2 {
	public:
		anyclass1 myvalue;
		anyclass2() {
			cout << "default constructor2\n";
		}
		anyclass2(const anyclass1& value) {
			cout << "copy constructor2\n";
		}
		/// <summary>
		/// myvalue ���� �� ���� �����ڷ� ������. myvalue(move(value)) �� �����ؾ� �̵� �����ڷ� ������.
		/// </summary>
		anyclass2(anyclass1&& value) noexcept : myvalue(value) /*myvalue(move(value))*/ {
			cout << "move constructor2\n";
		}
	};
	void case1() {
		anyclass1 a;
		//������ ����
		anyclass2 b(move(a));

	}
	
	class anyclass3{
	public:
		int value;
	};

	void anywork2(anyclass3& value) {
		cout << "reference" << endl;
	}
	void anywork2(const anyclass3& value) {
		cout << "const reference" << endl;
	}
	void anywork2(anyclass3&& value) {
		cout << "move" << endl;
	}

	/// <summary>
	/// ���ø� ���ڰ� ���ø� Ÿ��(T)�� �߷��� �� T�� ���۷����� �ƴ� �Ϲ����� Ÿ���̶�� const�� ������.
	/// �׷��� cref, move ��� lvalue�� �߷е�.
	/// </summary>
	template<typename T>
	void anywork1(T value) {
		anywork2(value);
	}
	void case2() {
		anyclass3 value;
		const anyclass3 cvalue;
		anywork2(value); //ref
		anywork2(cvalue); //const ref
		anywork2(anyclass3()); //move

		cout << endl;

		anywork1(value); //ref
		anywork1(cvalue); //ref
		anywork1(anyclass3()); //ref
	}

	template<typename T>
	void anywork3(T& value) {
		anywork2(value);
	}
	template<>
	void anywork3(int& value) {

	}
	void case3() {
		anyclass3 value;
		const anyclass3 cvalue;

		anywork3(value);
		anywork3(cvalue);
		
		// ������ ���� �߻�.
		// anyclass3()�� rvalue�̹Ƿ� ������ ������ �� ����. �Ʒ��� ���� ����.
		//anywork3(anyclass3()); 
		
		int a = 1;
		anywork3(a);
		// rvalue�̹Ƿ� ������ ������ �� ����.
		// anywork3(1);
	}

	void main() {
		//case1();
		//case2();
		case3();
	}
}