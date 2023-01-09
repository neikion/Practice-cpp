#pragma once
#ifndef Book_Practice1_h
#define Book_Practice1_h
#include <iostream>
using namespace std;
class test1 {
private :
	int testintvalue1;
	int testintvalue2;
public : 
	int Practice_Main();
	void Practice_scope();
	test1();
	test1(int value1,int value2);
	test1(const test1& value);
	~test1();
};

#else
#error header aleary include
#endif