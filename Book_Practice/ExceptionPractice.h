#pragma once
#ifndef Exception_Practice_h
#define Exception_Practice_h
#include <iostream>
using namespace std;
namespace ExceptionPractice {
	void Main();
	class TestClassMini {
	public:
		int value;
		TestClassMini();
	};
	class TestClass {
	public:
		int value;
		TestClassMini tc;
		TestClass();
	};

}

#else
#error header aleary include
#endif