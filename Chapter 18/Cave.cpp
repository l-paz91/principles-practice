// -----------------------------------------------------------------------------

// ---- INCLUDES ---- //
#include "Cave.h"

#include <conio.h>

// ---- GLOBALS ---- //
CodeHelp::Vector2D gStartPos;
CodeHelp::Vector2D gWumpusPos;
uint8 gNumRooms = 1;

// -----------------------------------------------------------------------------

void Cave::printCave()
{
	using namespace Console;
	for (int row = 0; row < mHeight; ++row)
	{
		for (int col = 0; col < mWidth; ++col)
		{
			switch (mCave[row][col].key)
			{
			case eDEFAULT:
				SetConsoleTextAttribute(gConsole, red);
				cout << (char)mCave[row][col].key << " ";
				break;
			case eWALL: case eTUNNEL: case eEMPTY:
				SetConsoleTextAttribute(gConsole, grey);
				//cout << (char)mCave[row][col].key << " ";
				cout << "  ";
				break;
			default:
				SetConsoleTextAttribute(gConsole, white);
				cout << (char)mCave[row][col].key << " ";
				break;
			}
			SetConsoleTextAttribute(gConsole, white);	// set console back to normal
		}
		cout << endl;
	}
}

// -----------------------------------------------------------------------------

void Cave::emptyCave()
{
	for (int row = 0; row < mHeight; ++row)
	{
		for (int col = 0; col < mWidth; ++col)
		{
			mCave[row][col] = Square(eDEFAULT, 0, row, col);
		}
	}
}

// -----------------------------------------------------------------------------

void Cave::initCave()
{
	emptyCave();

	// choose random spot in cave to start drawing rooms from
	// also can't believe I genuinely need to use a do while
	int row, col;
	do {
		row = randint(0, mWidth - 3);
		col = randint(0, mHeight - 3);
	} while (!createRoom(row, col, gNumRooms));

	// we were unlucky
	if (gNumRooms < 10)
	{
		gNumRooms = 1;
		initCave();
		return;
	}

	// now add the wumpus somewhere
	uint8 randRoom = randint(2, gNumRooms);
	setKeyGivenRoomNum(randRoom, eWUMPUS);
}

// -----------------------------------------------------------------------------

