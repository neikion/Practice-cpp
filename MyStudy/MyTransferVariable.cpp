#include"MyTransferVariable.h"
#include <iostream>
#include <string>
#include <type_traits>
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
	
	class anyclass3{};

	void checkValueRef(anyclass3& value) {
		cout << "lvalue reference" << endl;
	}
	void checkValueRef(const anyclass3& value) {
		cout << "const reference" << endl;
	}
	void checkValueRef(anyclass3&& value) {
		cout << "rvalue reference" << endl;
	}

	/// <summary>
	/// ���ø� ���ڰ� ���ø� Ÿ��(T)�� �߷��� �� T�� ���۷����� �ƴ� �Ϲ����� Ÿ���̶�� const�� ������.
	/// �׷��� cref, move ��� lvalue�� �߷е�.
	/// </summary>
	template<typename T>
	void anywork1(T value) {
		checkValueRef(value);
	}
	void case2() {
		anyclass3 value;
		const anyclass3 cvalue;
		checkValueRef(value); //ref
		checkValueRef(cvalue); //const ref
		checkValueRef(anyclass3()); //move

		cout << endl;

		anywork1(value); //ref
		anywork1(cvalue); //ref
		anywork1(anyclass3()); //ref
	}

	template<typename T>
	void anywork2(T& value) {
		checkValueRef(value);
	}
	template<>
	void anywork2(int& value) {

	}
	void case3() {
		anyclass3 value;
		const anyclass3 cvalue;

		anywork2(value);
		anywork2(cvalue);
		
		// ������ ���� �߻�.
		// anyclass3()�� rvalue�̹Ƿ� ������ ������ �� ����. �Ʒ��� ���� ����.
		//anywork3(anyclass3()); 
		
		int a = 1;
		anywork2(a);
		// rvalue�̹Ƿ� ������ ������ �� ����.
		// anywork3(1);
	}

	/// <summary>
	/// T&&�� rvalue�� �ƴ϶� ������ ���۷����� ǥ�ô�.
	/// </summary>
	template<typename T>
	void anywork3(T&& value) {
		checkValueRef(forward<T>(value));
	}

	void case4() {
		anyclass3 value;
		anywork3(move(value));
		anywork3(value);
	}


	/// <summary>
	/// forward lvalue to lvalue
	/// </summary>
	template<typename t>
	t&& anywork5(typename remove_reference<t>::type& value) {
		return static_cast<t&&>(value);
	}

	/// <summary>
	/// forward rvalue to rvalue
	/// </summary>
	template<typename t>
	t&& anywork5(typename remove_reference<t>::type&& value) {
		return static_cast<t&&>(value);
	}


	template<typename t>
	void anywork6(t&& value) {
		checkValueRef(anywork5<t>(value));
	}
	void case5() {
		anyclass3 value;
		anywork6(value);
		anywork6(move(value));
	}

	void main() {
		//case1();
		//case2();
		//case3();
		//case4();
		case5();
	}
}