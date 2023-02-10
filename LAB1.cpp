// LAB1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;
#include "Book_Practice/Book_Practice1.h"

#include "test2/test2_2.h"
#include "test2/test2_1.h"
#include "test3/MultipleInheritance.h"

#include "Book_Practice/Generic_Practice.h"
#include "Book_Practice/Virtual_Practice.h"
int main()
{
    /*
    책 연습
    */
    
    /*test1 t1;
    t1.Practice_Main();
    int a = 5;
    int* b = &a;
    int* c = b;
    cout << *(&a);
    (&t1)->Practice_Main();
    (*(&t1)).Practice_Main();*/
    
    /*
    test2
    include test
    포함
    */
    //testmethod1();
    //testmethod2();
    
    /*
    test3
    MultipleInheritance
    다중 상속
    */
    //MultipleInheritanceMain();

    /* test4
    제네릭
    */
    //GenericPractice::Main();
    
    /* test 5
    다형성
    */
    VirtualPractice::Main();

    return 0;
}
