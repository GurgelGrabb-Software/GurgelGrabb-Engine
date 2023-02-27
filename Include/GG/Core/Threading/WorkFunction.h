#pragma once

#include <string>

namespace gg
{
    namespace threading_internal
    {
        class IWorkFunction
        {
        public:
            IWorkFunction() = default;
            IWorkFunction& operator=( IWorkFunction&& ) = default;
            IWorkFunction( IWorkFunction&& ) = default;

            IWorkFunction( const IWorkFunction& ) = delete;
            IWorkFunction& operator=( const IWorkFunction& ) = delete;

            virtual ~IWorkFunction() = default;

            virtual bool IsCompleted() const = 0;
            virtual const std::string& GetTag() const = 0;

            virtual void Work() = 0;
            virtual bool OnComplete() = 0;
        };

        template < typename TWorkReturnType >
        class TWorkFunction : public IWorkFunction
        {
        public:
            TWorkFunction() = default;
            TWorkFunction& operator=( TWorkFunction&& ) = default;
            TWorkFunction( TWorkFunction&& ) = default;

            TWorkFunction( const TWorkFunction& ) = delete;
            TWorkFunction& operator=( const TWorkFunction& ) = delete;

            TWorkFunction( const std::function< TWorkReturnType() >& inWork, const std::function< void( const TWorkReturnType& ) >& inOnComplete, const std::string& inTag = std::string() )
                : work( inWork )
                , onComplete( inOnComplete )
                , completed( false )
                , tag( inTag )
            {
            }

            virtual bool IsCompleted() const override
            {
                return completed;
            }

            virtual const std::string& GetTag() const override
            {
                return tag;
            }

            virtual void Work() override
            {
                if ( work )
                {
                    result = work();
                    work = nullptr;
                    completed = true;
                }
            }

            virtual bool OnComplete() override
            {
                if ( onComplete )
                {
                    onComplete( result );
                    onComplete = nullptr;

                    return true;
                }

                return false;
            }

        private:
            std::function< TWorkReturnType() > work;
            std::function< void( const TWorkReturnType& ) > onComplete;

            TWorkReturnType result;
            bool completed;
            std::string tag;
        };
    }
}