#pragma once

#include "ThreadObject.h"
#include "WorkFunction.h"

#include <array>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "GG/Core/Service/ServiceProviderInterface.h"

namespace gg
{
    class CThreadPool : public IService
    {
    public:
        enum class EPriority
        {
            HIGH,
            MEDIUM,
            LOW,
            SIZE
        };

        CThreadPool& operator=( CThreadPool&& ) = default;
        CThreadPool( CThreadPool&& ) = default;

        CThreadPool( const CThreadPool& ) = delete;
        CThreadPool& operator=( const CThreadPool& ) = delete;

        CThreadPool( size_t inNumWantedThreads = std::thread::hardware_concurrency() );
        ~CThreadPool();

        // Call on main thread
        void CallOnCompletes( size_t inAllowedDurationInMilliseconds );
        void ShutDown();

        size_t ActiveWorkCount( const std::string& inWithTag = std::string() ) const;

        template < typename TWorkReturnType >
        size_t StartWork( const std::function< TWorkReturnType() >& inWork,
                          const std::function< void( const TWorkReturnType& ) >& inOnComplete,
                          EPriority inPriority = EPriority::MEDIUM,
                          const std::string& inTag = std::string() )
        {
            size_t threadID = FindAvailableThread();

            auto it = currentWorkCounters.find( inTag );
            if ( it == currentWorkCounters.end() )
            {
                currentWorkCounters[inTag] = 1;
            }
            else
            {
                it->second++;
            }

            auto workFunc = std::make_shared< threading_internal::TWorkFunction< TWorkReturnType > >( inWork, inOnComplete, inTag );

            if ( threadID < threads.size() )
            {
                threads[threadID]->StartWork( workFunc );
            }
            else
            {
                queuedWork[static_cast< size_t >( inPriority )].emplace( workFunc );
            }

            return threadID;
        }

    private:
        size_t FindAvailableThread() const;
        void StartQueuedWork( threading_internal::CThreadObject& inOnThread );

        std::vector< threading_internal::CThreadObject* > threads;
        std::array< std::queue< std::shared_ptr< threading_internal::IWorkFunction > >, static_cast< size_t >( EPriority::SIZE ) > queuedWork;
        std::map< std::string, size_t > currentWorkCounters;
    };
}