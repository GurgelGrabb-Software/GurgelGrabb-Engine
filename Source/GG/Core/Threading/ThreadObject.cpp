#include "GG/Core/Threading/ThreadObject.h"

#include "GG/Core/Threading/WorkFunction.h"

using namespace gg;

threading_internal::CThreadObject::CThreadObject()
    : terminateThread( false )
{
    thread = std::thread( std::bind( &CThreadObject::Loop, this ) );
}

threading_internal::CThreadObject::~CThreadObject()
{
    std::unique_lock< std::mutex > lock( workMutex );
    terminateThread = true;

    condition.notify_one();

    lock.unlock();

    thread.join();
}

threading_internal::IWorkFunction* threading_internal::CThreadObject::GetWorkFunction() const
{
    return workFunction.get();
}

void threading_internal::CThreadObject::StartWork( std::shared_ptr< IWorkFunction > inWorkFunction )
{
    std::unique_lock< std::mutex > lock( workMutex );
    workFunction = inWorkFunction;

    condition.notify_one();
}

void threading_internal::CThreadObject::Loop()
{
    while ( !terminateThread )
    {
        std::unique_lock< std::mutex > lock( workMutex );
        condition.wait( lock, [this]() { return ( workFunction != nullptr && !workFunction->IsCompleted() ) || terminateThread; } );

        if ( !terminateThread )
        {
            if ( workFunction && !workFunction->IsCompleted() )
            {
                workFunction->Work();
            }
        }
    }
}