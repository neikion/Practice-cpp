#pragma once

#ifndef Operator_Overload_h
#define Operator_Overload_h
#include <iostream>
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

		

		//CustomType + CustomType
		//���ο� ��ü�� �Լ� ���ο��� ��������� ��ȯ��.
		//friend ���� ���� �Լ��ε� ���� ����.(��� getter,setter�� ���� �����ؾߵ�)
		//�� �Լ��� Ŭ���� �ȿ� ���� ���
		// �����Ϸ��� Customtype2 + �� CustomType2 + CustomType2�� �ް����Ѵ�.
		// �̸� �����ϱ� ���� �ڱ� �ڽ��� �������� �ʴ� ���� ������(+,-,*,/ ��)�� �ܺη�
		// �ڱ� �ڽ��� �����ϴ� ���׿�����(++, += ��)�� Ŭ���� ���ο� �����Ѵ�.
		friend const CustomType operator+(const CustomType& left, const CustomType& right);
		
		//�� �ڵ嵵 ���� ���� ����� ������ �� ����� �� ��õ��.
		//const CustomType operator+(const CustomType& right) const;

		/* �� �ڵ� ����
		const CustomType CustomType::operator+(const CustomType& right) const {
			CustomType ct(this->value+right.value);
			return ct;
		}
		*/
		friend bool operator<(const CustomType&, const CustomType&);
		friend std::ostream& operator<<(std::ostream& os, const CustomType& c);
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
		int current=0;
	public:
		CustomFunctor();
		CustomFunctor(int);
		int operator()(int);
	};

	class AutoChangeCustomType {	
	public:
		int value;
		AutoChangeCustomType() = default;
		//�Ʒ� ������(��ȯ ������)�� ���� �����Ϸ����� �⺻ �ڷ���(int)�� Ŭ���� �ڷ������� �ڵ� ��ȯ
		AutoChangeCustomType(int);
		friend const AutoChangeCustomType operator+(const AutoChangeCustomType&, const AutoChangeCustomType&);
	};
	class NotAutoChangeCustomType {
	public:
		int value;
		NotAutoChangeCustomType() = default;
		//��������� ��ȯ(ĳ����)�Ҷ��� ��ȯ ����.
		//�����Ϸ����� �ڵ����� �ٲ��� ����.
		explicit NotAutoChangeCustomType(int);
		//Ŭ������ double�� ��ȯ �����ϰ� ����. explicit���� ��� ����.
		explicit operator double();
	};
}
#else
#error header aleary include
#endif