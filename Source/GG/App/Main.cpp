#include <GG/Core/Engine.h>
#include <GG/Game/GameSystem.h>

int main( int argc, char* argv[] )
{
	gg::CEngine engine;
	engine.Run( new gg::CGameSystem() );
	return 0;
}