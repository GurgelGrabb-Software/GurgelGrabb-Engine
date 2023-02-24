#include "GG/Core/Math/Vec3.h"

gg::CVec3::CVec3()
	: _vec3( 0, 0, 0 )
	, X( _vec3.x )
	, Y( _vec3.y )
	, Z( _vec3.z )
{
}

gg::CVec3::CVec3( float x, float y, float z )
	: _vec3( x, y, z )
	, X( _vec3.x )
	, Y( _vec3.y )
	, Z( _vec3.z )
{
}

gg::CVec3::CVec3(const CVec3& o)
    : _vec3(o._vec3)
    , X( _vec3.x )
	, Y( _vec3.y )
	, Z( _vec3.z )
{
}

gg::CVec3::operator gg::Vec3_Back()
{
    return _vec3;
}

gg::CVec3::operator gg::Vec3_Back() const
{
    return _vec3;
}