#pragma once
#ifndef Return_Practice_h
#define Return_Practice_h
namespace ReturnPractice {
	void Main();
	class ThisinClass {
	public:
		int value;
		void Main();
	};
	class ConstMethodinClass {
	public:
		int value;
		void ConstMethod() const;
		void Main();
	};
	class SendParameter {
	public:
		void refSend(int &value);
		void ptrSend(int* value);
		void valueSend(int value);
		void notChangeSend(const int value);
		void Main();
	};
	class returnResult {
	public:
		int returnValue();
		int& returnRef(int& value);
		int* returnPtr(int* value);
		const int& notChageReturn(int& value);
		void Main();
	};
}
#else
#error header aleary include
#endif