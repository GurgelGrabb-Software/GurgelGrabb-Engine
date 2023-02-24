#pragma once

#include <glm/Vec3.hpp>

namespace gg
{
	using Vec3_Back = glm::vec3;

	class CVec3
	{
	public:
		CVec3();
		CVec3( float x, float y, float z );
		CVec3( const CVec3& o );


		explicit operator Vec3_Back();
		explicit operator Vec3_Back() const;

	private:
		Vec3_Back _vec3;
        
    public:
    	float& X;
		float& Y;
		float& Z;

	};
} // namespace gg