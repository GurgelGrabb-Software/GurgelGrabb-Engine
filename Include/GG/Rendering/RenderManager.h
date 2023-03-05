#pragma once

namespace gg
{
	class CRenderManager
	{
	public:
		CRenderManager( class IRenderTarget& target, class CThreadPool& threadPool );

		void Draw();

	private:
		IRenderTarget& _target;
		CThreadPool& _threadPool;
	};
} // namespace gg