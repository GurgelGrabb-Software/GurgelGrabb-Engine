#include "GG/Core/Threading/ThreadPool.h"

#include <chrono>

using namespace gg;

CThreadPool::CThreadPool( size_t inNumWantedThreads )
{
	threads.resize( inNumWantedThreads );
	for ( auto& p : threads )
	{
		p = new threading_internal::CThreadObject();
	}
}

CThreadPool::~CThreadPool()
{
	ShutDown();
}

void CThreadPool::CallOnCompletes( size_t inAllowedDurationInMilliseconds )
{
	auto start = std::chrono::system_clock::now();

	for ( auto& threadObject : threads )
	{
		if ( auto workFunc = threadObject->GetWorkFunction() )
		{
			if ( workFunc->IsCompleted() )
			{
				bool wasCompleted = workFunc->OnComplete();

				if ( wasCompleted )
				{
					currentWorkCounters[workFunc->GetTag()] -= 1;

					threadObject->Reset();

					StartQueuedWork( *threadObject );
				}
			}

			auto duration = ( std::chrono::system_clock::now() - start );
			if ( std::chrono::duration_cast< std::chrono::milliseconds >( duration ).count() >= inAllowedDurationInMilliseconds )
			{
				break;
			}
		}
	}
}

void CThreadPool::ShutDown()
{
	for ( auto& p : threads )
	{
		delete p;
		p = nullptr;
	}
	threads.clear();
}

size_t CThreadPool::ActiveWorkCount( const std::string& inWithID ) const
{
	size_t count = 0;

	if ( !inWithID.empty() )
	{
		auto it = currentWorkCounters.find( inWithID );
		if ( it != currentWorkCounters.end() )
		{
			count = it->second;
		}
	}
	else
	{
		for ( auto& [tag, counter] : currentWorkCounters )
		{
			count += counter;
		}
	}

	return count;
}

size_t CThreadPool::FindAvailableThread() const
{
	size_t index = 0;

	for ( auto& threadObject : threads )
	{
		if ( threadObject->GetWorkFunction() == nullptr )
		{
			break;
		}

		++index;
	}

	return index;
}

void CThreadPool::StartQueuedWork( threading_internal::CThreadObject& inOnThread )
{
	for ( auto& queuedWorkArray : queuedWork )
	{
		if ( !queuedWorkArray.empty() )
		{
			auto work = queuedWorkArray.front();
			inOnThread.StartWork( work );
			queuedWorkArray.pop();
			work.reset();
		}
	}
}