#include "Virtual_Practice.h"
#include <iostream>
using namespace std;
using namespace VirtualPractice;

void BaseClass::notVirtual() {
	cout << "base";
}
void AdvanceClass::notVirtual() {
	cout << "Advance";
}
void BaseClass::Virtual() {
	cout << "base";
}
void AdvanceClass::Virtual() {
	cout << "Advance";
}

void VirtualMain() {
	BaseClass* pt;
	pt = new AdvanceClass();
	pt->notVirtual();
	delete pt;
	pt = new BaseClass();
	pt->Virtual();
	delete pt;
	pt = new AdvanceClass();
	pt->Virtual();
	delete pt;
}
void classSub1::show() {
	cout << "c2";
}
void classSub2::show() {
	cout << "c3";
}

//abstract, interface�� virtual ������
//1. ������ �����ǰ� ����.
//2. ������� �߻� �Լ��� ���� ���� Ŭ������ �ν��Ͻ� ������ ����. 
void AbstractVirtualMain() {
	classMaster* c=new classSub1();
	c->show();
	delete c;
	c = new classSub2();
	c->show();
	delete c;
}
void VirtualPractice::Main() {
	VirtualMain();
}