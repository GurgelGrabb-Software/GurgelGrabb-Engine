#include "GG/Core/Math/Mat4x4.h"

#include <glm/Vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

gg::CMat4x4& gg::CMat4x4::SetIdentity()
{
	_matrix = glm::identity<glm::mat4x4>();
	return *this;
}

gg::CMat4x4& gg::CMat4x4::Translate(const gg::CVec3& translation)
{
	_matrix = glm::translate(_matrix, static_cast<glm::vec3>(translation));
	return *this;
}

gg::CMat4x4& gg::CMat4x4::Rotate(float angle, const gg::CVec3& axis)
{
	_matrix = glm::rotate(_matrix, angle, static_cast<glm::vec3>(axis));
	return *this;
}

gg::CMat4x4& gg::CMat4x4::Scale(const gg::CVec3& scale)
{
	_matrix = glm::scale(_matrix, static_cast<glm::vec3>(scale));
	return *this;
}

gg::CMat4x4 gg::CMat4x4::operator*(const CMat4x4& other)
{
	return _matrix * other._matrix;
}

gg::CMat4x4& gg::CMat4x4::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
{
	_matrix = glm::ortho(left, right, bottom, top, near, far);
	return *this;

}
gg::CMat4x4& gg::CMat4x4::SetPerspective(float fovY, float aspect, float near, float far)
{
	_matrix = glm::perspective(fovY, aspect, near, far);
	return *this;
}

const float* gg::CMat4x4::GetData() const
{
	return &_matrix[0][0];
}

gg::CMat4x4::operator gg::Mat4x4_Back()
{
    return _matrix;
}