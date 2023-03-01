// GGTL (2023) - TList
// Sequential container like std::vector

#pragma once
#include "GG/Common/Helpers/MemUtil.h"

#include <initializer_list>
#include <type_traits>
#include <utility>

namespace gg
{
	template < typename T, typename TSize = size_t >
	class TList
	{
	public: // CTOR/DTOR
		TList()
			: _elems( new T[16] )
			, _reserved( 16 )
			, _size( 0 )
		{
		}

		TList( TSize reserve )
			: _elems( nullptr )
			, _reserved( 0 )
			, _size( 0 )
		{
			Reserve( reserve );
		}

		TList( const TList< T, TSize >& other )
			: _elems( new T[other._reserved] )
			, _reserved( other._reserved )
			, _size( other._size )
		{
			BufferCopy< T >( other._elems, _elems, _size );
		}

		TList( TList< T, TSize >&& other ) noexcept
			: _elems( std::exchange( other._elems, nullptr ) )
			, _reserved( std::exchange( other._reserved, 0 ) )
			, _size( std::exchange( other._size, 0 ) )
		{
		}

		TList( std::initializer_list< T > initList )
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

		~TList()
		{
			if ( _elems )
			{
				Clear();
				delete _elems;
			}
		}

	public: // OPERATORS
		[[nodiscard]] T& operator[]( TSize i )
		{
			return _elems[i];
		}

		[[nodiscard]] const T& operator[]( TSize i ) const
		{
			return _elems[i];
		}

	public: // MUTATORS
		template < typename... TArgs >
		T& Emplace( TArgs&&... args )
		{
		}

		T& Add( const T& cpy )
		{
			if ( _size == _reserved )
			{
				Reserve( _reserved * 2 );
			}

			_elems[_size] = cpy;
			++_size;
			return _elems[_size - 1];
		}

		T& Back()
		{
			return _elems[_size - 1];
		}

		const T& Back() const
		{
			return _elems[_size - 1];
		}

		const TSize BackIndex() const
		{
			return _size - 1;
		}

		void PopBack( T* set = nullptr )
		{
			if ( set != nullptr )
			{
				*set = _elems[_size - 1];
			}

			Remove( _size - 1 );
		}

		void Remove( TSize i )
		{
			_elems[i] = _elems[_size - 1];
			_size--;
		}

		void Reserve( TSize s )
		{
			T* newBuf = new T[s];
			if ( _elems )
			{
				BufferCopy< T >( _elems, newBuf, (unsigned int)_size );
				delete[] _elems;
			}

			_reserved = s;
			_elems = newBuf;
		}

		void Clear()
		{
			for ( TSize i = 0; i < _size; ++i )
			{
				_elems[i].~T();
				ZeroMem( &_elems[i], sizeof( T ) );
			}
			_size = 0;
		}

	public: // ACCESSORS
		bool IsEmpty() const
		{
			return _size == 0u;
		}

		TSize Size() const
		{
			return _size;
		}

		TSize Reserved() const
		{
			return _reserved;
		}

		bool Contains(const T& e) const
		{
			for(TSize i = 0; i < _size; ++i)
			{
				if(_elems[i] == e)
				{
					return true;
				}
			}

			return false;
		}

	public: // ITERATORS
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
} // namespace gg