#include <GG/Common/Container/List.h>
#include <gtest/gtest.h>

// NO CTOR EXCEPTION
TEST( TList, Test_TList_Ctors_NoThrow )
{
	EXPECT_NO_THROW( gg::TList< int > l );		  // Default
	EXPECT_NO_THROW( gg::TList< int > l( 10u ) ); // Reserve

	gg::TList< int > cpy;
	EXPECT_NO_THROW( gg::TList< int > l( cpy ) ); // Copy

	gg::TList< int > mv;
	EXPECT_NO_THROW( gg::TList< int > l( std::move( mv ) ) ); // Move

	EXPECT_NO_THROW( gg::TList< int > l( { 10, 20, 30 } ) ); // Init list
}

// CTOR BEHAVIOUR
TEST( TList, Test_TList_DefaultCtor_ReserveNonZero_SizeZero )
{
	gg::TList< int > l;
	EXPECT_EQ( l.Size(), 0 );
	EXPECT_NE( l.Reserved(), 0 );
}

TEST( TList_Ctor, Test_TList_DefaultCtor_ReserveArg_SizeZero )
{
	constexpr size_t r = 10u;
	gg::TList< int > l( r );
	EXPECT_EQ( l.Size(), 0 );
	EXPECT_EQ( l.Reserved(), r );
}

TEST( TList_Ctor, Test_TList_InitListCtor_SizeAndReserveMatchList )
{
	gg::TList< int > l( { 10, 20, 30, 40 } );
	EXPECT_EQ( l.Size(), 4 );
	EXPECT_EQ( l.Reserved(), 4 );
}

TEST( TList_Ctor, Test_TList_CopyCtor_SizeAndReserveMatchSource )
{
	gg::TList< int > a( { 10, 20, 30, 40 } );
	gg::TList< int > b( a );

	EXPECT_EQ( a.Size(), b.Size() );
	EXPECT_EQ( a.Reserved(), b.Reserved() );
}

TEST( TList_Ctor, Test_TList_MoveCtor_SizeAndReservedMatchSource_SourceAtZero )
{
	gg::TList< int > a( { 10, 20, 30, 40 } );
	gg::TList< int > b( std::move( a ) );

	EXPECT_EQ( b.Size(), 4 );
	EXPECT_EQ( b.Reserved(), 4 );
	EXPECT_EQ( a.Size(), 0 );
	EXPECT_EQ( a.Reserved(), 0 );
}