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
	
	////변환 실패됨. 자식 클래스로 내려가기엔 정보가 부족.
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
VirtualInhertop::VirtualInhertop(int input)
:value(input){
	cout << "top " << value << "\n";
}
void VirtualInhertop::print() {
	cout << "top " << value << "\n";
}

VirtualInhermiddle1::VirtualInhermiddle1(int input)
	:value2(input) , VirtualInhertop(input) {
	cout << "middle1 " << value2 << "\n";
}
void VirtualInhermiddle1::print() {
	cout << "middle1 "<< value2 << "\n";
}

VirtualInhermiddle2::VirtualInhermiddle2(int input)
	:value3(input), VirtualInhertop(input){
	cout << "middle2 "<<value3 << "\n";
}
void VirtualInhermiddle2::print() {
	cout << "middle2 " << value3 << "\n";
}
VirtualInherAll::VirtualInherAll(int input)
	: VirtualInhermiddle1(input), VirtualInhermiddle2(input), VirtualInhertop(4){
	cout << "all" << value2 << value3 << "\n";
}
void VirtualInherAll::print() {
	cout << "all"<<value<< value2<<value3 << "\n";
}

void VirtualInherMain() {
	/*
	middle1과 middle2의 상속에서 virtual이 없을 경우 각 middle이 top에 생성자를 각자 호출하여서 top의 생성자가 두번 호출된다.
	virtual를 붙여 상속하고 All에서 Top생성자를 불러줌으로써 top생성자를 한번만 호출할 수 있게 된다.
	
	가상 테이블을 생성함으로써 기존 다중 상속보다 데이터 크키보다 커질 수 있고, 성능 저하를 일으킬 수 있다. 
	다만 top의 생성자에 넣는 값을 임의로 자식 클래스에서 바꿔줄 수 있어 middle에서 호환성 문제가 일어날 수도 있을 것 같다.

	다중 상속을 생각한다면 브리지 패턴, 중첩된 일반화도 고려해볼만 함.
	*/
	VirtualInhertop vt(1);
	cout << "\n";
	VirtualInhermiddle1 vm1(21);
	cout << "\n";
	VirtualInhermiddle2 vm2(22);
	cout << "\n";
	VirtualInherAll va(3);
}


void DSCSub1::t1()
{
	cout << "sub1"<<"\n";
}
void DSCSub2::t2() {
	cout << "Sub2 t2\n";
}

//delegate to a sister class
void DelegateSisterClass() {
	//모두 Sub2에 t2 함수를 가리킨다.
	//가상 상속을 사용했기에 가능함. 전체객체에서 Sub1과 Sub2가 공유하는 Base객체가 하나만 있기에 가능.
	//Sub1과 Sub2는 가상 함수 중 하나의 구현을 제공하며, 이러한 객체가 하나만 있기에 전체 객체 내에서 각각의 구현을 제공함.
	//t2를 호출하면 Base::t2를 호출한 다음 Sub2::t2를 호출함.
	DSCAll* pa = new DSCAll();
	DSCSub1* ps1 = pa;
	DSCBase* psb = pa;
	DSCSub2* ps2 = pa;
	
	
	pa->t2();
	ps1->t2();
	ps2->t2();
	psb->t2();


	//sub1 sub2 포인터들이 같은 인스턴스를 가리키는 것을 확인하는 것은 까다로울 수 있다.
	//각 포인터의 값
	cout << "All ptr : " << pa << "\nSub1 ptr : " << ps1 << "\nSub2 ptr : " << psb <<"\nBase ptr : " << psb<< "\n";
	
	//dynamic_cast로 같은 클래스로 맞춰주면 같은 인스턴스인지 확인가능하다.
	cout << (dynamic_cast<DSCSub2*>(ps1)) << "\n";
	cout << (dynamic_cast<DSCSub2*>(ps2)) << "\n";
	cout << ((dynamic_cast<DSCBase*>(ps1)) == (dynamic_cast<DSCBase*>(ps2)));

	delete pa;
}

VirtualPractice::Mixmain::Mixmain(int value1)
	:mainvalue(value1)
{
}

void VirtualPractice::Mixmain::print() {
	cout << "main " << mainvalue << "\n";
}
void Mixall::print()
{
	cout << "all\nmain value : " <<mainvalue << "\nsub1 value : "
		<< Mixsub1::subvalue <<"\nsub2 value : " << Mixsub2::subvalue << "\n";
}

Mixall::Mixall(int inmain, int insub1, int insub2)
	: Mixmain(inmain){
	//Mixsub에 생성자가 없어 여기서 할당
	//부모에 생성자가 없으면 부모 변수는 초기화 리스트에서 초기화가 안된다.
	Mixsub1::subvalue = insub1;
	Mixsub2::subvalue = insub2;
}

//MixinClass
//순수 가상 함수를 가져서 인스턴스화할 수 없지만, 자른 클래스에 데이터 멤버를 추가해주는 클래스
void MixinMain() {
	Mixall mc(0, 1, 2);
	Mixall* mc1 = new Mixall(0, 1, 2);
	mc1->print();
	dynamic_cast<Mixsub1*>(mc1)->print();
	dynamic_cast<Mixsub2*>(mc1)->print();
	dynamic_cast<Mixmain*>(mc1)->print();
	delete mc1;
}
void VirtualPractice::Main() {
	MixinMain();
}


