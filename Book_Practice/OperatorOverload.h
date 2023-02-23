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
		int current;
	public:
		CustomFunctor();
		CustomFunctor(int);
		int operator()(int);
	};
}
#else
#error header aleary include
#endif