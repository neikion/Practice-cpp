#include "Book_Practice1.h"
int test1::Practice_Main() {
	test1::Practice_scope();
	return 0;
}
int scope_test = 1;

//Practice_scope2�� ����� �����Ƿ� �ٸ� ���Ͽ��� include�ص� ��� ����
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
�⺻ ������
�ʱ�ȭ ����Ʈ ��� ����
*/
test1::test1()
{
	testintvalue1 = 0;
	testintvalue2 = 0;
}

/*�Ű����� ������*/
test1::test1(int value1, int value2):testintvalue1(value1),testintvalue2(value2)
{

}

/*���� ������*/
test1::test1(const test1& value):
	testintvalue1(value.testintvalue1),
	testintvalue2(value.testintvalue2)
{

}

test1::~test1() {
	cout << "test1 delete";
}