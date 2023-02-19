#include "Return_Practice.h"
#include <iostream>
using namespace std;
using namespace ReturnPractice;

void ThisinClass::Main(){
	cout << this->value << "\n";
	cout << (*this).value << "\n";
	cout << value << "\n";
	
}

//�Լ� �ڿ� const�� ���� ��� ��� �Լ��� ȣ��Ʈ ��ü(�ڱ� �ڽ� Ŭ����)�� �������� ���Ѵ�.
void ConstMethodinClass::ConstMethod() const {
	//�ڱ� �ڽ��� �������� ���ϹǷ� ������
	//ConstMethodinClass::value += 1;
	
	//�д� ���� ����
	cout << value << "\n";
}

void ConstMethodinClass::Main() {
	ConstMethod();
}

//���������� ���� �޸� ����. ���� ��� ����
void SendParameter::refSend(int& value) {
	value ++;
}

//�����͸� �Ѱ���
//�����Ϳ� ���� ó���� �ؾߵ�
void SendParameter::ptrSend(int* value) {
	(*value)++;
}
//���� �����ؿ�
void SendParameter::valueSend(int value) {
	value++;
}
void SendParameter::notChangeSend(const int value) {
	//�Ű������� const�̹Ƿ� ���� �Ұ�
	//value++;
}

void SendParameter::Main() {
	int value=0;
	cout << "origin value" << value << "\n";
	valueSend(value);
	cout << "value " << value << "\n";
	refSend(value);
	cout <<"ref " << value << "\n";
	int* ptrValue = &value;
	ptrSend(ptrValue);
	cout <<"ptr " << value << "\n";
	notChangeSend(value);
	cout << "not Change " << value << "\n";

}

int returnResult::returnValue() {
	return 1;
}

int& returnResult::returnRef(int& value) {
	value++;
	return value;
}

int* returnResult::returnPtr(int* value) {
	(*value)++;
	return value;
}

//���� ��ü�� �������� ���ϰ� ����.
//���� ��ü�� ��ȣ�ؾ� �ϴ� ���(rvalue�θ� ����ϴ� ���) ���
const int& returnResult::notChageReturn(int& value) {
	return value;
}

void returnResult::Main() {
	int value = returnValue();
	cout << "value " << value << "\n";

	value = returnRef(value);
	cout << "ref " << value << "\n";

	int* ptrValue = &value;
	value = (*returnPtr(ptrValue));
	cout << "ptr " << value << "\n";

	//const�� notChageReturn�� ���� �Ұ�
	//value=(notChageReturn(value)++);
	cout << "not Change " << notChageReturn(value) << "\n";

	//�ٸ� ������ ��Ƽ� ������ ����
	value = notChageReturn(value);
	value++;
	cout << "change possible " << value << "\n";
	
}

void ReturnPractice::Main() {
	returnResult sp;
	sp.Main();
}