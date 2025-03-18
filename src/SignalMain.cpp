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
		while (true)
		{
			if (!mQueue.empty())
			{
				std::unique_lock lock(mQueueMutex);
				const auto [signal, index] = mQueue.front();

				lock.unlock();
				signal->call(index);		// call connected functions

				lock.lock();
				mQueue.pop();				// remove from queue
			}
		}
	}

    void SignalMain::addToQueue(const SignalPacket& packet)
    {
		std::scoped_lock lock(mQueueMutex);
		mQueue.push(packet);
    }
}
