#pragma once

#include "GG/Core/Math/Mat4x4.h"
#include "GG/Core/Math/Vec3.h"

namespace gg
{
    class CTransform
    {
    public:

        CTransform();

        CMat4x4 GetMatrix() const;
        const CMat4x4& GetMatrix();

        void SetPosition(const CVec3& position);
        void SetScale(const CVec3& scale);
        //void SetRotation(const CQuat& rotation);

    private:

        bool _dirty;

        CVec3 _position;
        CVec3 _scale;
        //CQuat _rotation;
        
        CMat4x4 _mat;
    };
}