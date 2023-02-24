
#include "GG/Rendering/GraphicsUtilities.h"
#include "GG/Rendering/VertexBuffer.h"
#include <cmath>

using namespace gg;

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateTriangle(float size, EVertexFormat format)
{
    auto buffer = std::make_shared<CVertexBuffer>(format);
	buffer->SetPrimitiveType(EPrimitiveType::Triangles);

	//const float hs = size * std::sqrtf(3.f) / 3.f;
	//const float PI2 = 3.14159f * 2.f;
	//SFloat3 v[3] = {
	//	{.x = hs*std::sinf(PI2 * 1.f/3.f), .y=hs*std::cosf(PI2 * 1.f/3.f)},
	//	{.x = hs*std::sinf(0.f),           .y=hs*std::cosf(0.f)},
	//	{.x = hs*std::sinf(PI2 * 2.f/3.f), .y=hs*std::cosf(PI2 * 2.f/3.f)},
	//};
	const float hs = 0.5f * size;
	SFloat3 v[3] = {
		{.x = -hs, .y = hs},
		{.x = 0.f, .y = -hs},
		{.x = hs, .y = hs},
	};
	std::vector<float> buf(GetNumOfElements(EAttributeType::Position) * 3);
	memcpy(buf.data(), v, buf.size() * sizeof(float));
	buffer->SetAttributeData(EAttributeType::Position, buf);

    return buffer;
}

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateRectangle(float width, float height, EVertexFormat format)
{
	auto buffer = std::make_shared<CVertexBuffer>(format);
	buffer->SetPrimitiveType(EPrimitiveType::Triangles);

	const float hw = 0.5f * width;
	const float hh = 0.5f * height;

	SFloat3 tl{.x =-hw, .y = -hh};
	SFloat3 tr{.x = hw, .y = -hh};
	SFloat3 br{.x = hw, .y =  hh};
	SFloat3 bl{.x =-hw, .y =  hh};

	SFloat3 v[6] = {
		tl, tr, bl,
		bl, tr, br
	};
	std::vector<float> buf(GetNumOfElements(EAttributeType::Position) * 6);
	memcpy(buf.data(), v, buf.size() * sizeof(float));
	buffer->SetAttributeData(EAttributeType::Position, buf);

	return buffer;
}

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateCircle(float diameter, int resolution, EVertexFormat format)
{
	auto buffer = std::make_shared<CVertexBuffer>(format);
	buffer->SetPrimitiveType(EPrimitiveType::TriangleFan);
	const float r = 0.5f * diameter;
	SFloat3* v = new SFloat3[resolution+1];
	float angle = 0.f;
	for (int i = 0; i < resolution+1; ++i)
	{
		v[i] = {.x = r * std::cosf(angle), .y = r * std::sinf(angle)};
		angle += 2.f * 3.14159f / resolution;
	}

	std::vector<float> buf(GetNumOfElements(EAttributeType::Position) * (resolution+1));
	memcpy(buf.data(), v, buf.size() * sizeof(float));
	buffer->SetAttributeData(EAttributeType::Position, buf);

	delete[] v;

	return buffer;
}

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateRectangle(float width, float height, const SFloat4& color)
{
	auto buffer = CreateRectangle(width, height, EVertexFormat::P3C4);
	SetVertexAttributes<SFloat4>(*buffer, EAttributeType::Color, color);

	return buffer;
}

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateTriangle(float size, const SFloat4& color)
{
	auto buffer = CreateTriangle(size, EVertexFormat::P3C4);
	SetVertexAttributes<SFloat4>(*buffer, EAttributeType::Color, color);

	return buffer;
}

std::shared_ptr<CVertexBuffer> GraphicsUtilities::CreateCircle(float size, const SFloat4& color, int resolution)
{
	auto buffer = CreateCircle(size, resolution, EVertexFormat::P3C4);
	SetVertexAttributes<SFloat4>(*buffer, EAttributeType::Color, color);

	return buffer;
}