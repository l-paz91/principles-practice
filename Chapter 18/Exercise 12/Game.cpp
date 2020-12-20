// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Game.h"
#include "ConsoleHelpers.h"

#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>

// -----------------------------------------------------------------------------
	using namespace std;
void Game::titlescreen()
{

	// resize console window
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1000, 600, TRUE);

	// set output mode to print unicode text
	_setmode(_fileno(stdout), _O_U8TEXT);
	wcout << L"----------------------------------------------------------------------------------------------------------------------------" << endl;
	wcout << L"██╗  ██╗██╗   ██╗███╗   ██╗████████╗    ████████╗██╗  ██╗███████╗    ██╗    ██╗██╗   ██╗███╗   ███╗██████╗ ██╗   ██╗███████╗" << endl;
	wcout << L"██║  ██║██║   ██║████╗  ██║╚══██╔══╝    ╚══██╔══╝██║  ██║██╔════╝    ██║    ██║██║   ██║████╗ ████║██╔══██╗██║   ██║██╔════╝" << endl;
	wcout << L"███████║██║   ██║██╔██╗ ██║   ██║          ██║   ███████║█████╗      ██║ █╗ ██║██║   ██║██╔████╔██║██████╔╝██║   ██║███████╗" << endl;
	wcout << L"██╔══██║██║   ██║██║╚██╗██║   ██║          ██║   ██╔══██║██╔══╝      ██║███╗██║██║   ██║██║╚██╔╝██║██╔═══╝ ██║   ██║╚════██║" << endl;
	wcout << L"██║  ██║╚██████╔╝██║ ╚████║   ██║          ██║   ██║  ██║███████╗    ╚███╔███╔╝╚██████╔╝██║ ╚═╝ ██║██║     ╚██████╔╝███████║" << endl;
	wcout << L"╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚══╝╚══╝  ╚═════╝ ╚═╝     ╚═╝╚═╝      ╚═════╝ ╚══════╝" << endl;
	wcout << L"----------------------------------------------------------------------------------------------------------------------------" << endl;
	_setmode(_fileno(stdout), _O_TEXT);	// set it back to normal so we can use std::cout again

	instructions();
	system("CLS");

	Sleep(100); cout << "."; Sleep(100); cout << "."; Sleep(100); cout << "." << endl;
	string s1 = "hey...take these. it's dangerous to enter the cave alone.\n";
	printString(s1, 6);

	Sleep(100); cout << "."; Sleep(100); cout << "."; Sleep(100); cout << "." << endl;
	cout << ">> received a bow, 5 arrows and 5 planks" << endl;
	cout << "\nPress any key to continue...";
	_getch();
}

// -----------------------------------------------------------------------------

void Game::instructions()
{
	cout << "- A rather smelly monster lives deep in the dark cave. It is threatening life as we know it." << endl;
	cout << "- The princess wants you to go and slay the Wumpus. You are the only one that can do it..." << endl;
	cout << "- The cave has two hazards; bottomless pits and giant bats." << endl;
	cout << "- If you enter a room with a pit and you have no planks, it's the end of the game." << endl;
	cout << "- If you enter a room with a bat, it will pick you up and drop you in another room." << endl;
	cout << "- If you enter a room with the wumpus, or he enters yours, he eats you." << endl;
	cout << "- You can hear bats and smell the wumpus. If you feel a breeze, that means there is a pit nearby." << endl;

	cout << "\n---CONTROLS--\n";
	cout << "- To move type 'm' followed by the room number. Example: m13" << endl;
	cout << "- To shoot type 's' followed by the room number. Example: s13" << endl;

	cout << "\nMaybe other things will happen in the cave...who knows? All those who have ventured in, have not returned..." << endl;
	cout << "It's time to go and Hunt the Wumpus. ";
	cout << "\nPress any key to continue...";
	_getch();
}

// -----------------------------------------------------------------------------

void Game::endScreen()
{
}

// -----------------------------------------------------------------------------

void Game::gameOver()
{
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

void Game::printString(string& pText, int pColour)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for (uint32_t i = 0; i < pText.size(); ++i)
	{
		SetConsoleTextAttribute(console, pColour);
		cout << pText[i];
		Sleep(100);
	}
	SetConsoleTextAttribute(console, 15);
}

void Game::printChar(uint8_t pChar, int pColour)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, pColour);
	cout << pChar;
	SetConsoleTextAttribute(console, 15);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
