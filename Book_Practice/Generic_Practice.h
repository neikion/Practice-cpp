#pragma once
#ifndef Generic_Practice_h
#define Generic_Practice_h
#include <iostream>
namespace GenericPractice {
	void Main();
	template<typename T>
	T SumTemplateInHeader(const T& var1, const T& var2) {
		return var1 + var2;
}
	//Ŭ���� ���� �ÿ��� template<typename T>�� �־����
	//���ø� Ŭ������ ���ø� �Լ� ������ �� ���� ����(cpp ����)���� �� Ŭ������ ��� �۵��ϴ����� ���� ���ǰ� �־����.
	// ���ø� ���ǿ� ���� cpp�� ����� include�ϴ� ����� ���.
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

	template<typename T>
	class ClassTemplateStack {
	private:
		T* ptr;
		int limit;
		int size;
	public:
		ClassTemplateStack(int limit);
		~ClassTemplateStack();
		void push(const T& element);
		T pop();
	};
	typedef ClassTemplateStack<int> reanmeintStack;
}
#else
#error header aleary include
#endif