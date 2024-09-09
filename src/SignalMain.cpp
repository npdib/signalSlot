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
			if (mQueue.size() > 0)
			{
				const auto [signal, index] = mQueue.front();
				signal->call(index);		// call connected functions
				mQueue.pop();				// remove from queue
			}
		}
	}
}