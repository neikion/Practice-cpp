// LAB1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;
#include "Book_Practice/Book_Practice1.h"

#include "MyStudy/Practice_Include/test2_2.h"
#include "MyStudy/Practice_Include//test2_1.h"
#include "MyStudy/MultipleInheritance.h"

#include "Book_Practice/Generic_Practice.h"
#include "Book_Practice/Virtual_Practice.h"
#include "Book_Practice/Return_Practice.h"
#include "Book_Practice/OperatorOverload.h"
#include "Book_Practice/ExceptionPractice.h"
#include "MyStudy/MyThread.h"
#include "MyStudy/MyFunctional.h"
#include "MyStudy/MyConst.h"
#include "MyStudy/MyTransferVariable.h"
int main()
{
    /*test 1
    기타 테스트
    */
    //Book_Practice1::Main();
    
    /*
    test2
    include test
    포함
    */
    /*testmethod1();
    testmethod2();*/
    
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
    //VirtualPractice::Main();

    /* test 6
    리턴 종류
    */
    //ReturnPractice::Main();

    /* test 7
    연산자 오버로딩
    */
    //OperatorOverload::Main();

    /* test 8
    예외 처리
    */
    //ExceptionPractice::Main();
    
    /* test 9
    쓰레드
    */
    //MyThead::Main();

    /* test 10
    함수 객체
    */
    //MyFunctional::Main();

    /* test11
    const
    */
    //MyConst::Main();
    /* test12
    rvalue
    */
    TransferVariable::main();
    return 0;
}