bool Cave::createRoom(int row, int col, uint8 localRoomNum)
{
	// rooms are 3x3 in size

	// can go three across and 3 down? then draw square
	if (mCave[row][col + 2].key == eDEFAULT
		&& mCave[row + 2][col].key == eDEFAULT)
	{
		Square temp;

		// --------- row 1
		mCave[row][col] = Square(eWALL, localRoomNum, row, col);

		// if there is already a room above, connect them
		if ((row - 1 >= 0) && mCave[row - 1][col + 1].key == eTUNNEL)
		{
			mCave[row][col + 1] = Square(eTUNNEL, localRoomNum, row, col);
			mCave[row - 1][col + 1] = Square(eTUNNEL, 0, row, col);
		}
		else
		{
			// make it a wall by default
			mCave[row][col + 1] = Square(eWALL, localRoomNum, row, col);

			// can the space above be a room?
			if ((row - 4) >= 0 && mCave[row - 4][col].key == eDEFAULT)
			{
				temp = Square(wallOrTunnel(), localRoomNum, row, col);
				if (temp.key == eTUNNEL)
				{
					mCave[row][col + 1] = temp;
					mCave[row - 1][col + 1] = Square(eTUNNEL, 0, row, col);
					createRoom(row - 4, col, ++gNumRooms);
				}
			}
		}

		mCave[row][col + 2] = Square(eWALL, localRoomNum, row, col);

		// -------- row 2
		// if there is already a room to the left, connect them
		if ((col - 2 >= 0) && mCave[row + 1][col - 2].key == eTUNNEL)
		{
			mCave[row + 1][col] = Square(eTUNNEL, localRoomNum, row, col);
			mCave[row + 1][col - 1] = Square(eTUNNEL, 0, row, col);
		}
		else
		{
			// make it a wall by default
			mCave[row + 1][col] = Square(eWALL, localRoomNum, row, col);

			// can the space to the left be a room?
			if ((col - 4) >= 0 && mCave[row][col - 4].key == eDEFAULT)
			{
				temp = Square(wallOrTunnel(), localRoomNum, row, col);
				if (temp.key == eTUNNEL)
				{
					mCave[row + 1][col] = temp;
					mCave[row + 1][col - 1] = Square(eTUNNEL, 0, row, col);
					createRoom(row, col - 4, ++gNumRooms);
				}
			}
		}

		mCave[row + 1][col + 1] = Square(determineHazard(localRoomNum, row, col), localRoomNum, row, col); // center spot

		// if there is already a room to the right, connect them
		if ((col + 4 < mWidth) && mCave[row + 1][col + 4].key == eTUNNEL)
		{
			mCave[row + 1][col + 2] = Square(eTUNNEL, localRoomNum, row, col);
			mCave[row + 1][col + 3] = Square(eTUNNEL, 0, row, col);
		}
		else
		{
			// make it a wall by default
			mCave[row + 1][col + 2] = Square(eWALL, localRoomNum, row, col);

			// can the space to the right be a room?
			if ((col + 6) < mWidth && mCave[row][col + 4].key == eDEFAULT)
			{
				temp = Square(wallOrTunnel(), localRoomNum, row, col);
				if (temp.key == eTUNNEL)
				{
					mCave[row + 1][col + 2] = temp;
					mCave[row + 1][col + 3] = Square(eTUNNEL, 0, row, col);
					createRoom(row, col + 4, ++gNumRooms);
				}
			}
		}

		// -------- row 3
		mCave[row + 2][col] = Square(eWALL, localRoomNum, row, col);

		// if there is already a room below, connect them
		if ((row + 4 < mHeight) && mCave[row + 4][col + 1].key == eTUNNEL)
		{
			mCave[row + 2][col + 1] = Square(eTUNNEL, localRoomNum, row, col);
			mCave[row + 3][col + 1] = Square(eTUNNEL, 0, row, col);
		}
		else
		{
			// make it a wall by default
			mCave[row + 2][col + 1] = Square(eWALL, localRoomNum, row, col);

			// can the space below be a room?
			if ((row + 6) < mHeight && mCave[row + 4][col + 1].key == eDEFAULT)
			{
				temp = Square(wallOrTunnel(), localRoomNum, row, col);
				if (temp.key == eTUNNEL)
				{
					mCave[row + 2][col + 1] = temp;
					mCave[row + 3][col + 1] = Square(eTUNNEL, 0, row, col);
					createRoom(row + 4, col, ++gNumRooms);
				}
			}
		}

		mCave[row + 2][col + 2] = Square(eWALL, localRoomNum, row, col);
	}
	else
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

bool Cave::movePlayer()
{
	vector<CodeHelp::Vector2D> rooms;
	getNearbyRooms(rooms);

	cout << "\nMove or shoot?" << endl;
	char c1;
	uint32_t c2;
	cin >> c1 >> c2;

	switch (c1)
	{
	case 'm':
	{
		//do move stuff
		for (uint32_t i = 0; i < rooms.size(); ++i)
		{
			if (mCave[rooms[i].row][rooms[i].col].mRoomNum == c2)
			{
				// set room player is leaving back to what it used to be
				mCave[mPlayer.mPosition.row][mPlayer.mPosition.col].key = mPrevRoomKey;

				//are there any hazards?

				switch (mCave[rooms[i].row][rooms[i].col].key)
				{
				case ePIT:
					if (mPlayer.mPlanks > 0)
					{
						SetConsoleTextAttribute(Console::gConsole, Console::red2);
						cout << "\nThere was a pit!";
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						cout << " But you used a plank to create a walkway." << endl;
						--mPlayer.mPlanks;
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						cout << "\nPress any key to continue...";
						_getch();
						break;
					}
					else
					{
						SetConsoleTextAttribute(Console::gConsole, Console::red2);
						cout << "\nOh no, there was a pit!";
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						cout << " You tripped and fell, whoops." << endl;
						return false;
					}
					break;
				case eBAT:
				{
					SetConsoleTextAttribute(Console::gConsole, Console::red2);
					cout << "\nThere was a bat!";
					SetConsoleTextAttribute(Console::gConsole, Console::white);				
					CodeHelp::Vector2D newPos;
					getCenterOfRoom(newPos);

					// set new room to show player and store key
					mPrevRoomKey = mCave[newPos.row][newPos.col].key;
					mPlayer.mCurrentRoom = mCave[newPos.row][newPos.col].mRoomNum;
					mPlayer.mPosition.row = newPos.row;
					mPlayer.mPosition.col = newPos.col;
					mCave[newPos.row][newPos.col].key = ePLAYER;

					cout << " It picked you up and moved you to room " << mPlayer.mCurrentRoom << "." << endl;
					switch (mPrevRoomKey)
					{
					case eBAT:
						SetConsoleTextAttribute(Console::gConsole, Console::red2);
						cout << "The room had a pit!";
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						cout << " But, you saw it coming, grabbed onto the ledge and pulled yourself to safety. Epic." << endl;
						cout << "The bat has flown off...what an asshole." << endl;
						break;
					case eWUMPUS:
						SetConsoleTextAttribute(Console::gConsole, Console::red2);
						cout << "It's the wumpus!";
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						if (mPlayer.mArrows > 0)
						{
							cout << " You shot the wumpus from the air. You and the bat high-fived...somehow. The world has been saved." << endl;
							return false;
						}
						else
						{
							cout << " You had no arrows left. Both you and the bat exploded mid-air from terror. How unfortunate." << endl;
							return false;
						}
						break;
					}
					cout << "Press any key to continue...";
					_getch();
					return true;
				}
				case eWUMPUS:
					SetConsoleTextAttribute(Console::gConsole, Console::red2);
					cout << "\nIt's the Wumpus!";
					SetConsoleTextAttribute(Console::gConsole, Console::white);
					cout << "\nYou were unprepared and died. Your body then blew up. How unfortunate." << endl;
					return false;
				}

				// set new room to show player and store key
				mPrevRoomKey = mCave[rooms[i].row][rooms[i].col].key;
				mPlayer.mCurrentRoom = mCave[rooms[i].row][rooms[i].col].mRoomNum;
				mPlayer.mPosition.row = rooms[i].row;
				mPlayer.mPosition.col = rooms[i].col;
				mCave[rooms[i].row][rooms[i].col].key = ePLAYER;

				int rand = randint(0, 10);
				if (rand == 6)
				{
					SetConsoleTextAttribute(Console::gConsole, Console::green2);
					cout << "\nYou found a";
					int rand2 = randint(1, 2);
					if (rand2 == 1)
					{
						cout << " plank!" << endl;
						++mPlayer.mPlanks;
					}
					else
					{
						cout << "n arrow!" << endl;
						++mPlayer.mArrows;
					}
					SetConsoleTextAttribute(Console::gConsole, Console::white);
					cout << "\nPress any key to continue...";
					_getch();
				}
				return true;
			}
		}
		cout << "That wasn't a valid room number. Try again." << endl;
		movePlayer();
	}
	case 's':
	{
		if (mPlayer.mArrows > 0)
		{
			// do shooty stuff
			for (uint32_t i = 0; i < rooms.size(); ++i)
			{
				if (mCave[rooms[i].row][rooms[i].col].mRoomNum == c2)
				{
					switch (mCave[rooms[i].row][rooms[i].col].key)
					{
					case eBAT:
						cout << "\nThe arrow hit a bat!";
						SetConsoleTextAttribute(Console::gConsole, Console::green2);
						cout << " It was super effective.";
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						batLoot();
						break;
					case eWUMPUS:
						SetConsoleTextAttribute(Console::gConsole, Console::green2);
						cout << "\nThe arrow hit the Wumpus! Precision 100.";
						cout << " You have saved the princess and the world." << endl;
						SetConsoleTextAttribute(Console::gConsole, Console::white);
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						return false;
					default:
						cout << "\nThe arrow did not hit anything. It then blew up. How unfortunate.";
						--mPlayer.mArrows;
						break;
					}

					cout << "\nThe arrow made quite a noise...lets hope nothing heard it.";
					if (!moveWumpus())
						return false;
					cout << "\nPress any key to continue...";
					_getch();
					return true;
				}	
			}
			cout << "That's not a valid move. Try again." << endl;
			movePlayer();
		}
		else
		{
			cout << "\nYou have no arrows left." << endl;
			cout << "\nPress any key to continue...";
			_getch();
			return true;
		}
	}
	default:
		cout << "That's not a valid move. Try again." << endl;
		movePlayer();
		break;
	}

	return true;
}

// -----------------------------------------------------------------------------

void Cave::getNearbyRooms(vector<CodeHelp::Vector2D>& pRooms)
{
	uint8 row = mPlayer.mPosition.row;
	uint8 col = mPlayer.mPosition.col;

	CodeHelp::Vector2D temp;

	cout << "Planks: " << mPlayer.mPlanks << "  |  Arrows: " << mPlayer.mArrows << endl;
	cout << "\nYou are in room " << (int)mCave[row][col].mRoomNum;
	cout << ". There are tunnels to the following rooms: ";
	if (mCave[row - 1][col].key == eTUNNEL)
	{
		cout << "\n - " << (int)mCave[row - 4][col].mRoomNum;
		temp.row = row - 4;
		temp.col = col;
		pRooms.push_back(temp);
	}
	if (mCave[row][col + 1].key == eTUNNEL)
	{
		cout << "\n - " << (int)mCave[row][col + 4].mRoomNum;
		temp.row = row;
		temp.col = col + 4;
		pRooms.push_back(temp);
	}
	if (mCave[row + 1][col].key == eTUNNEL)
	{
		cout << "\n - " << (int)mCave[row + 4][col].mRoomNum;
		temp.row = row + 4;
		temp.col = col;
		pRooms.push_back(temp);
	}
	if (mCave[row][col - 1].key == eTUNNEL)
	{
		cout << "\n - " << (int)mCave[row][col - 4].mRoomNum;
		temp.row = row;
		temp.col = col - 4;
		pRooms.push_back(temp);
	}

	SetConsoleTextAttribute(Console::gConsole, Console::yellow);
	for (uint32_t i = 0; i < pRooms.size(); ++i)
	{

		switch (mCave[pRooms[i].row][pRooms[i].col].key)
		{
		case eBAT:		
			cout << "\nI hear a bat." << endl;
			break;
		case ePIT:
			cout << "\nI feel a breeze." << endl;
			break;
		case eWUMPUS:
			cout << "\nI smell the wumpus." << endl;
			break;
		}
	}
	SetConsoleTextAttribute(Console::gConsole, Console::white);
}

// -----------------------------------------------------------------------------

void Cave::getCenterOfRoom(CodeHelp::Vector2D& OutPosition)
{
	int randNum = randint(1, gNumRooms);
	if (randNum == mPlayer.mCurrentRoom)
	{
		randNum = randint(1, gNumRooms);
	}

	for (int row = 0; row < mHeight; ++row)
	{
		for (int col = 0; col < mWidth; ++col)
		{
			if (mCave[row][col].mRoomNum == randNum)
			{
				OutPosition.row = row + 1;
				OutPosition.col = col + 1;
				return;
			}			
		}
	}
}

// -----------------------------------------------------------------------------

void Cave::setKeyGivenRoomNum(uint8 pRoomNum, CaveKey pCK)
{
	for (int i = 0; i < mWidth; ++i)
	{
		for (int j = 0; j < mHeight; ++j)
		{
			if (mCave[i][j].mRoomNum == pRoomNum)
			{
				// should always hit top left of room
				mPrevWumpusKey = mCave[i + 1][j + 1].key;
				mCave[i + 1][j + 1].key = pCK;
				gWumpusPos.row = i + 1;
				gWumpusPos.col = j + 1;
				return;
			}
		}
	}
}

// -----------------------------------------------------------------------------

bool Cave::moveWumpus()
{
	uint8 row = gWumpusPos.row;
	uint8 col = gWumpusPos.col;
	mCave[row][col].key = mPrevWumpusKey;

	vector<CodeHelp::Vector2D> rooms;
	CodeHelp::Vector2D temp;

	if (mCave[row - 1][col].key == eTUNNEL)
	{
		temp.row = row - 4;
		temp.col = col;
		rooms.push_back(temp);
	}
	if (mCave[row][col + 1].key == eTUNNEL)
	{
		temp.row = row;
		temp.col = col + 4;
		rooms.push_back(temp);
	}
	if (mCave[row + 1][col].key == eTUNNEL)
	{
		temp.row = row + 4;
		temp.col = col;
		rooms.push_back(temp);
	}
	if (mCave[row][col - 1].key == eTUNNEL)
	{
		temp.row = row;
		temp.col = col - 4;
		rooms.push_back(temp);
	}

	//choose a random room to move to
	int randNum = randint(0, rooms.size() - 1);
	gWumpusPos.row = rooms[randNum].row;
	gWumpusPos.col = rooms[randNum].col;
	if (mCave[gWumpusPos.row][gWumpusPos.col].key == ePLAYER)
	{
		SetConsoleTextAttribute(Console::gConsole, Console::red2);
		cout << "\nThe Wumpus found you!";
		SetConsoleTextAttribute(Console::gConsole, Console::white);
		cout << "\nYou were unprepared and died. Your body then blew up. How unfortunate." << endl;
		return false;
	}
	mCave[gWumpusPos.row][gWumpusPos.col].key = eWUMPUS;
	return true;
}

// -----------------------------------------------------------------------------

CaveKey Cave::determineHazard(int roomNum, int row, int col)
{
	// hacky way of setting weight for hazards, does the job though
	int weight = rand() % 10;
	int randNum;

	switch (weight)
	{
	case 0: case 1: case 2: case 3:
		randNum = randint(2, 3);
		break;
	case 4: case 5: case 6: case 7: case 8: case 9:
		randNum = 1;
		break;
	default:
		randNum = 99;
		cout << "why are we here?" << endl;
		break;
	}

	if (roomNum == 1)
	{
		mPlayer.mPosition.row = row + 1;
		mPlayer.mPosition.col = col + 1;
		mPlayer.mCurrentRoom = 1;
		mPrevRoomKey = eSTART;
		return eSTART;
	}
	else
	{
		switch (randNum)
		{
		case 1:
			return eEMPTY;
		case 2:
			return eBAT;
		case 3:
			return ePIT;
		default:
			cout << "why are we here?" << endl;
			return eERROR;
		}
	}
}

// -----------------------------------------------------------------------------

CaveKey Cave::wallOrTunnel()
{
	int weight = rand() % 10;

	switch (weight)
	{
	case 8: case 4: case 5: case 7:
		return eWALL;
	case 1: case 3: case 6: case 9: case 0: case 2: 
		return eTUNNEL;
	default:
		cout << "why are we here?" << endl;
		return eERROR;
	}
}

// -----------------------------------------------------------------------------

void Cave::batLoot()
{
	int weight = rand() % 10;

	switch (weight)
	{
	case 8: case 4: case 5: case 7:
		cout << " The bat dropped an arrow!" << endl;
		break;
	case 1: case 3: case 6:
		cout << " The bat dropped a plank!" << endl;
		--mPlayer.mArrows;
		++mPlayer.mPlanks;
		break;
	case 9: case 0: case 2: default:
		cout << " The bat did not drop anything." << endl;
		--mPlayer.mArrows;
		break;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


