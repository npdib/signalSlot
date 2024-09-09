#pragma once

#include <iostream>
#include <vector>
#include <functional>

class ISignal
{
public:
	virtual void emit()			{ std::cout << "parent emit\n";	}
	virtual void call()			{ std::cout << "parent call\n"; }
	virtual void connect()		{ std::cout << "parent connect\n"; }
};
