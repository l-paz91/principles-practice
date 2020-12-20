// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 12
/*
	Implement a version of Hunt the Wumpus. (See blog post for more detail about
	the exercise requirements)
	This is not a perfect implementation. There is a lot of repetition and bad
	names.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Cave.h"
#include "Game.h"

// -----------------------------------------------------------------------------

int main()
{
	// set seed for random
	srand(static_cast<unsigned int>(time(NULL)));

	Game::titlescreen();

	Cave cave;
	bool playGame = true;
	while (playGame)
	{
		system("CLS");
		cave.printCave();
		playGame = cave.movePlayer();
	}

	cout << "Game over." << endl;
	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------