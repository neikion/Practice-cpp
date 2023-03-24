#include "OperatorOverload.h"
#include <iostream>
using namespace OperatorOverload;
using namespace std;

CustomType::CustomType(int invalue)
	:value(invalue) {

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
void Operator_Overload_Return_Copy_Constructor_Main() {
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
	CustomType c(1), c2(2);
	c = c2;
	cout << c.value << "\n";
	c = c;
	cout << c.value << "\n";
}

CustomType::~CustomType() {
	cout << "CustomType Destroy\n";
}

CustomTypeSmartPtr::CustomTypeSmartPtr(CustomType* ct) {
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
	CustomTypeSmartPtr sp = new CustomType(0);
	cout << sp->value << "\n";
	cout << (*sp).value << "\n";
	//아레의 경우에는 소멸자가 호출되지 않으니 대입 연산자를 오버라이딩해서 전 객체를 소멸시켜줘야함
	//ct = new CustomType(2);

}

CustomArray::CustomArray(int insize)
	:size(insize) {
	ptr = new int[size];
}

CustomArray::~CustomArray() {
	delete ptr;
}

int& CustomArray::operator[](int index) {
	if (size < 0 || size <= index) {
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
	CustomArray a(5);
	a[0] = 1;
	cout << a[0] << "\n";

}

CustomFunctor::CustomFunctor() {
	current = numeric_limits<int>::max();
}
CustomFunctor::CustomFunctor(int value)
	:current(value) {
}

int CustomFunctor::operator()(int value) {
	if (value < current) {
		current = value;
	}
	return current;
}

void CustomFunctorMain() {
	// 가장 성가신 구문 해석(Most vexing parse)
	// c++은 선언으로 해석할 수 있는 것은 항상 선언으로 해석한다.
	// CustomFunctor cf()
	// 위 코드는 기본 생성자를 호출하는 CustomFunctor를 생성하는 코드인지
	// CustomFunctor를 반환하는  cf()함수를 호출하는 것인지 컴파일러는 햇갈려한다.
	// 그래서 함수의 프로토 타입이 없다고 경고문구를 띄우기도 한다.
	// 클래스 생성은 괄호를 지울것.
	// 또는 중괄호 초기화를 사용하여 피할 수 있다.

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
	cout << "ct1(1) + ct2(2) = " << (ct1 + ct2).value << "\n";
}

// 포인터 왼쪽에 const는 해당 주소에 값 변경 불가.
// 포인터 오른쪽 const는 주소 변경 불가.
// 함수의 리턴타입이 클래스 유형이 아닐 경우 const는 아무 효과가 없다.
// 값을 복사해서 넘겨주기 때문
bool OperatorOverload::operator<(const CustomType& left, const CustomType& right) {
	return left.value < right.value;
}

//아레의 방법도 가능하며 좀 더 일반적인 방법
// VisaulStudio 2019 16.11.24에서는 컴파일러 버그로 오류가 남.
//namespace OperatorOverload {
//	
//	
//	ostream& operator<<(ostream& os, const CustomType& c) {
//		os << c.value;
//		return os;
//	}
//}

ostream& OperatorOverload::operator<<(ostream& os, const CustomType& c) {
	os << c.value;
	return os;
}

void CustomTypeNotMemberOverLoadMain2() {
	CustomType ct1(1), ct2(2);
	std::cout << "ct1(1) < ct2(2) = " << (ct1 < ct2) << "\n";
	std::cout << ct1 << "\n";
}




AutoChangeCustomType::AutoChangeCustomType(int invalue)
	:value(invalue) {
	cout << "int"<<"\n";
}

const AutoChangeCustomType OperatorOverload::operator+(const AutoChangeCustomType& left, const AutoChangeCustomType& right) {
	AutoChangeCustomType cf(left.value + right.value);
	return cf;
}

void AutoChangeCustomTypeMain() {
	AutoChangeCustomType cf1(0), cf2;
	cf2 = cf1 + 2;
	cout << cf2.value<<"\n";
}

NotAutoChangeCustomType::NotAutoChangeCustomType(int invalue)
	:value(invalue) {

}

NotAutoChangeCustomType::operator double() {
	return (double)value;
}


void NotAutoChangeCustomTypeMain() {
	NotAutoChangeCustomType cf1 = (NotAutoChangeCustomType)2;
	cout << cf1.value<<"\n";
	//cf1의 value가 double로 변환됨.
	cout << (double)cf1+1.2;
}
template<typename T>
CustomSmartPointer<T>::CustomSmartPointer(T* inptr)
	:ptr(inptr) {

}
template<typename T>
CustomSmartPointer<T>::~CustomSmartPointer() {
	delete ptr;
}
template<typename T>
T& CustomSmartPointer<T>::operator*() {
	return *ptr;
}
template<typename T>
T* CustomSmartPointer<T>::operator->() {
	return ptr;
}
InnerClass& InnerClass::operator*() {
	cout << "* 사용" << endl;
	return *this;
}
InnerClass* InnerClass::operator->() {
	cout << "-> 사용" << endl;
	return this;
}
void InnerClass::print() {
	cout << value << endl;
}
void SmartPointer2Main() {
	InnerClass* t1 = new InnerClass;
	CustomSmartPointer<InnerClass> sp(t1);
	(*t1).value = 10;

	// InnerClass의 ->와 * 연산자를 오버로딩 했는데 왜 연산자가 표시 안될까
	sp->print();

	// sp->은 *t1으로 치환되니 *t1 print 아닌가?
	// 연산자가 없으니 sp->-> 이런 식이 되어야 하지 않을까?

	// 출처 : https://www.tutorialspoint.com/cplusplus/class_member_access_operator_overloading.htm
	// sp->print(); 는 sp.operator->()->print(); 이렇게 치환된다.
	// sp객체에 operator->() 함수를 실행하여 받아온것을 -> 연산자를 통해 print()함수로 출력한다.
	// 또한 아레와 의미가 같다.
	(*(sp.operator->())).print();
	// sp.operator->()는 리턴값은 t1에 대한 포인터이므로 이는 결국와 같고
	(*(t1)).print();
	// 필요없는 괄호를 정리하면 이렇게 된다.
	(*t1).print();
	// t1앞에 *이 붙어서 왜 *연산자가 적용 안되는가 싶을텐데 이는 
	// t1이 InnerClass를 힙에 할당하며 주소값을 받아온 포인터이기 때문에
	// 객체.print()와 다를 것이 없다.
	// 즉 이게 만약 스택에 할당되었다면 아레와 같은 의미가 된다.
	// t1.print()
	
	// 만약 InnerClass에 -> 또는 * 연산자로 접근할 때 뭔가를 하고 싶게 만들고 싶다면
	// 스마트 포인터처럼 한번 더 감싸는 클래스가 필요하다.
}

InnerClass2& CustomSmartPointer2::operator*() {
	return *ptr;
}

InnerClass2* CustomSmartPointer2::operator->() {
	return ptr;
}
void InnerClass2::print() {
	cout << value << endl;
}
CustomSmartPointer2::CustomSmartPointer2(InnerClass2* inptr)
	:ptr(inptr) {

}

CustomSmartPointer2::~CustomSmartPointer2() {
	cout << "delete" << endl;
	delete ptr;
}

//기존 객체를 함수에서 delete해줘야 되므로
//잘 쓰던 포인터가 헤제될 수 있어 별로 좋은 방법이 아닌듯.
CustomSmartPointer2& CustomSmartPointer2::operator=(InnerClass2& right) {
	cout << this->ptr << endl << &right << endl;
	//주소 비교
	if (ptr != &right) {
		if (ptr->value != right.value) {
			InnerClass2* temp = ptr;
			(this->ptr) = &right;
			delete temp;
		}
	}
	cout << this->ptr << endl << &right << endl;
	return *this;
}

// 커스텀 스마트 포인터에 포인터가 아닌 int 자로형처럼
// =를 이용해서 내용물을 쉽게 바꿔보고 싶었다.
void SmartPointer3Main() {
	InnerClass2* t1 = new InnerClass2;
	t1->value = 20;
	InnerClass2* t2 = new InnerClass2;
	t2->value = 30;
	CustomSmartPointer2 sp(t1);
	sp->print();
	//원하던 것.
	sp = *t2;
	sp->print();
}
void OperatorOverload::Main() {
	SmartPointer3Main();
}

