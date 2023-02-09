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
	//클래스 선언 시에도 template<typename T>가 있어야함
	//템플릿 클래스의 템플림 함수 구현은 각 번역 유닛(cpp 파일)마다 이 클래스가 어떻게 작동하는지에 대한 정의가 있어야함.
	// 템플릿 정의에 관한 cpp를 만들어 include하는 방식을 사용.
	//그래서 Book_Practice_All.h에 클래스 선언이, Generic_Practice.cpp에 정의가 있을 경우, LAB1에서 Generic_Practice.cpp를 include하지 않으면 LAB1에서는 정의가 없어서 오류남
	//다만 위에 다른 번역 유닛(cpp)에서 템플릿 이외의 일반 함수에서(호출되지 않은 함수여도 된다.) 한번이라도 사용된 적 있는 함수는 다른 번역 유닛(cpp)에서 T와 함수 시그니쳐가 같다면 사용할 수 있다.
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