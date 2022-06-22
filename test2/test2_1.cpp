#include "test2_1.h"
#include "test2_3.h"
void testmethod1() {
	cout << "tm1"<<endl;
	testmethod3();
	testmethod4();
}
inline void testmethod3() {
	cout << "tm3" << endl;
}
void testmethod4() {
	cout << "tm4" << endl;
}