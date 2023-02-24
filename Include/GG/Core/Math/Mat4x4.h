#pragma once

#include <glm/mat4x4.hpp>
#include <GG/Core/Math/Vec3.h>

namespace gg
{
    using Mat4x4_Back = glm::mat4x4;

	class CMat4x4
	{
    public:
        CMat4x4();
        CMat4x4( const Mat4x4_Back& backend );

        CMat4x4 GetTransposed() const;
        CMat4x4 GetInverse() const;

        CMat4x4 operator*(const CMat4x4& rhs) const;
        CMat4x4& operator*=(const CMat4x4& rhs);

        CMat4x4& SetIdentity();
        CMat4x4& Translate(const CVec3& translation);
        CMat4x4& Rotate(float angle, const CVec3& axis);
        CMat4x4& Scale(const CVec3& scale);

        CMat4x4 operator*(const CMat4x4& other);

        CMat4x4& SetOrthographic(float left, float right, float top, float bottom, float near=-1.f, float far = 1.f);
        CMat4x4& SetPerspective(float fovY, float aspect, float near, float far);
        
        const float* GetData() const;

        // Allow static cast to the backend type
        explicit operator Mat4x4_Back();

	private:
        Mat4x4_Back _matrix;
	};
} // namespace gg