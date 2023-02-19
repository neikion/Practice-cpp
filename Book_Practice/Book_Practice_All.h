#pragma once
#ifndef Book_Practice_All_h
#define Book_Practice_All_h
#include <iostream>
void GenericMain();

template<typename T>
T SumTemplateInHeader(const T& var1,const T& var2) {
	return var1 + var2;
}
//Ŭ���� ���� �ÿ��� template<typename T>�� �־����
//���ø� Ŭ������ ���ø� �Լ� ������ �� ���� ����(cpp ����)���� �� Ŭ������ ��� �۵��ϴ����� ���� ���ǰ� �־����.
//�׷��� Book_Practice_All.h�� Ŭ���� ������, Generic_Practice.cpp�� ���ǰ� ���� ���, LAB1���� Generic_Practice.cpp�� include���� ������ LAB1������ ���ǰ� ��� ������
//�ٸ� ���� �ٸ� ���� ����(cpp)���� ���ø� �̿��� �Ϲ� �Լ�����(ȣ����� ���� �Լ����� �ȴ�.) �ѹ��̶� ���� �� �ִ� �Լ��� �ٸ� ���� ����(cpp)���� T�� �Լ� �ñ״��İ� ���ٸ� ����� �� �ִ�.
template<typename T>
class classtemplate1 {
private:
	T var1;
public:
	T get() const;
	T test1(T input) const;
	T test1() const;
	void set(T input);
	classtemplate1(T input);
	~classtemplate1();
};
#else
#error header aleary include
#endif