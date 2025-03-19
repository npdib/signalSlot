#pragma once

#include <mutex>
#include <queue>

#include "SignalBase.h"

/* SignalMain

This class is a singleton which can be constructed to run a signal based project.

It contains a queue of pointers to signals to be emitted

*/

namespace npdib
{
	class SignalMain
	{
		template<typename...> friend class Signal;

	public:
		static SignalMain& get();								// singleton getter

		void run();											// run the main Signal Loop
		void quit() { m_run = false; }
		using SignalPacket = std::pair<SignalBase*, uint16_t>;
		void addToQueue(const SignalPacket& packet);

		// explicitly delete constructor and equality
		SignalMain(SignalMain const&) = delete;					// Don't Implement
		void operator=(SignalMain const&) = delete;				// Don't implement

	private:
		SignalMain() = default;

		std::atomic<bool> m_run;

		std::mutex m_queueMutex;
		std::queue<SignalPacket> m_queue;			// queue of incoming signals
	};
}