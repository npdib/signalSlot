#pragma once

#include <iostream>

namespace npdib
{
	class SignalBase
	{
	public:
        virtual ~SignalBase() = default;
        void emit() { std::cout << "parent emit\n"; }
		virtual void call(uint16_t index) { std::cout << "parent call\n"; }
		void connect() { std::cout << "parent connect\n"; }
	};
}