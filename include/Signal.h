#pragma once
#include "ISignal.h"
#include "SignalMain.h"

#include <iostream>

template<typename... Arguments>
class Signal : public ISignal
{
public:

    void emit() override
    {
        std::cout << "derived emit\n";
        SignalMain::get().mQueue.push(std::make_shared<Signal>(*this));
    }

    void call() override { std::cout << "derived call\n"; }
    void connect() override { std::cout << "derived connect\n"; }
};

