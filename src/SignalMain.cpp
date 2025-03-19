#include "SignalMain.h"

namespace npdib
{
	SignalMain& SignalMain::get()
	{
		static SignalMain sSignalMain;
		return sSignalMain;
	}

	void SignalMain::run()
	{
		m_run = true;

		while (m_run)
		{
			if (!m_queue.empty())
			{
				std::unique_lock lock(m_queueMutex);
				const auto [signal, index] = m_queue.front();

				lock.unlock();
				signal->call(index);		// call connected functions

				lock.lock();
				m_queue.pop();				// remove from queue
			}
		}
	}

    void SignalMain::addToQueue(const SignalPacket& packet)
    {
		std::scoped_lock lock(m_queueMutex);
		m_queue.push(packet);
    }
}
