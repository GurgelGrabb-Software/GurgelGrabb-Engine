#include "GG/Rendering/InputTypes.h"

#include <unordered_map>

// clang-format off

using namespace gg;

#define PAIR( k )                                                                                                                                                                                      \
	{                                                                                                                                                                                                  \
		EInputCode::k, #k                                                                                                                                                                              \
	}

const std::string& gg::ToString( EInputCode inputCode )
{
	static auto empty = std::string( "" );
	static std::unordered_map< EInputCode, std::string > values = {
		PAIR( KEY_A ),
		PAIR( KEY_B ),
		PAIR( KEY_C ),
		PAIR( KEY_D ),
		PAIR( KEY_E ),
		PAIR( KEY_F ),
		PAIR( KEY_G ),
		PAIR( KEY_H ),
		PAIR( KEY_I ),
		PAIR( KEY_J ),
		PAIR( KEY_K ),
		PAIR( KEY_L ),
		PAIR( KEY_M ),
		PAIR( KEY_N ),
		PAIR( KEY_O ),
		PAIR( KEY_P ),
		PAIR( KEY_Q ),
		PAIR( KEY_R ),
		PAIR( KEY_S ),
		PAIR( KEY_T ),
		PAIR( KEY_U ),
		PAIR( KEY_V ),
		PAIR( KEY_W ),
		PAIR( KEY_X ),
		PAIR( KEY_Y ),
		PAIR( KEY_Z ),

		PAIR( NUM_0 ),
		PAIR( NUM_1 ),
		PAIR( NUM_2 ),
		PAIR( NUM_3 ),
		PAIR( NUM_4 ),
		PAIR( NUM_5 ),
		PAIR( NUM_6 ),
		PAIR( NUM_7 ),
		PAIR( NUM_8 ),
		PAIR( NUM_9 ),

		PAIR( F1 ),
		PAIR( F2 ),
		PAIR( F3 ),
		PAIR( F4 ),
		PAIR( F5 ),
		PAIR( F6 ),
		PAIR( F7 ),
		PAIR( F8 ),
		PAIR( F9 ),
		PAIR( F10 ),
		PAIR( F11 ),
		PAIR( F12 ),

		PAIR( LEFT ),
		PAIR( RIGHT ),
		PAIR( UP ),
		PAIR( DOWN ),

		PAIR( LALT ),
		PAIR( RALT ),
		PAIR( LCTRL ),
		PAIR( RCTRL ),
		PAIR( LSHIFT ),
		PAIR( RSHIFT ),
		PAIR( CAPS ),
		PAIR( TAB ),
		PAIR( BACKSPACE ),
		PAIR( ENTER ),

		PAIR( INSERT ),
		PAIR( DELETE ),
		PAIR( HOME ),
		PAIR( END ),
		PAIR( PGUP ),
		PAIR( PGDOWN ),

		PAIR( PLUS ),
		PAIR( MINUS ),
	};

	auto it = values.find( inputCode );
	if ( it != values.end() )
	{
		return it->second;
	}

	return empty;
}

// clang-format on