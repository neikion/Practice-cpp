#include "Book_Practice1.h"
int test1::Practice_Main() {
	test1::Practice_scope();
	return 0;
}
int scope_test = 1;

//Practice_scope2는 헤더에 없으므로 다른 파일에서 include해도 사용 못함
void Practice_scope2(int a);
void test1::Practice_scope() {
	int scope_test = 2;
	cout << scope_test<<endl;
	cout << ::scope_test<<endl;
	Practice_scope2(1);
}
void Practice_scope2(int b) {
	cout << "dd"<<b<<endl;
}

/*
기본 생성자
초기화 리스트 사용 안함
*/
test1::test1()
{
	testintvalue1 = 0;
	testintvalue2 = 0;
}

/*매개변수 생성자*/
test1::test1(int value1, int value2):testintvalue1(value1),testintvalue2(value2)
{

}

/*복사 생성자*/
test1::test1(const test1& value):
	testintvalue1(value.testintvalue1),
	testintvalue2(value.testintvalue2)
{

}

test1::~test1() {
	cout << "test1 delete";
}