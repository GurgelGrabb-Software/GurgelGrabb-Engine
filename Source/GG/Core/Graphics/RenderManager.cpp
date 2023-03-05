#include "GG/Core/Graphics/RenderManager.h"

#include "GG/Core/EntitySystem/Entity.h"
#include "GG/Core/Playground.h"
#include "GG/Core/Threading/ThreadPool.h"
#include "GG/Rendering/GraphicsUtilities.h"
#include "GG/Rendering/Image.h"
#include "GG/Rendering/RenderTarget.h"
#include "GG/Rendering/Shader.h"
#include "GG/Rendering/ShaderParser.h"
#include "GG/Rendering/ShaderProgram.h"
#include "GG/Rendering/Texture.h"
#include "GG/Rendering/VertexBuffer.h"

#include <iostream>

using namespace gg;

CRenderManager::CRenderManager( IRenderTarget& target, CThreadPool& threadPool )
	: _target( target )
	, _threadPool( threadPool )
{
	_defaults.texturedSquare = GraphicsUtilities::CreateRectangleColorUV( 1.f, 1.f, { 1, 1, 1, 1 } );
	_defaults.texture = std::make_shared< CTexture >( *CImage::LoadFromFile( "Textures/default.png" ) );

	CShaderParser parser;
	parser.ParseFromFile( "Shaders/defaults.ggs" );

	const auto& vs = parser.GetShaderSource( "P3C4UV2_Vertex" );
	const auto& ps = parser.GetShaderSource( "P3C4UV2_Pixel" );

	_defaults.program = std::make_shared< CShaderProgram >( CShader( vs.c_str(), EShaderType::Vertex ), CShader( ps.c_str(), EShaderType::Pixel ) );
}

void CRenderManager::Draw()
{
	for ( auto& drawable : _drawables )
	{
		if ( drawable.entity )
		{
			drawable.world = drawable.entity->GetTransform().GetMatrix();
		}

		_defaults.program->Bind();
		_defaults.program->SetUniform( "mvp", drawable.world );
		_defaults.program->SetUniform( "color", { 1, 1, 1, 1 } );
		_defaults.program->SetUniform( "tex", *_defaults.texture );

		_target.Draw( *_defaults.texturedSquare );
	}
}

void CRenderManager::OnComponentAdded( CDrawableComponent& component )
{
	_drawables.Add( { .entity = &component.GetOwner() } );
}

void CRenderManager::OnComponentChanged( CDrawableComponent& component ) { }

void CRenderManager::OnComponentRemoved( CDrawableComponent& component ) { }
