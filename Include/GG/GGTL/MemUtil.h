#pragma once
#include <type_traits>
#include <cstring>

namespace gg
{
    template < typename T, bool B >
    struct BufCpyT
    {
        static void Cpy( const T* src, T* dst, unsigned int num )
        {
        }
    };

    template < typename T >
    struct BufCpyT< T, true >
    {
        static void Cpy(const T* src, T* dst, unsigned int num)
        {
            size_t cpyB = sizeof(T) * num;
            memcpy_s( dst, cpyB, src, cpyB );
        }
    };

    template < typename T >
    struct BufCpyT<T, false>
    {
        static void Cpy(const T* src, T* dst, unsigned int num)
        {
            for(unsigned i = 0; i < num; ++i)
            {
                dst[i] = src[i];
            }
        }
    };

    template < typename T >
    static void BufferCopy( const T* src, T* dst, unsigned int num ) 
    {
         BufCpyT< T, std::is_trivially_copyable<T>::value>::Cpy(src, dst, num);
    }
}