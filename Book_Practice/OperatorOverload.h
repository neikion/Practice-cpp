#pragma once

#ifndef Operator_Overload_h
#define Operator_Overload_h
#include <iostream>
namespace OperatorOverload {
	void Main();
	//함수 앞 const
	//리턴 객체는 연산결과 의미
	//참조로 리턴 여부
	//컴파일러가 최적화 할 수 있게 하는 의미가 큼
	
	//함수 뒤 const
	//호스트 객체 변경 여부
	class CustomType {
	public:
		int value;
		CustomType(int);
		~CustomType();

		//+CustomType
		//호스트 객체 변경 없음
		//새로운 객체 생성
		//rvalue로만 사용
		const CustomType operator+() const;
		
		//++CustomType
		//호스트 객체 변경 필요
		//호스트 객체 참조로 리턴
		//lvalue로도 사용 가능
		CustomType& operator++();

		//CustomType++
		//int는 하는 일이 없다. 그저 컴파일러에게 후위 연산자임을 알려주기 위한 표식
		//int외에 다른 자료형은 오류가 난다.
		//호스트 객체 변경 필요
		//rvalue로 사용
		const CustomType operator++(int);

		// CustomType = CustomType
		// 오른쪽 객체를 변경시키면 안됨
		// 호스트 객체를 변경시켜야함
		// 참조로 전달
		CustomType& operator=(const CustomType& ctRight);

		

		//CustomType + CustomType
		//새로운 객체가 함수 내부에서 만들어져서 반환됨.
		//friend 없이 전역 함수로도 구현 가능.(대신 getter,setter로 변수 접근해야됨)
		//이 함수가 클래스 안에 있을 경우
		// 컴파일러는 Customtype2 + 와 CustomType2 + CustomType2를 햇갈려한다.
		// 이를 방지하기 위해 자기 자신을 리턴하지 않는 이항 연산자(+,-,*,/ 등)은 외부로
		// 자기 자신을 리턴하는 이항연산자(++, += 등)는 클래스 내부에 선언한다.
		friend const CustomType operator+(const CustomType& left, const CustomType& right);
		
		//이 코드도 위와 같은 결과를 내지만 위 방법을 더 추천함.
		//const CustomType operator+(const CustomType& right) const;

		/* 위 코드 구현
		const CustomType CustomType::operator+(const CustomType& right) const {
			CustomType ct(this->value+right.value);
			return ct;
		}
		*/
		friend bool operator<(const CustomType&, const CustomType&);
		friend std::ostream& operator<<(std::ostream& os, const CustomType& c);
	};
	
	class CustomTypeSmartPtr {
	private:
		CustomType* ptr;
	public:
		CustomTypeSmartPtr(CustomType*);
		~CustomTypeSmartPtr();
		CustomType* operator->() const;
		CustomType& operator*() const;
	};

	class CustomArray {
	private:
		int* ptr;
		int size;
	public:
		CustomArray(int size);
		~CustomArray();
		//getter와 setter의 차이는 함수 뒤 const여부로 나뉨
		//접근자
		int& operator[](int index)const;
		//설정자
		int& operator[](int index);
	};

	//이 클래스의 생성자에 입력된 값 중 가장 작은 값 출력
	class CustomFunctor {
	private:
		int current=0;
	public:
		CustomFunctor();
		CustomFunctor(int);
		int operator()(int);
	};

	class AutoChangeCustomType {	
	public:
		int value;
		AutoChangeCustomType() = default;
		//아레 생성자(변환 생성자)를 통해 컴파일러에서 기본 자료형(int)을 클래스 자료형으로 자동 변환
		AutoChangeCustomType(int);
		friend const AutoChangeCustomType operator+(const AutoChangeCustomType&, const AutoChangeCustomType&);
	};
	class NotAutoChangeCustomType {
	public:
		int value;
		NotAutoChangeCustomType() = default;
		//명시적으로 변환(캐스팅)할때만 변환 가능.
		//컴파일러에서 자동으로 바꾸지 않음.
		explicit NotAutoChangeCustomType(int);
		//클래스를 double로 변환 가능하게 만듦. explicit없이 사용 가능.
		explicit operator double();
	};
}
#else
#error header aleary include
#endif