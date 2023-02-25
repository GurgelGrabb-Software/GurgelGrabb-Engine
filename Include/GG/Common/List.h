// GGTL (2023) - TList
// Sequential container like std::vector

#pragma once
#include "GG/Common/MemUtil.h"

#include <initializer_list>
#include <type_traits>
#include <utility>

namespace gg
{
	// DECL
	template < typename T, typename TSize = size_t >
	class TList
	{
	public:
		// CTOR/DTOR
		TList();
		TList( TSize reserve );
		TList( const TList< T, TSize >& other );
		TList( TList< T, TSize >&& other ) noexcept;
		TList( std::initializer_list< T > initList );
		~TList();

		// OPERATOR
		[[nodiscard]] T& operator[]( TSize i );
		[[nodiscard]] const T& operator[]( TSize i ) const;

		// MUTATORS
		T& Add( const T& cpy );
		void Remove( TSize i );
		void Reserve( TSize s );

		// GETTERS
		TSize Size() const;
		TSize Reserved() const;

	public:
		class TIt
		{
		public:
			TIt( T* e, TSize idx )
				: _e( e )
				, _idx( idx )
			{
			}
			void operator--()
			{
				_idx--;
			}
			void operator++()
			{
				_idx++;
			}
			bool operator==( const TIt& r )
			{
				return _idx == r._idx;
			}
			bool operator!=( const TIt& r )
			{
				return _idx != r._idx;
			}
			T& operator*()
			{
				return _e[_idx];
			}

		private:
			T* _e;
			TSize _idx;
		};

		class TCIt
		{
		public:
			TCIt( const T* e, TSize idx )
				: _e( e )
				, _idx( idx )
			{
			}
			void operator--()
			{
				_idx--;
			}
			void operator++()
			{
				_idx++;
			}
			bool operator==( const TCIt& r )
			{
				return _idx == r._idx;
			}
			bool operator!=( const TCIt& r )
			{
				return _idx != r._idx;
			}
			const T& operator*()
			{
				return _e[_idx];
			}

		private:
			const T* _e;
			TSize _idx;
		};

		TIt begin()
		{
			return TIt( _elems, 0 );
		}
		TIt end()
		{
			return TIt( _elems, _size );
		}
		TCIt begin() const
		{
			return TCIt( _elems, 0 );
		}
		TCIt end() const
		{
			return TCIt( _elems, _size );
		}

	private:
		T* _elems;
		TSize _reserved;
		TSize _size;
	};

// clang-format off
#define LIST_T template < typename T, typename TSize >
#define LIST TList<T, TSize>
	// clang-format on

	// DEF
	LIST_T LIST::TList()
		: _elems( new T[16] )
		, _reserved( 16 )
		, _size( 0 )
	{
	}

	LIST_T LIST::TList( TSize reserve )
		: TList()
		, _reserved( 0 )
		, _size( 0 )
	{
		Reserve( reserve );
	}

	LIST_T LIST::TList( const TList< T, TSize >& other )
		: _elems( new T[other._reserved] )
		, _reserved( other._reserved )
		, _size( other._size )
	{
		BufferCopy< T >( other._elems, _elems, _size );
	}

	LIST_T LIST::TList( TList< T, TSize >&& other ) noexcept
		: _elems( std::exchange( other._elems, nullptr ) )
		, _reserved( std::exchange( other._reserved, 0 ) )
		, _size( std::exchange( other._size, 0 ) )
	{
	}

	LIST_T LIST::TList( std::initializer_list< T > initList )
		: _elems( new T[initList.size()] )
		, _reserved( initList.size() )
		, _size( initList.size() )
	{
		TSize i = 0;
		for ( const auto& ilt : initList )
		{
			_elems[i] = ilt;
			i++;
		}
	}

	LIST_T LIST::~TList()
	{
		if ( _elems )
		{
			delete[] _elems;
		}
	}

	LIST_T T& LIST::operator[]( TSize i )
	{
		return _elems[i];
	}

	LIST_T const T& LIST::operator[]( TSize i ) const
	{
		return _elems[i];
	}

	LIST_T T& LIST::Add( const T& cpy )
	{
		if ( _size == _reserved )
		{
			Reserve( _reserved * 2 );
		}

		_elems[_size] = cpy;
		++_size;
		return _elems[_size - 1];
	}

	LIST_T void LIST::Remove( TSize i )
	{
		_elems[i] = _elems[_size - 1];
		_size--;
	}

	LIST_T void LIST::Reserve( TSize s )
	{
		T* newBuf = new T[s];
		BufferCopy< T >( _elems, newBuf, (unsigned int)_size );
		delete[] _elems;

		_reserved = s;
		_elems = newBuf;
	}

	LIST_T TSize LIST::Size() const
	{
		return _size;
	}

	LIST_T TSize LIST::Reserved() const
	{
		return _reserved;
	}
#undef LIST_T
#undef LIST

} // namespace gg