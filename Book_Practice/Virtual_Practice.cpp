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
	
	////��ȯ ���е�. �ڽ� Ŭ������ �������⿣ ������ ����.
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
	middle1�� middle2�� ��ӿ��� virtual�� ���� ��� �� middle�� top�� �����ڸ� ���� ȣ���Ͽ��� top�� �����ڰ� �ι� ȣ��ȴ�.
	virtual�� �ٿ� ����ϰ� All���� Top�����ڸ� �ҷ������ν� top�����ڸ� �ѹ��� ȣ���� �� �ְ� �ȴ�.
	
	���� ���̺��� ���������ν� ���� ���� ��Ӻ��� ������ ũŰ���� Ŀ�� �� �ְ�, ���� ���ϸ� ����ų �� �ִ�. 
	�ٸ� top�� �����ڿ� �ִ� ���� ���Ƿ� �ڽ� Ŭ�������� �ٲ��� �� �־� middle���� ȣȯ�� ������ �Ͼ ���� ���� �� ����.

	���� ����� �����Ѵٸ� �긮�� ����, ��ø�� �Ϲ�ȭ�� ����غ��� ��.
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
	//��� Sub2�� t2 �Լ��� ����Ų��.
	//���� ����� ����߱⿡ ������. ��ü��ü���� Sub1�� Sub2�� �����ϴ� Base��ü�� �ϳ��� �ֱ⿡ ����.
	//Sub1�� Sub2�� ���� �Լ� �� �ϳ��� ������ �����ϸ�, �̷��� ��ü�� �ϳ��� �ֱ⿡ ��ü ��ü ������ ������ ������ ������.
	//t2�� ȣ���ϸ� Base::t2�� ȣ���� ���� Sub2::t2�� ȣ����.
	DSCAll* pa = new DSCAll();
	DSCSub1* ps1 = pa;
	DSCBase* psb = pa;
	DSCSub2* ps2 = pa;
	
	
	pa->t2();
	ps1->t2();
	ps2->t2();
	psb->t2();


	//sub1 sub2 �����͵��� ���� �ν��Ͻ��� ����Ű�� ���� Ȯ���ϴ� ���� ��ٷο� �� �ִ�.
	//�� �������� ��
	cout << "All ptr : " << pa << "\nSub1 ptr : " << ps1 << "\nSub2 ptr : " << psb <<"\nBase ptr : " << psb<< "\n";
	
	//dynamic_cast�� ���� Ŭ������ �����ָ� ���� �ν��Ͻ����� Ȯ�ΰ����ϴ�.
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
	//Mixsub�� �����ڰ� ���� ���⼭ �Ҵ�
	//�θ� �����ڰ� ������ �θ� ������ �ʱ�ȭ ����Ʈ���� �ʱ�ȭ�� �ȵȴ�.
	Mixsub1::subvalue = insub1;
	Mixsub2::subvalue = insub2;
}

//MixinClass
//���� ���� �Լ��� ������ �ν��Ͻ�ȭ�� �� ������, �ڸ� Ŭ������ ������ ����� �߰����ִ� Ŭ����
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


