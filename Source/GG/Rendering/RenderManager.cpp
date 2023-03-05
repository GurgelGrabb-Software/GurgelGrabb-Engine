#include "GG/Rendering/RenderManager.h"

#include "GG/Core/Playground.h"
#include "GG/Core/Threading/ThreadPool.h"
#include "GG/Rendering/RenderTarget.h"

#include <iostream>

using namespace gg;

CPlayground* pg;

CRenderManager::CRenderManager( IRenderTarget& target, CThreadPool& threadPool )
	: _target( target )
	, _threadPool( threadPool )
{
}

void CRenderManager::Draw()
{
	if ( !pg ) pg = new CPlayground();

	pg->Update();
	pg->Draw( _target );
}