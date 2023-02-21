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

void OperatorOverload::Main() {
	Operator_Overload_Return_Copy_Constructor_Main();
}