#include "GG/Core/Playground.h"

#include "GG/Rendering/GraphicsUtilities.h"
#include "GG/Rendering/Shader.h"
#include "GG/Rendering/ShaderParser.h"
#include "GG/Rendering/ShaderProgram.h"
#include "GG/Rendering/VertexBuffer.h"
#include "GG/Rendering/RenderTarget.h"
#include "GG/Rendering/Texture.h"
#include "GG/Rendering/Image.h"

#include "GG/Core/Objects/Transform.h"
#include "GG/Core/Utility/Timer.h"

using namespace gg;

static std::shared_ptr<CVertexBuffer> vb;
static std::shared_ptr<CShaderProgram> sp;
static CTransform mat;
static CTimer timer;
static std::shared_ptr<CTexture> tex;

CPlayground::CPlayground() {
    vb = GraphicsUtilities::CreateRectangleUV(0.5f, 0.5f);

    CShaderParser parser;
    parser.ParseFromFile("Shaders/defaults.ggs");

    sp = std::make_shared<CShaderProgram>(
        CShader(parser.GetShaderSource("P3UV2_Vertex").c_str(), EShaderType::Vertex),
        CShader(parser.GetShaderSource("P3UV2_Pixel").c_str(), EShaderType::Pixel));

    tex = std::make_shared<CTexture>(*CImage::LoadFromFile("Textures/JGobSanta.png"));

 }

void CPlayground::Update() 
{ 
    float dt = timer.Reset();

    mat.SetScale({0.75f + 0.25f * std::cosf(timer.GetTotalTime()), 0.75f + 0.25f * std::sinf(timer.GetTotalTime()), 1});
    mat.SetPosition({0.5f * std::cosf(timer.GetTotalTime()), 0.5f * std::sinf(timer.GetTotalTime()), 0});
}

void CPlayground::Draw(IRenderTarget& target)
{
    CMat4x4 m = mat.GetMatrix();
    CMat4x4 p;

    p.SetOrthographic(-1, 1, -1, 1);

    m *= p;

    sp->SetUniform("mvp", m);
    sp->SetUniform("color", {1,1,1,1});
    sp->SetUniform("tex", *tex);

    target.Draw(*vb, *sp);
}