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

	class DestructorBaseClass {
	public:
		~DestructorBaseClass();
	};
	class DestructorAdvancedClass :public DestructorBaseClass{
	public:
		~DestructorAdvancedClass();
	};
	class VirtualDestructorBaseClass {
	public:
		virtual ~VirtualDestructorBaseClass();
	};
	class VirtualDestructorAdvancedClass : public VirtualDestructorBaseClass{
	public:
		~VirtualDestructorAdvancedClass();
	};
	class VirtualInhertop {
	public:
		int value;
		VirtualInhertop(int input);
		void print();
	};
	class VirtualInhermiddle1 : virtual public VirtualInhertop {
	public:
		int value2;
		VirtualInhermiddle1(int input);
		void print();
	};
	class VirtualInhermiddle2 :virtual public VirtualInhertop{
	public:
		int value3;
		VirtualInhermiddle2(int input);
		void print();
	};
	
	class VirtualInherAll : public VirtualInhermiddle1,public VirtualInhermiddle2 {
	public:
		VirtualInherAll(int input);
		void print();
	};

	class DSCBase {
	public:
		virtual void t1() = 0;
		virtual void t2() = 0;
	};
	class DSCSub1 : public virtual DSCBase {
	public:
		virtual void t1();
	};
	class DSCSub2 : public virtual DSCBase {
	public:
		virtual void t2();
	};
	class DSCAll : public DSCSub1, public DSCSub2 {
	};
}
#else
#error header aleary include
#endif