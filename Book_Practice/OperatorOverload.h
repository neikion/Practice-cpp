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
	};
}
#else
#error header aleary include
#endif