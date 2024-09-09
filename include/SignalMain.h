#pragma once

#include <vector>
#include <memory>
#include <queue>

#include "ISignal.h"

/* SignalMain

This class is a singleton which can be constructed to run a signal based project.

It contains a queue of pointers to signals to be emitted

*/

class SignalMain
{
	template<typename...> friend class Signal;

public:
	static SignalMain& get();								// singleton getter

	void run();												// run the main Signal Loop

	// explicitly delete constructor and equality
	SignalMain(SignalMain const&) = delete;					// Don't Implement
	void operator=(SignalMain const&) = delete;				// Don't implement

private:
	SignalMain() = default;

	std::queue<std::shared_ptr<ISignal>> mQueue;			// queue of incoming signals
};