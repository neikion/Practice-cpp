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
	cout << "Sub1";
}
void classSub2::show() {
	cout << "Sub2";
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

DestructorBaseClass::~DestructorBaseClass() {
	cout << "base"<<"\n";
}

//�θ� �Ҹ��ڸ� ȣ��ǰ� �ڽ� �Ҹ��ڴ� ȣ����� �ʴ´�.
//�ڽ� Ŭ�������� ���� �Ҵ� ������ �ִٸ� �Ҹ��ڸ� ����� ȣ������ ���� �޸� ������ ���ɼ��� �ִ�.
DestructorAdvancedClass::~DestructorAdvancedClass() {
	cout << "Advanced" << "\n";
}

VirtualDestructorBaseClass::~VirtualDestructorBaseClass() {
	cout << "virtual base" << "\n";
}

//virtual�� ���� �ڽ� �Ҹ��� ȣ�� �� �θ� �Ҹ��ڱ��� ȣ��ȴ�.
VirtualDestructorAdvancedClass::~VirtualDestructorAdvancedClass() {
	cout << "virtual Advanced" << "\n";
}

void DestuctorMain() {
	DestructorBaseClass* dc;
	dc = new DestructorBaseClass();
	delete dc;
	dc = new DestructorAdvancedClass();
	delete dc;

	VirtualDestructorBaseClass* vdc;
	vdc = new VirtualDestructorBaseClass();
	delete vdc;
	vdc = new VirtualDestructorAdvancedClass();
	delete vdc;
	
}

void typeidMain() {
	BaseClass bc;
	AdvanceClass ac;
	cout << typeid(bc).name()<<"\n";
	cout << typeid(ac).name() << "\n";
	cout << (typeid(bc) == typeid(ac))<<"\n";
	cout << (typeid(bc) != typeid(ac))<<"\n";
}

void DynamicCastMain() {
	
	////��ȯ ���е�. �ڽ� Ŭ������ �������⿣ ������ �����ؼ� �����ϴ� ��
	//BaseClass* vdc = new BaseClass;
	//vdc->Virtual();
	//AdvanceClass* vdc2 = dynamic_cast<AdvanceClass*>(vdc);
	//vdc2->Virtual();
	//delete vdc2;
	

	BaseClass* vdc=new AdvanceClass;
	vdc->notVirtual();
	AdvanceClass* vdc2 = dynamic_cast<AdvanceClass*>(vdc);
	vdc2->notVirtual();
	delete vdc2;
}

void VirtualPractice::Main() {
	DynamicCastMain();
}