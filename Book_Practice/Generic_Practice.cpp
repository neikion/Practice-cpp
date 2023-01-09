using namespace std;
#include <iostream>
#include "Book_Practice_All.h"
template<typename T>

void Sum(T var1, T var2) {
	cout << var1+var2;
}

void GenericMain() {
	Sum(1, 2);
}