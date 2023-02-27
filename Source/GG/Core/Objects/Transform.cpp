#include "GG/Core/Objects/Transform.h"

using namespace gg;

CTransform::CTransform()
	: _position( 0, 0, 0 )
	, _scale( 1, 1, 1 )
	, _dirty( true )
{
}

CMat4x4 CTransform::GetMatrix() const
{
	CMat4x4 m;
	if ( _dirty )
	{
		m.Translate( _position );
		m.Scale( _scale );
	}
	else
	{
		m = _mat;
	}
	return m;
}

const CMat4x4& CTransform::GetMatrix()
{
	if ( _dirty )
	{
		_mat.SetIdentity();
		_mat.Translate( _position );
		_mat.Scale( _scale );
        _dirty = false;
	}
	return _mat;
}

void CTransform::SetPosition( const CVec3& position )
{
	_position = position;
	_dirty = true;
}

void CTransform::SetScale( const CVec3& scale )
{
	_scale = scale;
	_dirty = true;
}