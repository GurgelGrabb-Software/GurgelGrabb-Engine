#pragma once

namespace gg
{
	class IRenderTarget
	{
	public:
		virtual void Draw( const class CVertexBuffer& ) = 0;
	};
} // namespace gg