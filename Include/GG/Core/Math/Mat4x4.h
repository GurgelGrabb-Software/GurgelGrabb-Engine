#include <glm/mat4x4.hpp>

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
        
        const float* GetData() const;

        // Allow static cast to the backend type
        explicit operator Mat4x4_Back();

	private:
        Mat4x4_Back _matrix;
	};
} // namespace gg