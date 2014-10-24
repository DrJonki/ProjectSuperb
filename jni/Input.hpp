#pragma once

#include <Vector2.hpp>


namespace eng
{
	namespace KeyBoard
	{

		enum Key
		{
			Invalid			= -1,

			Back			= 0x08,
			Tab				= 0x09,
			Clear			= 0x0C,
			Return			= 0x0D,
			Shift			= 0x10,
			Control			= 0x11,
			Alt				= 0x12,
			Pause			= 0x13,
			CapsLock		= 0x14,
			Escape			= 0x1B,
			Space			= 0x20,
			PG_Up			= 0x21,
			PG_Down			= 0x22,
			End				= 0x23,
			Home			= 0x24,
			Left			= 0x25,
			Up				= 0x26,
			Right			= 0x27,
			Down			= 0x28,
			Select			= 0x29,
			Print			= 0x2A,
			PrintScreen		= 0x2C,
			Insert			= 0x2D,
			Delete			= 0x2E,
			Help			= 0x2F,
			Num0			= '0',
			Num1			= '1',
			Num2			= '2',
			Num3			= '3',
			Num4			= '4',
			Num5			= '5',
			Num6			= '6',
			Num7			= '7',
			Num8			= '8',
			Num9			= '9',
			A				= 'A',
			B				= 'B',
			C				= 'C',
			D				= 'D',
			E				= 'E',
			F				= 'F',
			G				= 'G',
			H				= 'H',
			I				= 'I',
			J				= 'J',
			K				= 'K',
			L				= 'L',
			M				= 'M',
			N				= 'N',
			O				= 'O',
			P				= 'P',
			Q				= 'Q',
			R				= 'R',
			S				= 'S',
			T				= 'T',
			U				= 'U',
			V				= 'V',
			W				= 'W',
			X				= 'X',
			Y				= 'Y',
			Z				= 'Z',
			Numpad0			= 0x60,
			Numpad1			= 0x61,
			Numpad2			= 0x62,
			Numpad3			= 0x63,
			Numpad4			= 0x64,
			Numpad5			= 0x65,
			Numpad6			= 0x66,
			Numpad7			= 0x67,
			Numpad8			= 0x68,
			Numpad9			= 0x69,
			Multiply		= 0x6A,
			Add				= 0x6B,
			Separator		= 0x6C,
			Subtract		= 0x6D,
			Decimal			= 0x6E,
			Divide			= 0x6F,
			F1				= 0x70,
			F2				= 0x71,
			F3				= 0x72,
			F4				= 0x73,
			F5				= 0x74,
			F6				= 0x75,
			F7				= 0x76,
			F8				= 0x77,
			F9				= 0x78,
			F10				= 0x79,
			F11				= 0x7A,
			F12				= 0x7B,
			F13				= 0x7C,
			F14				= 0x7D,
			F15				= 0x7E,
			F16				= 0x7F,
			F17				= 0x80,
			F18				= 0x81,

			Last
		};
	}

	namespace Mouse
	{
		enum Key
		{
			Left = 0x01,
			Right = 0x02,
			Middle = 0x04,
			Extra1 = 0x05,
			Extra2 = 0x06
		};
	}


	bool keyPressed(const KeyBoard::Key key);

	bool keyPressed(const Mouse::Key key);

	gpm::Vector2F getLastMouseMove();
}