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

	void main() {
		case1();
	}
}