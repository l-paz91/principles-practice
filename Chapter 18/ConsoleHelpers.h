// -----------------------------------------------------------------------------
#ifndef CONSOLEHELPERS_H_
#define CONSOLEHELPERS_H_

// ---- INCLUDES ---- //
#include <Windows.h>
#include <stdint.h>

typedef uint8_t uint8;

// -----------------------------------------------------------------------------

namespace Console
{
	const uint8 grey = 136;	// grey with grey background
	const uint8 white = 15;
	const uint8 red = 4;
	const uint8 red2 = 12;	// perfectly named
	const uint8 green = 2;
	const uint8 green2 = 10;
	const uint8 yellow = 6;

	const HANDLE gConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

// -----------------------------------------------------------------------------

namespace CodeHelp
{
	struct Vector2D
	{
		Vector2D()
			: row(0), col(0)
		{}

		uint8 row;
		uint8 col;
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !CONSOLEHELPERS_H_