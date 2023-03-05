#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace gg
{
	namespace threading_internal
	{
		class IWorkFunction;

		class CThreadObject
		{
		public:
			CThreadObject& operator=( CThreadObject&& ) = delete;
			CThreadObject( CThreadObject&& ) = delete;

			CThreadObject( const CThreadObject& ) = delete;
			CThreadObject& operator=( const CThreadObject& ) = delete;

			CThreadObject();
			~CThreadObject();

			IWorkFunction* GetWorkFunction() const;
			void Reset();

			void StartWork( std::shared_ptr< IWorkFunction > inWorkFunction );

		private:
			void Loop();

			std::atomic_bool terminateThread;

			std::mutex workMutex;
			std::shared_ptr< IWorkFunction > workFunction;

			std::condition_variable condition;
			std::thread thread;
		};
	} // namespace threading_internal
} // namespace gg