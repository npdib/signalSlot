#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <map>

#include "ISignal.h"
#include "SignalMain.h"


namespace npdib
{
    /* This is a templated class which takes the arguments of the functions that it connects to

    You can then connect functions of this type to this signal. when emitted with a certain set of parameters, these parameters are stored with an index and ran when the loop gets to them.

    */

    template <typename... Arguments>
    class Signal : public ISignal
    {
    public:
        Signal()
            : mCurrentIndex(0)
        {
        }

        // push an event onto the event queue
        void emit(Arguments... args)
        {
            SignalMain::get().addToQueue({this, mCurrentIndex});             

            std::scoped_lock lock(mArgumentMapMutex);
            mArgumentMap[mCurrentIndex++] = std::tuple<Arguments...>(args...);  // store the arguments in the map against the index

#ifdef DEBUG
            std::cout << "derived emit\n";
#endif
        }

        // directly run all connected functions with a set of arguments
        void run(Arguments... args)  
        {
            std::unique_lock lock(mFunctionMutex);
            for (const auto& function : mFunctions)
            {
                lock.unlock();
                function(args...);
                lock.lock();
            }
        }

        // call functions with arguments from the map
        void call(uint16_t index) override      
        {
            std::unique_lock lock(mArgumentMapMutex);
            if (!mArgumentMap.contains(index))
            {
                std::cout << "the index didnt exist, oops";
                return;
            }

            const std::tuple<Arguments...> tuple = mArgumentMap[index];

            lock.unlock();
            unpackAndRunFunctions(tuple, std::index_sequence_for<Arguments...>());

            lock.lock();
            mArgumentMap.erase(index);

#ifdef DEBUG
            std::cout << "derived call\n";
#endif
        }

        // connect a function to the signal
        void connect(std::function<void(Arguments...)> func)
        {
            std::scoped_lock lock(mFunctionMutex);
            mFunctions.push_back(func);

#ifdef DEBUG
            std::cout << "derived connect\n";
#endif
        }

    private:
        // Helper method to unpack the tuple
        template <std::size_t... Is>
        void unpackAndRunFunctions(const std::tuple<Arguments...>& tuple, std::index_sequence<Is...>)
        {
            std::unique_lock lock(mFunctionMutex);
            for (const auto& function : mFunctions)
            {
                lock.unlock();
                function(std::get<Is>(tuple)...);
                lock.lock();
            }
        }

        std::mutex mFunctionMutex;
        std::vector<std::function<void(Arguments...)>> mFunctions;     // all connected functions

        std::mutex mArgumentMapMutex;
        std::map<uint16_t, std::tuple<Arguments...>> mArgumentMap;      // map between indices and arguments

        uint16_t mCurrentIndex;
    };
}