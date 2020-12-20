// -----------------------------------------------------------------------------
#ifndef GAME_H_
#define GAME_H_

//----INCLUDES----//
#include <stdint.h>
#include <string>

// -----------------------------------------------------------------------------

namespace Game
{
	void titlescreen();
	void instructions();
	void endScreen();
	void gameOver();

	void printString(std::string& pText, int pColour);
	void printChar(uint8_t pChar, int pColour);
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GAME_H_
