#include "GG/Core/Math/Mat4x4.h"

#include <glm/vec3.hpp>

#define IDENTITY_R1 1, 0, 0, 0
#define IDENTITY_R2 0, 1, 0, 0
#define IDENTITY_R3 0, 0, 1, 0
#define IDENTITY_R4 0, 0, 0, 1

gg::CMat4x4::CMat4x4()
	: _matrix( IDENTITY_R1, IDENTITY_R2, IDENTITY_R3, IDENTITY_R4 )
{
}

gg::CMat4x4::CMat4x4( const Mat4x4_Back& backend )
	: _matrix( backend )
{
}

gg::CMat4x4 gg::CMat4x4::GetTransposed() const
{
	return glm::transpose( _matrix );
}

gg::CMat4x4 gg::CMat4x4::GetInverse() const
{
	return glm::inverse( _matrix );
}

gg::CMat4x4 gg::CMat4x4::operator*( const CMat4x4& rhs ) const
{
	return _matrix * rhs._matrix;
}

gg::CMat4x4& gg::CMat4x4::operator*=( const CMat4x4& rhs )
{
	_matrix *= rhs._matrix;
	return *this;
}

gg::CMat4x4::operator gg::Mat4x4_Back()
{
    return _matrix;
}