#pragma once
#ifndef Operator_Overload_h
#define Operator_Overload_h
namespace OperatorOverload {
	void Main();
	//�Լ� �� const
	//���� ��ü�� ������ �ǹ�
	//������ ���� ����
	//�����Ϸ��� ����ȭ �� �� �ְ� �ϴ� �ǹ̰� ŭ
	
	//�Լ� �� const
	//ȣ��Ʈ ��ü ���� ����
	class CustomType {
	public:
		int value;
		CustomType(int);
		~CustomType();

		//+CustomType
		//ȣ��Ʈ ��ü ���� ����
		//���ο� ��ü ����
		//rvalue�θ� ���
		const CustomType operator+() const;
		
		//++CustomType
		//ȣ��Ʈ ��ü ���� �ʿ�
		//ȣ��Ʈ ��ü ������ ����
		//lvalue�ε� ��� ����
		CustomType& operator++();

		//CustomType++
		//int�� �ϴ� ���� ����. ���� �����Ϸ����� ���� ���������� �˷��ֱ� ���� ǥ��
		//int�ܿ� �ٸ� �ڷ����� ������ ����.
		//ȣ��Ʈ ��ü ���� �ʿ�
		//rvalue�� ���
		const CustomType operator++(int);

		// CustomType = CustomType
		// ������ ��ü�� �����Ű�� �ȵ�
		// ȣ��Ʈ ��ü�� ������Ѿ���
		// ������ ����
		CustomType& operator=(const CustomType& ctRight);
	};

	class CustomTypeSmartPtr {
	private:
		CustomType* ptr;
	public:
		CustomTypeSmartPtr(CustomType*);
		~CustomTypeSmartPtr();
		CustomType* operator->() const;
		CustomType& operator*() const;
	};

	class CustomArray {
	private:
		int* ptr;
		int size;
	public:
		CustomArray(int size);
		~CustomArray();
		//getter�� setter�� ���̴� �Լ� �� const���η� ����
		//������
		int& operator[](int index)const;
		//������
		int& operator[](int index);
	};

	//�� Ŭ������ �����ڿ� �Էµ� �� �� ���� ���� �� ���
	class CustomFunctor {
	private:
		int current;
	public:
		CustomFunctor();
		CustomFunctor(int);
		int operator()(int);
	};
}
#else
#error header aleary include
#endif