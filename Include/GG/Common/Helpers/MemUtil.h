#pragma once
#include <cstring>
#include <type_traits>
#include <new>

namespace gg
{
	namespace mem_util_internal
	{
		template < typename T, bool B >
		struct BufCpyT
		{
			static void Cpy( const T* src, T* dst, unsigned int num ) { }
		};

		template < typename T >
		struct BufCpyT< T, true >
		{
			static void Cpy( const T* src, T* dst, unsigned int num )
			{
				size_t cpyB = sizeof( T ) * num;
				memcpy_s( dst, cpyB, src, cpyB );
			}
		};

		template < typename T >
		struct BufCpyT< T, false >
		{
			static void Cpy( const T* src, T* dst, unsigned int num )
			{
				for ( unsigned i = 0; i < num; ++i )
				{
					dst[i] = src[i];
				}
			}
		};
	} // namespace mem_util_internal

	/// @brief Copy elements from src to dst buffer using memcpy if trivially copyable, otherwise copy assign
	/// @tparam T Element type
	/// @param src Buffer to copy from
	/// @param dst Buffer to copy to
	/// @param num Num elements (T) to copy 
	template < typename T >
	static void BufferCopy( const T* src, T* dst, unsigned int num )
	{
		mem_util_internal::BufCpyT< T, std::is_trivially_copyable< T >::value >::Cpy( src, dst, num );
	}

    /// @brief Allocate the type T at the given dst address
    /// @tparam T Type to allocate
    /// @tparam ...TArgs Ctor arguments
    /// @param dst The address to allocate at
    /// @param ...args Ctor args
    template < typename T, typename ... TArgs >
    static void AllocAt( void* dst, TArgs&&... args  )
    {
        new(dst) T(args...);
    }

    /// @brief Sets the memory to 0
    /// @tparam T Type to use for size determine (default 1B)
    /// @param dst Start address of memory
    /// @param numT The offset in T to set the memory for (sizeof(T) * numT)
    template <typename T = unsigned char>
    static void ZeroMem( void* dst, size_t numT = 1 )
    {
        memset( dst, 0, sizeof(T) * numT );
    }

} // namespace gg