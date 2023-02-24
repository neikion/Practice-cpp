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
void Operator_Overload_Return_Copy_Constructor_Main(){
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
	//�Ʒ��� ��쿡�� �Ҹ��ڰ� ȣ����� ������ ���� �����ڸ� �������̵��ؼ� �� ��ü�� �Ҹ���������
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
	// �� �ڵ�� �⺻ �����ڸ� ȣ���ϴ� CustomFunctor�� �����ϴ� �ڵ�����
	// CustomFunctor�� ��ȯ�ϴ�  cf()�Լ��� ȣ���ϴ� ������ �����Ϸ��� �ް����Ѵ�.
	// �׷��� �Լ��� ������ Ÿ���� ���ٰ� ������� ���⵵ �Ѵ�.
	// Ŭ���� ������ ��ȣ�� �����.

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
	cout <<"ct1(1) + ct2(2) = " << (ct1+ct2).value << "\n";
}

void OperatorOverload::Main() {
	CustomTypeNotMemberOverLoadMain();
}

