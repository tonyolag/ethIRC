#include "connection.hpp"

namespace hydra
{
    connection::connection(sockets::socket pSock, session *pSess, std::thread *pThreadPtr)
        : mSock(pSock), mSess(pSess), mThreadPtr(pThreadPtr)
    {
        mThreadPtr->detach();
    }

    message connection::read()
    {
        while (mQueue.empty())
        {
            std::vector<std::string> lines = mSock.recv();
            for (std::string line : lines)
            {
                try
                {
                    message msg = message(line);
                    mQueue.push(msg);
                }
                catch (const std::invalid_argument&)
                {
                    logs::error << "Error interpreting message: " << line << logs::done;
                }
            }
        }
        return mQueue.pop();
    }

    bool connection::running()
    {
        return mRunning;
    }
}
