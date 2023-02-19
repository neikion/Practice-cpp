using namespace std;
#include <iostream>
#include "Book_Practice_All.h"

template<typename T>
void Sum(T var1, T var2) {
	cout << var1+var2;
}

//���� ������ template<typename T>�� ������ �ȵȴ�.
//SumRef�� template<typename T>�� ���� template�� �����Ϸ��� �������� ���شٸ� ������ ����.
template<typename T>
void SumRecycle(T var1,T var2) {
	cout << var1 + var2;
}

//������ ����
template<typename T>
void SwapRef(T& var1, T& var2) {

	T temp = var1;
	var1 = var2;
	var2 = temp;
}

//T�� � �ڷ����� ������� ������.
//N�� ������ int ������ ������ ����
//T���� ary�� ������������ ����
//N�� �����Ϸ����� �迭 ����� ũŰ�� ���� �Ѱ��ش�.
template<typename T, int N>
void printAry(T (&ary)[N]) {
	for (int i = 0; i < N; i++) {
		cout << ary[i] << "\n";
	}
}

void SendPointer(int ary[]) {
	//�Ķ���ͷ� int ary[]�� int *ary�� ����.
	// �Լ� ������ ������ �ϳ� �� ����. �� �����Ͱ� ���ο� ary�� ����Ŵ
	cout << "�迭 ��" << *ary << "\n";
	cout << "�迭 �ּ�" << ary << "\n";
	cout << "�迭�� ����Ű�� ������ �ּ�" << &ary << "\n";
}
void SendRef(int (&ary)[2]) {
	//�Ķ���Ͱ� �����Լ��� ary�� ������.
	//�� �ڿ� �ε����� �ڷ����� ��ġ�ؾߵ�.
	cout << "�迭 ��" << *ary << "\n";
	cout << "�迭 �ּ�" << ary << "\n";
	cout <<"�迭�� ����Ű�� ������ �ּ�"<< & ary << "\n";
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
	//������ �ڷ����� �޶� ������ ��
	//castingTemplate(1.2,1);
	//��������� �ڷ����� �����Ͽ� �Է� ������ double�� ��ȯ��
	castingTemplate<double>(1.2, 1);
}



template<typename T>
void SumSpecialization(T var1,T var2) {
	cout << var1 + var2<<"\n";
}

//double�� ���� ó��
//�����ε����� �ٸ��� �Ű� ������ ������ ����.
//���� ���ο� �Լ��� ������ ���� �ƴ�, Ư�� �ڷ����� ���� ó���ϴ� ���̴�.
template<>
void SumSpecialization(double var1,double var2) {
	cout << "double�� ��츸 Ư���� ���� ���� ���" << "\n" << var1 + var2 << "\n";
}

void SumSpecializationMain() {
	SumSpecialization(1,2);
	SumSpecialization(1.2, 2.2);
}



//const�� ������ ������ �� �Ű������� ���ͷ� ���� ����ϱ� ���Ͽ� ����Ͽ���.
//const�� �ƴ� ���� �Ű� �������� const �μ��� ������ �� ����. const �Ű� ������ ����ϸ� non-const �� const �μ��� �Լ��� ������ �� �ִ�.
//const ������ l-value(���Թ�(=)���� ���� ��, ��� �޸� ��ġ�� ����Ű�µ�, & �����ڸ� ���� �� ��ġ�� ������ �� �ִ� ��), const l-value �� r-value(���Թ�(=)���� ������ ��,lvalue�� �ƴ� ��) �� ������ ��� ������ �μ��� ����� �� �ִ�.
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

//�Լ��� ������ �� ������ <T>�� �ٿ���� ��.
//<T>�� �ٿ��ֱ� ���� template<typename T>�� ������.
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