// GGTL (2023) - TChunkedList
// Sparse list that allocates in chunks when growing, ensuring all elements remain in place in memory

#pragma once
#include "GG/Common/Container/ChunkedList.h"
#include "GG/Common/Helpers/MemUtil.h"

namespace gg
{
	template < typename T, typename TSize = unsigned long long, unsigned short ChunkSize = 8u >
	class TChunkedList
	{
	private:
		struct SChunkedListIDX
		{
			SChunkedListIDX() = default;

			SChunkedListIDX( unsigned int eidx, unsigned int cidx )
				: elemIdx( eidx )
				, chunkIdx( cidx )
			{
			}

			bool operator==( const SChunkedListIDX& r ) const
			{
				return elemIdx == r.elemIdx && chunkIdx == r.chunkIdx;
			}

			bool operator!=( const SChunkedListIDX& r ) const
			{
				return operator==( r ) == false;
			}

			unsigned int elemIdx;
			unsigned int chunkIdx;
		};

	public:
		TChunkedList()
			: _free()
			, _chunks()
			, _size( 0 )
		{
			AllocChunk();
		}

		TChunkedList( const TChunkedList& r )
			: _free( r._free )
			, _chunks( r._chunks )
			, _size( r._size )
		{
		}

		TChunkedList( TChunkedList&& r ) noexcept
			: _free( std::move( r._free ) )
			, _chunks( std::move( r._chunks ) )
			, _size( std::exchange( r._size, 0 ) )
		{
		}

		~TChunkedList()
		{
			Clear();
		}

		T& operator[]( TSize idx )
		{
			return GetElem( ElemToListIdx( idx ) );
		}

		const T& operator[]( TSize idx ) const
		{
			return GetElem( ElemToListIdx( idx ) );
		}

		bool IsElementValid( TSize idx ) const
		{
			return !_free.Contains( ElemToListIdx( idx ) );
		}

		template < typename... TArgs >
		T& Emplace( TArgs&&... args )
		{
			SChunkedListIDX allocIdx;

			if ( !_free.IsEmpty() )
			{
				allocIdx = _free.Back();
				_free.Remove( _free.BackIndex() );
			}
			else
			{
				if ( _size == ReservedSize() )
				{
					AllocChunk();
				}

				allocIdx = ElemToListIdx( _size );
			}

			AllocAt< T, TArgs... >( GetElemSlotPtr( allocIdx ), std::forward< TArgs... >( args )... );
			_size++;
			return GetElem( allocIdx );
		}

		void Remove( TSize idx )
		{
			const SChunkedListIDX lidx = ElemToListIdx( idx );
			GetElem( lidx ).~T();
			_free.Add( lidx );
		}

		void Clear()
		{
			for ( TSize i = 0; i < _size; ++i )
			{
				const SChunkedListIDX i_lidx = ElemToListIdx( i );
				if ( _free.Contains( i_lidx ) )
				{
					continue;
				}
				GetElem( i_lidx ).~T();
			}

			for ( T* c : _chunks )
			{
				delete c;
			}
		}

		TSize ReservedSize() const
		{
			return _chunks.Size() * ChunkSize;
		}

	private:
		T* GetElemSlotPtr( SChunkedListIDX lidx )
		{
			return &_chunks[lidx.chunkIdx][lidx.elemIdx];
		}

		T& GetElem( SChunkedListIDX lidx )
		{
			return _chunks[lidx.chunkIdx][lidx.elemIdx];
		}

		const T& GetElem( SChunkedListIDX lidx ) const
		{
			return _chunks[lidx.chunkIdx][lidx.elemIdx];
		}

		void AllocChunk()
		{
			_chunks.Add( new T[ChunkSize] );
		}

		SChunkedListIDX ElemToListIdx( TSize idx ) const
		{
			const unsigned int chunkIdx = idx / ChunkSize;
			const unsigned int elemIdx = idx % ChunkSize;
			return SChunkedListIDX( static_cast< unsigned int >( elemIdx ), static_cast< unsigned int >( chunkIdx ) );
		}

		friend struct TChunkedListIterator;
		friend struct TChunkedListConstIterator;

		struct TChunkedListIterator
		{
		public:
			TChunkedListIterator( TChunkedList& parent, TSize idx )
				: _parentList( &parent )
				, _repIdx( idx )
			{
			}

			void operator++()
			{
				_repIdx++;
				if ( _repIdx >= _parentList->_size )
				{
					_repIdx = _parentList->_size;
					return;
				}
				else if ( !_parentList->IsElementValid( _repIdx ) )
				{
					operator++();
				}
			}

			bool operator==( const TChunkedListIterator& r ) const
			{
				return _repIdx == r._repIdx;
			}

			T& operator*()
			{
				return _parentList->operator[]( _repIdx );
			}

		private:
			TChunkedList< T, TSize, ChunkSize >* _parentList;
			TSize _repIdx;
		};

		struct TChunkedListConstIterator
		{
		public:
			TChunkedListConstIterator( const TChunkedList& parent, TSize idx )
				: _parentList( &parent )
				, _repIdx( idx )
			{
			}

			void operator++()
			{
				_repIdx++;
				if ( _repIdx >= _parentList->_size )
				{
					_repIdx = _parentList->_size;
					return;
				}
				else if ( !_parentList->IsElementValid( _repIdx ) )
				{
					operator++();
				}
			}

			bool operator==( const TChunkedListConstIterator& r ) const
			{
				return _repIdx == r._repIdx;
			}

			const T& operator*() const
			{
				return _parentList->operator[]( _repIdx );
			}

		private:
			const TChunkedList< T, TSize, ChunkSize >* _parentList;
			TSize _repIdx;
		};

	public:
		TChunkedListIterator begin()
		{
			return TChunkedListIterator( *this, 0 );
		}

		TChunkedListIterator end()
		{
			return TChunkedListIterator( *this, _size );
		}

		TChunkedListConstIterator begin() const
		{
			return TChunkedListConstIterator( *this, 0 );
		}

		TChunkedListConstIterator end() const
		{
			return TChunkedListConstIterator( *this, _size );
		}

	private:
		TList< SChunkedListIDX > _free;
		TList< T* > _chunks;
		TSize _size;
	};
} // namespace gg