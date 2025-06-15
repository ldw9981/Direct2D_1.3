#pragma once
#include "Component.h"
#include <iostream>
#include "MySystem.h"
#include "MyComponent.h"
#include "GameObject.h"

class MyPlusComponent :
	public MyComponent
{
public:
	MyPlusComponent()
		:MyComponent(1)
	{
		std::cout << this << " " << __FUNCTION__ << "\n";
	}
	~MyPlusComponent() override
	{
		std::cout << this << " " << __FUNCTION__ << "\n";
	}
	
	MyComponent* Other=nullptr;

	void DoSomeThing() override
	{
		std::cout << this << " " << __FUNCTION__  << "\n";
	}

	void OnEnable() override
	{
		std::cout << this << " " << __FUNCTION__ << "\n";
		Other = owner->GetComponent<MyComponent>();
		//�߰� ������ ���� �������� �ִ�.
	};
	void OnDestroy() override
	{
		std::cout << this << " " << __FUNCTION__ << "\n";
	};
};

