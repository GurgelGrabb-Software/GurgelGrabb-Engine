#include "GG/Core/Playground.h"

#include "GG/Core/EntitySystem/Entity.h"
#include "GG/Core/Graphics/DrawableComponent.h"
#include "GG/Core/Objects/Transform.h"
#include "GG/Core/Utility/Timer.h"
#include "GG/Rendering/GraphicsUtilities.h"
#include "GG/Rendering/Image.h"
#include "GG/Rendering/RenderTarget.h"
#include "GG/Rendering/Shader.h"
#include "GG/Rendering/ShaderParser.h"
#include "GG/Rendering/ShaderProgram.h"
#include "GG/Rendering/Texture.h"
#include "GG/Rendering/VertexBuffer.h"

using namespace gg;

static std::shared_ptr< CVertexBuffer > vb;
static std::shared_ptr< CShaderProgram > sp;
static CTransform mat;
static CTimer timer;
static std::shared_ptr< CTexture > tex;
static CEntity* entity;

CPlayground::CPlayground()
{
	vb = GraphicsUtilities::CreateRectangleUV( 0.5f, 0.5f );

	entity = CEntity::Instantiate();
	entity->AddListener( this );

	CShaderParser parser;
	parser.ParseFromFile( "Shaders/defaults.ggs" );

	sp = std::make_shared< CShaderProgram >( CShader( parser.GetShaderSource( "P3UV2_Vertex" ).c_str(), EShaderType::Vertex ), CShader( parser.GetShaderSource( "P3UV2_Pixel" ).c_str(), EShaderType::Pixel ) );

	tex = std::make_shared< CTexture >( *CImage::LoadFromFile( "Textures/JGobSanta.png" ) );
}

void CPlayground::Update()
{
	float dt = timer.Reset();

	entity->GetTransform().SetScale( { 0.75f + 0.25f * std::cosf( timer.GetTotalTime() ), 0.75f + 0.25f * std::sinf( timer.GetTotalTime() ), 1 } );
	entity->GetTransform().SetPosition( { 0.5f * std::cosf( timer.GetTotalTime() ), 0.5f * std::sinf( timer.GetTotalTime() ), 0 } );
}

void CPlayground::Draw( IRenderTarget& target )
{
	CMat4x4 m = entity->GetTransform().GetMatrix();
	CMat4x4 p;

	p.SetOrthographic( -1, 1, -1, 1 );

	m *= p;

	sp->Bind();
	sp->SetUniform( "mvp", m );
	sp->SetUniform( "color", { 1, 1, 1, 1 } );
	sp->SetUniform( "tex", *tex );

	target.Draw( *vb );
}

void CPlayground::OnComponentAdded( TestComponent& comp )
{
	int hello = 0;
}

void CPlayground::OnComponentRemoved( TestComponent& comp ) { }