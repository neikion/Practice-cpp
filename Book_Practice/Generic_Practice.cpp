using namespace std;
#include <iostream>
#include "Book_Practice_All.h"

template<typename T>
void Sum(T var1, T var2) {
	cout << var1+var2;
}

//위에 선언한 template<typename T>는 재사용이 안된다.
//SumRef에 template<typename T>를 위에 template을 재사용하려는 생각으로 없앤다면 오류가 난다.
template<typename T>
void SumRecycle(T var1,T var2) {
	cout << var1 + var2;
}

//참조로 전달
template<typename T>
void SwapRef(T& var1, T& var2) {

	T temp = var1;
	var1 = var2;
	var2 = temp;
}

//T는 어떤 자료형을 사용할지 지정함.
//N은 무조건 int 값으로 오도록 지정
//T형식 ary를 참조형식으로 받음
//N은 컴파일러에서 배열 요소의 크키를 구해 넘겨준다.
template<typename T, int N>
void printAry(T (&ary)[N]) {
	for (int i = 0; i < N; i++) {
		cout << ary[i] << "\n";
	}
}

void SendPointer(int ary[]) {
	//파라미터로 int ary[]는 int *ary와 같다.
	// 함수 생성시 포인터 하나 더 생성. 그 포인터가 메인에 ary를 가리킴
	cout << "배열 값" << *ary << "\n";
	cout << "배열 주소" << ary << "\n";
	cout << "배열을 가리키는 포인터 주소" << &ary << "\n";
}
void SendRef(int (&ary)[2]) {
	//파라미터가 메인함수의 ary와 공유됨.
	//단 뒤에 인덱스와 자료형이 일치해야됨.
	cout << "배열 값" << *ary << "\n";
	cout << "배열 주소" << ary << "\n";
	cout <<"배열을 가리키는 포인터 주소"<< & ary << "\n";
}

void SendMain() {
	int ary[2] = { 1,16 };
	SendPointer(ary);
	SendRef(ary);
}

template<typename T>
void castingTemplate(T var1,T var2) {
	cout << var1 + var2;
}
void castingTemplateMain() {
	//서로의 자료형이 달라 오류가 남
	//castingTemplate(1.2,1);
	//명시적으로 자료형을 지정하여 입력 값들을 double로 변환함
	castingTemplate<double>(1.2, 1);
}



template<typename T>
void SumSpecialization(T var1,T var2) {
	cout << var1 + var2<<"\n";
}

//double만 따로 처리
//오버로딩과는 다르게 매개 변수의 갯수가 같다.
//또한 새로운 함수를 만들어내는 것이 아닌, 특정 자료형을 따로 처리하는 것이다.
template<>
void SumSpecialization(double var1,double var2) {
	cout << "double의 경우만 특별히 현재 문구 출력" << "\n" << var1 + var2 << "\n";
}

void SumSpecializationMain() {
	SumSpecialization(1,2);
	SumSpecialization(1.2, 2.2);
}



//const는 참조로 전달할 때 매개변수로 리터럴 값을 사용하기 위하여 사용하였다.
//const가 아닌 참조 매개 변수에는 const 인수를 전달할 수 없다. const 매개 변수를 사용하면 non-const 및 const 인수를 함수에 전달할 수 있다.
//const 참조는 l-value(대입문(=)에서 왼쪽 값, 어떠한 메모리 위치를 가리키는데, & 연산자를 통해 그 위치를 참조할 수 있는 것), const l-value 및 r-value(대입문(=)에서 오른쪽 값,lvalue가 아닌 값) 를 포함한 모든 유형의 인수를 허용할 수 있다.
template<typename T>
T SumTemplateOverroding(const T& var1,const T& var2) {
	return var1 + var2;
}
template<typename T>
T SumTemplateOverroding(const T& var1,const T& var2,const T& var3) {
	return SumTemplateOverroding(SumTemplateOverroding(var1, var2), var3);
}
void SumTemplateOverrodingMain() {
	double b = 1;
	cout << SumTemplateOverroding(1.2, b) << "\n";
}

//함수를 정의할 때 무조건 <T>를 붙여줘야 함.
//<T>를 붙여주기 위해 template<typename T>를 선언함.
template<typename T>
void classtemplate1<T>::set(T input) {
	var1 = input;
}

template<typename T>
T classtemplate1<T>::get() const {
	return var1;
}
template<typename T>
T classtemplate1<T>::test1(T input) const {
	return var1;
}

template<typename T>
classtemplate1<T>::classtemplate1(T input)
	:var1(input) {
	
}

template<typename T>
classtemplate1<T>::~classtemplate1() {

}
template<typename T>
T classtemplate1<T>::test1() const {
	return var1;
}


void GenericMain() {
	classtemplate1<int> test1(5);
	test1.test1();
}