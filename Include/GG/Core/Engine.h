#pragma once

#include "GG/Core/Service/ServiceProviderInterface.h"

namespace gg
{
    class CEngine
    {
    public:
        CEngine();
        ~CEngine();
        void Run();

        IServiceProvider& GetServiceProvider();
    
    private:
        IServiceProvider* _serviceProvider;

        // Service refs
        class CThreadPool& _threadPool;
    };
}