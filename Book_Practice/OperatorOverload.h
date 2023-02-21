#pragma once
#ifndef Operator_Overload_h
#define Operator_Overload_h
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
	};
}
#else
#error header aleary include
#endif