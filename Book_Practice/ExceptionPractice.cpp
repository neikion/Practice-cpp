#include "ExceptionPractice.h"
#include <iostream>
using namespace std;
namespace ExceptionPractice {


	// initializer list에서 예외를 잡을 수 있지만, catch를 하더라도
	// 다시 예외를 호출자에게 던진다.
	// funtion try block은 생성자의 오류를 해결하기보다
	// 예외를 전파하는데 목적이 있는 듯 하다.
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

	// function try block은 이렇게도 사용할 수 있지만,
	// 그냥 함수 내부의 try catch를 사용하는 쪽이 더 많다.
	void FunctionTryBlock2()
	try{
		throw exception("exception");
	}
	catch(...)
	{
		cout << "exception catch" << endl;
	}
	void FunctionTryBlockMain() {
		//이 try문이 없다면 그냥 오류가 나서 죽어버린다.
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