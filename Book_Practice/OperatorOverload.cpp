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

//c++������ dummy�� �̸� ���� int�� �־ ��
//�Լ� ������ ���ҽ��� ������� value�� ����
const CustomType CustomType::operator++(int dummy) {
	//�� ���� ������ ������ �ӽð�ü ����.
	//origin�� value�� �����Ͽ� ���� ���� ���� �����Ѵ�.
	CustomType ct(value);

	//ct�� �ƴ� origin��ü�� �����Ѵ�.
	++(*this);

	//return�� ���� ������ ȣ��.
	//ct�� ������ �����ش�. ��, origin�� ����Ǳ� ���� ����
	return ct;
}

//interesting.
void Operator_Overload_Return_Copy_Constructor_Main() {
	CustomType origin(1);

	//operator++�� ct�� ��ȯ������ ��ȯ��� ct�� ������ ǥ�õ�.
	cout << origin++.value << "\n";

	//���� �ٲ������ ��ȯ�Ǿ��� ��ü ct�� ������� origin�� ������ ��µȴ�.
	//operator++�ȿ��� orgin�� �����ߴ� ������ ǥ�õ�.
	cout << origin.value;
}

CustomType& CustomType::operator=(const CustomType& ctRight) {
	//�Ű������� &�� ��������
	//if���� &�� �ּ� �б�
	if (this != &ctRight) {
		value = ctRight.value;
		cout << "���� �ٸ� ��ü\n";
	}
	else {
		cout << "���� ��ü\n";
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
	//�Ʒ��� ��쿡�� �Ҹ��ڰ� ȣ����� ������ ���� �����ڸ� �������̵��ؼ� �� ��ü�� �Ҹ���������
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
	// ���� ������ ���� �ؼ�(Most vexing parse)
	// c++�� �������� �ؼ��� �� �ִ� ���� �׻� �������� �ؼ��Ѵ�.
	// CustomFunctor cf()
	// �� �ڵ�� �⺻ �����ڸ� ȣ���ϴ� CustomFunctor�� �����ϴ� �ڵ�����
	// CustomFunctor�� ��ȯ�ϴ�  cf()�Լ��� ȣ���ϴ� ������ �����Ϸ��� �ް����Ѵ�.
	// �׷��� �Լ��� ������ Ÿ���� ���ٰ� ������� ���⵵ �Ѵ�.
	// Ŭ���� ������ ��ȣ�� �����.
	// �Ǵ� �߰�ȣ �ʱ�ȭ�� ����Ͽ� ���� �� �ִ�.

	CustomFunctor cf;
	cout << "���� ���� ��" << cf(5) << "\n";
	cout << "���� ���� ��" << cf(6) << "\n";
	cout << "���� ���� ��" << cf(3) << "\n";
}


const CustomType OperatorOverload::operator+(const CustomType& left, const CustomType& right) {
	CustomType ct(left.value + right.value);
	return ct;
}



void CustomTypeNotMemberOverLoadMain() {
	CustomType ct1(1), ct2(2);
	cout << "ct1(1) + ct2(2) = " << (ct1 + ct2).value << "\n";
}

// ������ ���ʿ� const�� �ش� �ּҿ� �� ���� �Ұ�.
// ������ ������ const�� �ּ� ���� �Ұ�.
// �Լ��� ����Ÿ���� Ŭ���� ������ �ƴ� ��� const�� �ƹ� ȿ���� ����.
// ���� �����ؼ� �Ѱ��ֱ� ����
bool OperatorOverload::operator<(const CustomType& left, const CustomType& right) {
	return left.value < right.value;
}

//�Ʒ��� ����� �����ϸ� �� �� �Ϲ����� ���
// VisaulStudio 2019 16.11.24������ �����Ϸ� ���׷� ������ ��.
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
	//cf1�� value�� double�� ��ȯ��.
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
	cout << "* ���" << endl;
	return *this;
}
InnerClass* InnerClass::operator->() {
	cout << "-> ���" << endl;
	return this;
}
void InnerClass::print() {
	cout << value << endl;
}
void SmartPointer2Main() {
	InnerClass* t1 = new InnerClass;
	CustomSmartPointer<InnerClass> sp(t1);
	(*t1).value = 10;

	// InnerClass�� ->�� * �����ڸ� �����ε� �ߴµ� �� �����ڰ� ǥ�� �ȵɱ�
	sp->print();

	// sp->�� *t1���� ġȯ�Ǵ� *t1 print �ƴѰ�?
	// �����ڰ� ������ sp->-> �̷� ���� �Ǿ�� ���� ������?

	// ��ó : https://www.tutorialspoint.com/cplusplus/class_member_access_operator_overloading.htm
	// sp->print(); �� sp.operator->()->print(); �̷��� ġȯ�ȴ�.
	// sp��ü�� operator->() �Լ��� �����Ͽ� �޾ƿ°��� -> �����ڸ� ���� print()�Լ��� ����Ѵ�.
	// ���� �Ʒ��� �ǹ̰� ����.
	(*(sp.operator->())).print();
	// sp.operator->()�� ���ϰ��� t1�� ���� �������̹Ƿ� �̴� �ᱹ�� ����
	(*(t1)).print();
	// �ʿ���� ��ȣ�� �����ϸ� �̷��� �ȴ�.
	(*t1).print();
	// t1�տ� *�� �پ �� *�����ڰ� ���� �ȵǴ°� �����ٵ� �̴� 
	// t1�� InnerClass�� ���� �Ҵ��ϸ� �ּҰ��� �޾ƿ� �������̱� ������
	// ��ü.print()�� �ٸ� ���� ����.
	// �� �̰� ���� ���ÿ� �Ҵ�Ǿ��ٸ� �Ʒ��� ���� �ǹ̰� �ȴ�.
	// t1.print()
	
	// ���� InnerClass�� -> �Ǵ� * �����ڷ� ������ �� ������ �ϰ� �Ͱ� ����� �ʹٸ�
	// ����Ʈ ������ó�� �ѹ� �� ���δ� Ŭ������ �ʿ��ϴ�.
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

//���� ��ü�� �Լ����� delete����� �ǹǷ�
//�� ���� �����Ͱ� ������ �� �־� ���� ���� ����� �ƴѵ�.
CustomSmartPointer2& CustomSmartPointer2::operator=(InnerClass2& right) {
	cout << this->ptr << endl << &right << endl;
	//�ּ� ��
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

// Ŀ���� ����Ʈ �����Ϳ� �����Ͱ� �ƴ� int �ڷ���ó��
// =�� �̿��ؼ� ���빰�� ���� �ٲ㺸�� �;���.
void SmartPointer3Main() {
	InnerClass2* t1 = new InnerClass2;
	t1->value = 20;
	InnerClass2* t2 = new InnerClass2;
	t2->value = 30;
	CustomSmartPointer2 sp(t1);
	sp->print();
	//���ϴ� ��.
	sp = *t2;
	sp->print();
}
void OperatorOverload::Main() {
	SmartPointer3Main();
}

