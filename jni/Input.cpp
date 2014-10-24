#include "Input.hpp"
#include <Win32toAndroid.h>

#if defined(WINDOWS_FRAMEWORK)
	#include <Windows.h>

//#elif
		

#endif



namespace eng
{

	bool keyPressed(const KeyBoard::Key key)
	{
		#if defined(WINDOWS_FRAMEWORK)
			return (GetAsyncKeyState(key) & 0x8000) != 0;
		#else
			return false;
		#endif
	}


	bool keyPressed(const Mouse::Key key)
	{
		#if defined(WINDOWS_FRAMEWORK)
			return (GetAsyncKeyState(key) & 0x8000) != 0;
		#else
			return false;
		#endif
	}


	gpm::Vector2F getLastMouseMove()
	{
		#if defined(WINDOWS_FRAMEWORK)

			static POINT lastPos;
			static bool first = true;

			if (first)
			{
				GetCursorPos(&lastPos);
				first = false;
			}

			POINT currPos;
			GetCursorPos(&currPos);

			gpm::Vector2F difference(currPos.y - lastPos.y, currPos.x - lastPos.x);

			//lastPos = currPos;
			SetCursorPos(lastPos.x, lastPos.y);

			return difference;

		#else

			return gpm::Vector2F();

		#endif
	}

}