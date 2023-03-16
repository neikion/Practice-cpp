#include "ExceptionPractice.h"
#include <iostream>
using namespace std;
namespace ExceptionPractice {


	// initializer list���� ���ܸ� ���� �� ������, catch�� �ϴ���
	// �ٽ� ���ܸ� ȣ���ڿ��� ������.
	// funtion try block�� �������� ������ �ذ��ϱ⺸��
	// ���ܸ� �����ϴµ� ������ �ִ� �� �ϴ�.
	TestClass::TestClass()
	try :value(0),tc(TestClassMini()){
	}
	catch(...)
	{
		cout << "exception catch" << endl;
	}


	TestClassMini::TestClassMini():value(0) {
		throw std::exception("exception");
	}

	// function try block�� �̷��Ե� ����� �� ������,
	// �׳� �Լ� ������ try catch�� ����ϴ� ���� �� ����.
	void FunctionTryBlock2()
	try{
		throw exception("exception");
	}
	catch(...)
	{
		cout << "exception catch" << endl;
	}
	void FunctionTryBlockMain() {
		//�� try���� ���ٸ� �׳� ������ ���� �׾������.
		try {
			TestClass tc;
		}
		catch (exception e) {
			cout <<"exception catch massage : " << e.what() << endl;
		}

		FunctionTryBlock2();
		
	}
	void Main() {
		FunctionTryBlockMain();
	}
}