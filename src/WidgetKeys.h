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
			BackSpace = Pk_BackSpace,
			Tab = Pk_Tab,
			Return = Pk_Return,
			Escape = Pk_Escape,
			Home = Pk_Home,
			Up = Pk_Up,
			Right = Pk_Right,
			Down = Pk_Down,
			Pg_Up = Pk_Pg_Up,
			Pg_Down = Pk_Pg_Down,
			End = Pk_End,
			Insert = Pk_Insert,
			Delete = Pk_Delete,
			Menu = Pk_Menu,
			F1 = Pk_F1,
			F2 = Pk_F2,
			F3 = Pk_F3,
			F4 = Pk_F4,
			F5 = Pk_F5,
			F6 = Pk_F6,
			F7 = Pk_F7,
			F8 = Pk_F8,
			F9 = Pk_F9,
			F10 = Pk_F10,
			F11 = Pk_F11,
			F12 = Pk_F12,
			F13 = Pk_F13,
			F14 = Pk_F14,
			F15 = Pk_F15,
			F16 = Pk_F16,
			F17 = Pk_F17,
			F18 = Pk_F18,
			F19 = Pk_F19,
			F20 = Pk_F20,
			F21 = Pk_F21,
			F22 = Pk_F22,
			F23 = Pk_F23,
			F24 = Pk_F24,
			F25 = Pk_F25,
			F26 = Pk_F26,
			F27 = Pk_F27,
			F28 = Pk_F28,
			F29 = Pk_F29,
			F30 = Pk_F30,
			F31 = Pk_F31,
			F32 = Pk_F32,
			F33 = Pk_F33,
			F34 = Pk_F34,
			F35 = Pk_F35
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

}

#endif // WIDGET_HOTKEYS_H