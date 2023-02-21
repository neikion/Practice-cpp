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

//c++에서는 dummy는 이름 없이 int만 있어도 됨
//함수 내부의 리소스는 사라지니 value로 리턴
const CustomType CustomType::operator++(int dummy) {
	//한 번의 조작을 막아줄 임시객체 생성.
	//origin의 value를 저장하여 변경 전의 값을 저장한다.
	CustomType ct(value);

	//ct가 아닌 origin객체를 변경한다.
	++(*this);

	//return시 복사 생성자 호출.
	//ct의 내용을 돌려준다. 즉, origin이 변경되기 전의 내용
	return ct;
}

//interesting.
void Operator_Overload_Return_Copy_Constructor_Main(){
	CustomType origin(1);

	//operator++가 ct를 반환했으니 반환됬던 ct의 내용이 표시됨.
	cout << origin++.value << "\n";

	//줄이 바뀌었으니 반환되었던 객체 ct가 사라지고 origin의 내용이 출력된다.
	//operator++안에서 orgin을 조작했던 내용이 표시됨.
	cout << origin.value;
}

void OperatorOverload::Main() {
	Operator_Overload_Return_Copy_Constructor_Main();
}