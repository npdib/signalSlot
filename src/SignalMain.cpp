#include "SignalMain.h"

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
			mQueue.front()->call();		// call connected functions
			mQueue.pop();				// remove from queue
		}
	}
}
