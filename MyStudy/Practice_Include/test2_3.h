
#ifndef test2_3_h
#define test2_3_h
inline void testmethod3();

//2_1.cpp파일에서 구현한 함수를 2_2.cpp파일에서 사용할 수 있다.
void testmethod4();
#else
#error header aleary include
#endif
