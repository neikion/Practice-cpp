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
void VirtualPractice::Main() {
	VirtualMain();
}