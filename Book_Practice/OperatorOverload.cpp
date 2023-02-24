#include "OperatorOverload.h"
#include <iostream>
using namespace OperatorOverload;
using namespace std;

CustomType::CustomType(int invalue)
:value(invalue){

}

const CustomType CustomType::operator+() const {
	return CustomType(+value);
}

CustomType& CustomType::operator++() {
	value++;
	return *this;
}

//c++에서는 dummy는 이름 없이 int만 있어도 됨
//함수 내부의 리소스는 사라지니 value로 리턴
const CustomType CustomType::operator++(int dummy) {
	//한 번의 조작을 막아줄 임시객체 생성.
	//origin의 value를 저장하여 변경 전의 값을 저장한다.
	CustomType ct(value);

	//ct가 아닌 origin객체를 변경한다.
	++(*this);

	//return시 복사 생성자 호출.
	//ct의 내용을 돌려준다. 즉, origin이 변경되기 전의 내용
	return ct;
}

//interesting.
void Operator_Overload_Return_Copy_Constructor_Main(){
	CustomType origin(1);

	//operator++가 ct를 반환했으니 반환됬던 ct의 내용이 표시됨.
	cout << origin++.value << "\n";

	//줄이 바뀌었으니 반환되었던 객체 ct가 사라지고 origin의 내용이 출력된다.
	//operator++안에서 orgin을 조작했던 내용이 표시됨.
	cout << origin.value;
}

CustomType& CustomType::operator=(const CustomType& ctRight) {
	//매개변수의 &는 참조변수
	//if문의 &는 주소 읽기
	if (this != &ctRight) {
		value = ctRight.value;
		cout << "서로 다른 객체\n";
	}
	else {
		cout << "같은 객체\n";
	}
	return *this;
}

void OperatorEqulMain() {
	CustomType c(1),c2(2);
	c = c2;
	cout << c.value<<"\n";
	c = c;
	cout << c.value<<"\n";
}

CustomType::~CustomType() {
	cout << "CustomType Destroy\n";
}

CustomTypeSmartPtr::CustomTypeSmartPtr(CustomType* ct){
	ptr = ct;
}

CustomTypeSmartPtr::~CustomTypeSmartPtr() {
	delete ptr;
}

CustomType& CustomTypeSmartPtr::operator*() const {
	return *ptr;
}

CustomType* CustomTypeSmartPtr::operator->() const {
	return ptr;
}

void CustomTypeSmartPtrMain() {
	CustomType* ct(new CustomType(1));
	CustomTypeSmartPtr sp=new CustomType(0);
	cout << sp->value<<"\n";
	cout << (*sp).value << "\n";
	//아레의 경우에는 소멸자가 호출되지 않으니 대입 연산자를 오버라이딩해서 전 객체를 소멸시켜줘야함
	//ct = new CustomType(2);

}

CustomArray::CustomArray(int insize)
	:size(insize){
	ptr = new int[size];
}

CustomArray::~CustomArray() {
	delete ptr;
}

int& CustomArray::operator[](int index) {
	if (size < 0 || size<=index) {
		throw exception();
	}
	return ptr[index];
}

int& CustomArray::operator[](int index)const {
	if (size < 0 || size <= index) {
		throw exception();
	}
	return ptr[index];
}

void CustomArrayMain() {
	CustomArray a (5);
	a[0] = 1;
	cout << a[0]<<"\n";

}

CustomFunctor::CustomFunctor() {
	current = numeric_limits<int>::max();
}
CustomFunctor::CustomFunctor(int value)
:current(value){
}

int CustomFunctor::operator()(int value) {
	if (value < current) {
		current = value;
	}
	return current;
}

void CustomFunctorMain() {
	// CustomFunctor cf()
	// 위 코드는 기본 생성자를 호출하는 CustomFunctor를 생성하는 코드인지
	// CustomFunctor를 반환하는  cf()함수를 호출하는 것인지 컴파일러는 햇갈려한다.
	// 그래서 함수의 프로토 타입이 없다고 경고문구를 띄우기도 한다.
	// 클래스 생성은 괄호를 지울것.

	CustomFunctor cf;
	cout << "가장 작은 값" << cf(5) << "\n";
	cout << "가장 작은 값" << cf(6) << "\n";
	cout << "가장 작은 값" << cf(3) << "\n";
}


const CustomType OperatorOverload::operator+(const CustomType& left, const CustomType& right) {
	CustomType ct(left.value + right.value);
	return ct;
}



void CustomTypeNotMemberOverLoadMain() {
	CustomType ct1(1), ct2(2);
	cout <<"ct1(1) + ct2(2) = " << (ct1+ct2).value << "\n";
}

void OperatorOverload::Main() {
	CustomTypeNotMemberOverLoadMain();
}

