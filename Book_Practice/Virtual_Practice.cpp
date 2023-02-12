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

//abstract, interface와 virtual 차이점
//1. 선택적 재정의가 가능.
//2. 원래라면 추상 함수를 가진 상위 클래스도 인스턴스 생성이 가능. 
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

//부모 소멸자만 호출되고 자식 소멸자는 호출되지 않는다.
//자식 클래스에서 힙을 할당 받은게 있다면 소멸자를 제대로 호출하지 못해 메모리 누수에 가능성이 있다.
DestructorAdvancedClass::~DestructorAdvancedClass() {
	cout << "Advanced" << "\n";
}

VirtualDestructorBaseClass::~VirtualDestructorBaseClass() {
	cout << "virtual base" << "\n";
}

//virtual을 통해 자식 소멸자 호출 후 부모 소멸자까지 호출된다.
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
	
	////변환 실패됨. 자식 클래스로 내려가기엔 정보가 부족해서 실패하는 듯
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