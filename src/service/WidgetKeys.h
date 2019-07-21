#ifndef WIDGET_KEYS_H
#define WIDGET_KEYS_H

#include <photon/PkKeyDef.h>

namespace PhWidgets
{

	struct Hotkeys
	{
		enum eHotkeys
		{
			Left = Pk_Left,
			BackSpace = Pk_BackSpace, //!< BACKSPACE key
			Tab = Pk_Tab, //!< TAB key
			Return = Pk_Return,//!< ENTER key
			Escape = Pk_Escape,//!< ESC key
			Home = Pk_Home,//!< HOME key
			Up = Pk_Up,//!< UP key
			Right = Pk_Right,//!< RIGHT ARROW key
			Down = Pk_Down,//!< DOWN ARROW key
			Pg_Up = Pk_Pg_Up,//!< PAGE UP key
			Pg_Down = Pk_Pg_Down,//!< PAGE DOWN key
			End = Pk_End,//!< END key
			Insert = Pk_Insert,//!< INS key
			Delete = Pk_Delete,//!< DEL key
			Menu = Pk_Menu,//!< ALT key
			F1 = Pk_F1,//!< F1 key
			F2 = Pk_F2,//!< F2 key
			F3 = Pk_F3,//!< F3 key
			F4 = Pk_F4,//!< F4 key
			F5 = Pk_F5,//!< F5 key
			F6 = Pk_F6,//!< F6 key
			F7 = Pk_F7,//!< F7 key
			F8 = Pk_F8,//!< F8 key
			F9 = Pk_F9,//!< F9 key
			F10 = Pk_F10,//!< F10 key
			F11 = Pk_F11,//!< F11 key
			F12 = Pk_F12,//!< F12 key
			F13 = Pk_F13,//!< F13 key
			F14 = Pk_F14,//!< F14 key
			F15 = Pk_F15,//!< F15 key
			F16 = Pk_F16,//!< F16 key
			F17 = Pk_F17,//!< F17 key
			F18 = Pk_F18,//!< F18 key
			F19 = Pk_F19,//!< F19 key
			F20 = Pk_F20,//!< F20 key
			F21 = Pk_F21,//!< F21 key
			F22 = Pk_F22,//!< F22 key
			F23 = Pk_F23,//!< F23 key
			F24 = Pk_F24,//!< F24 key
			F25 = Pk_F25,//!< F25 key
			F26 = Pk_F26,//!< F26 key
			F27 = Pk_F27,//!< F27 key
			F28 = Pk_F28,//!< F28 key
			F29 = Pk_F29,//!< F29 key
			F30 = Pk_F30,//!< F30 key
			F31 = Pk_F31,//!< F31 key
			F32 = Pk_F32,//!< F32 key
			F33 = Pk_F33,//!< F33 key
			F34 = Pk_F34,//!< F34 key
			F35 = Pk_F35//!< F35 key
		};


	};

	struct KeyModes
	{
		enum eKeyModes
		{
			Shift = Pk_KM_Shift,
			Ctrl = Pk_KM_Ctrl,
			Alt = Pk_KM_Alt,
			none = 0
		};
	};

} // namespace PhWidgets

#endif // WIDGET_HOTKEYS_H