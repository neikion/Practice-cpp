#include "Book_Practice1.h"
#include <iostream>
using namespace std;
using namespace Book_Practice1;

void PointerMain() {
	//*�� ���� ������. �ּ��� ������ �˷���
	//&�� �ּ� ������. �޸� �ּҸ� �˷���
	int a = 5;
	int* b = &a;
	int* c = b;
	cout << *c << "\n";
	cout << *(&a)<<"\n";
}

void PointerMain2() {
	//������ ����
	test1 t1;
	(&t1)->Practice_scope();
	(*(&t1)).Practice_scope();
}

void ScopeMain() {
	test1 t1;
	t1.Practice_scope();
}

//Practice_scope2�� ����� �����Ƿ� �ٸ� ���Ͽ��� include�ص� ��� ����
void Practice_scope2(int value) {
	cout << "dd" << value << endl;
}

int scope_test = 1;
void test1::Practice_scope() {
	int scope_test = 2;
	cout << scope_test<<endl;
	cout << ::scope_test<<endl;
	Practice_scope2(1);
}
/*
�⺻ ������
�ʱ�ȭ ����Ʈ ��� ����
*/
test1::test1()
{
	testintvalue1 = 0;
	testintvalue2 = 0;
}

/*�Ű����� ������*/
test1::test1(int value1, int value2) :testintvalue1(value1), testintvalue2(value2)
{

}

/*���� ������*/
test1::test1(const test1& value) :
	testintvalue1(value.testintvalue1),
	testintvalue2(value.testintvalue2)
{

}

test1::~test1() {
	cout << "test1 delete";
}



void Book_Practice1::Main() {
	PointerMain();
}