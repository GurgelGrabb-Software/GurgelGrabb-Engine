// GGTL (2023) - TList
// Sequential container like std::vector with sparse slots

#pragma once
#include "GG/Common/Container/List.h"

namespace gg
{
	template < typename T, typename TSize = size_t >
	class TSparseList
	{
	public:
		TSparseList()
			: _free()
			, _elems( nullptr )
			, _size( 0u )
			, _reserved( 0u )
		{
		}

		TSparseList( const TSparseList< T, TSize >& other )
			: _free( other._free )
			, _elems( new T[other._elems] )
			, _size( other._size )
			, _reserved( other._reserved )
		{
			BufferCopy< T >( other._elems, _elems, _size );
		}

		TSparseList( TSparseList< T, TSize >&& other ) noexcept
			: _free( std::forward( other._free ) )
			, _elems( std::exchange( other._elems, nullptr ) )
			, _size( std::exchange( other._size, 0u ) )
			, _reserved( std::exchange( other._reserved, 0u ) )
		{
		}

		TSparseList( std::initializer_list< T > initList )
			: _free()
			, _elems( new T[initList.size()] )
			, _size( initList.size() )
			, _reserved( initList.size() )
		{
			TSize ei = 0u;
			for ( auto&& i : initList )
			{
				_elems[ei] = i;
				ei++;
			}
		}

		~TSparseList() { }

		[[nodiscard]] T& operator[]( TSize i )
		{
			return _elems[i];
		}

		[[nodiscard]] const T& operator[]( TSize i ) const
		{
			return _elems[i];
		}

		template < typename... TArgs >
		T& Emplace( TArgs&&... args )
		{
			TSize i;
			if ( _free.IsEmpty() )
			{
				if ( _size == _reserved )
				{
					Reserve( _reserved * 2 );
				}
				i = _size;
				_size++;
			}
			else
			{
				_free.PopBack( &i );
			}

			AllocAt( &_elems[i], std::forward( args... ) );
			return _elems[i];
		}

		T& Add( const T& cpy ) 
        {
            TSize i;
            if(_free.IsEmpty())
            {
                if(_size == _reserved)
                {
                    Reserve(_reserved * 2);
                }
                i = _size;
                _size++;
            }
            else
            {
                _free.PopBack(&i);
                KeepMemDestroy<T>(_elems[i]);
            }

            BufferCopy( &cpy, &_elems[i], 1 );
            return _elems[i];
        }

		void Remove( TSize i ) 
        {
			_elems[i].~T();
            _free.Add(i);
        }

		void Reserve( TSize s ) 
        {
            T* newBuff = new T[s];
            if(_elems)
            {
                BufferMove( _elems, newBuff, _size );
                delete[] _elems;
            }
            _reserved = s;
            _elems = newBuff;
        }

		TSize Size() const
		{
			return _size;
		}

		TSize Reserved() const
		{
			return _reserved;
		}

		TSize FreeSlots() const
		{
			return _free.Size();
		}

	private:
		TList< TSize, TSize > _free;
		T* _elems;
		TSize _size;
		TSize _reserved;
	};
} // namespace gg