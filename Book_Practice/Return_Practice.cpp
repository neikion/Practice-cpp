#include "Return_Practice.h"
#include <iostream>
using namespace std;
using namespace ReturnPractice;

void ThisinClass::Main(){
	cout << this->value << "\n";
	cout << (*this).value << "\n";
	cout << value << "\n";
	
}

//함수 뒤에 const를 붙일 경우 멤버 함수가 호스트 겍체(자기 자신 클래스)를 변경하지 못한다.
void ConstMethodinClass::ConstMethod() const {
	//자기 자신을 변경하지 못하므로 오류남
	//ConstMethodinClass::value += 1;
	
	//읽는 것은 가능
	cout << value << "\n";
}

void ConstMethodinClass::Main() {
	ConstMethod();
}

//참조변수를 통한 메모리 공유. 복사 비용 없음
void SendParameter::refSend(int& value) {
	value ++;
}

//포인터를 넘겨줌
//포인터에 대한 처리를 해야됨
void SendParameter::ptrSend(int* value) {
	(*value)++;
}
//값을 복사해옴
void SendParameter::valueSend(int value) {
	value++;
}
void SendParameter::notChangeSend(const int value) {
	//매개변수가 const이므로 수정 불가
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

//리턴 객체를 변경하지 못하게 막음.
//리턴 객체를 보호해야 하는 경우(rvalue로만 사용하는 경우) 사용
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

	//const로 notChageReturn는 수정 불가
	//value=(notChageReturn(value)++);
	cout << "not Change " << notChageReturn(value) << "\n";

	//다른 변수에 담아서 변경은 가능
	value = notChageReturn(value);
	value++;
	cout << "change possible " << value << "\n";
	
}

void ReturnPractice::Main() {
	returnResult sp;
	sp.Main();
}