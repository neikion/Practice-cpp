#pragma once
#ifndef Virtual_Practice_h
#define Virtual_Practice_h
namespace VirtualPractice {
	void Main();
	class BaseClass {
	public:
		void notVirtual();
		virtual void Virtual();

	};
	class AdvanceClass : public BaseClass {
	public:
		void notVirtual();
		void Virtual();
		
	};

	class classMaster{
	public:
		virtual void show()=0;
	};
	class classSub1 :public classMaster{
	public:
		void show();
	};
	class classSub2 :public classMaster{
	public:
		void show();
	};
}
#else
#error header aleary include
#endif