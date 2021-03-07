// -----------------------------------------------------------------------------

// ---- INCLUDES ---- //
#include "Cave.h"

#include <conio.h>

// ---- GLOBALS ---- //
CodeHelp::Vector2D gWumpusPos;
uint8 gNumRooms = 1;

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

	gNumRooms = 1;
	mPrevRoomKey = eDEFAULT;
	mPrevWumpusKey = eDEFAULT;
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

GameState Cave::movePlayer(vector<CodeHelp::Vector2D>& rooms, Multiline_Outbox& pGameText, In_box& pInput, 
	GameState& pGameState)
{
	char c1;
	uint32_t c2;

	// player has pressed continue
	string input = pInput.get_string();
	c1 = input[0];
	c2 = stoi(input.substr(1, input.size() - 1));

	stringstream ss;
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
						ss << "\nThere was a pit!";
						ss << " But you used a plank to create a walkway." << endl;
						--mPlayer.mPlanks;
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						break;
					}
					else
					{
						ss << "\nOh no, there was a pit!";
						ss << " You tripped and fell, whoops. Game over." << endl;
						pGameText.put(ss.str());
						return eGAMEOVER;
					}
					break;
				case eBAT:
				{
					ss << "\nThere was a bat!";
					CodeHelp::Vector2D newPos;
					getCenterOfRoom(newPos);

					// set new room to show player and store key
					mPrevRoomKey = mCave[newPos.row][newPos.col].key;
					mPlayer.mCurrentRoom = mCave[newPos.row][newPos.col].mRoomNum;
					mPlayer.mPosition.row = newPos.row;
					mPlayer.mPosition.col = newPos.col;
					mCave[newPos.row][newPos.col].key = ePLAYER;

					ss << " It picked you up and moved you to room " << mPlayer.mCurrentRoom << "." << endl;
					switch (mPrevRoomKey)
					{
					case eBAT:
						ss << "The room had a pit!";
						ss << " But, you saw it coming, grabbed onto the ledge and pulled yourself to safety. Epic." << endl;
						ss << "The bat has flown off...what an asshole." << endl;
						break;
					case eWUMPUS:
						ss << "It's the wumpus!";
						if (mPlayer.mArrows > 0)
						{
							ss << " You shot the wumpus from the air. You and the bat high-fived...somehow. The world has been saved." << endl;
							pGameText.put(ss.str());
							return eWIN;
						}
						else
						{
							ss << " You had no arrows left. Both you and the bat exploded mid-air from terror. How unfortunate." << endl;
							pGameText.put(ss.str());
							return eGAMEOVER;
						}
						break;
					}
					ss << "Press continue...";
					pGameText.put(ss.str());
					return eGETMOVE;
				}
				case eWUMPUS:
					ss << "\nIt's the Wumpus!";
					ss << "\nYou were unprepared and died. Your body then blew up. How unfortunate." << endl;
					pGameText.put(ss.str());
					return eGAMEOVER;
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
					ss << "\nYou found a";
					int rand2 = randint(1, 2);
					if (rand2 == 1)
					{
						ss << " plank!" << endl;
						++mPlayer.mPlanks;
					}
					else
					{
						ss << "n arrow!" << endl;
						++mPlayer.mArrows;
					}
				}
				ss << "\nPress continue...";
				pGameText.put(ss.str());
				return eGETMOVE;
			}
		}
		ss << "That wasn't a valid room number. Try again." << endl;
		pGameState = eGETMOVE;
		movePlayer(rooms, pGameText, pInput, pGameState);
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
						ss << "\nThe arrow hit a bat!";
						ss << " It was super effective.";
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						batLoot(ss);
						break;
					case eWUMPUS:
						ss << "\nThe arrow hit the Wumpus! Precision 100.";
						ss << " You have saved the princess and the world." << endl;
						mCave[rooms[i].row][rooms[i].col].key = eEMPTY;
						pGameText.put(ss.str());
						return eWIN;
					default:
						ss << "\nThe arrow did not hit anything. It then blew up. How unfortunate.";
						--mPlayer.mArrows;
						break;
					}

					ss << "\nThe arrow made quite a noise...lets hope nothing heard it.";
					if (!moveWumpus())
					{
						pGameText.put(ss.str());
						return eGAMEOVER;
					}
					ss << "\nPress continue...";
					pGameText.put(ss.str());
					return eGETMOVE;
				}
			}
			ss << "That's not a valid move. Try again." << endl;
			pGameState = eGETMOVE;
			movePlayer(rooms, pGameText, pInput, pGameState);
		}
		else
		{
			ss << "\nYou have no arrows left." << endl;
			ss << "\nPress continue...";
			pGameText.put(ss.str());
			return eGETMOVE;
		}
	}
	default:
		ss << "That's not a valid move. Try again." << endl;
		pGameState = eGETMOVE;
		movePlayer(rooms, pGameText, pInput, pGameState);
		break;
	}
	
	ss << "\nPress continue...";
	pGameText.put(ss.str());
	return eGETMOVE;
}

// -----------------------------------------------------------------------------

void Cave::getNearbyRooms(vector<CodeHelp::Vector2D>& pRooms, Multiline_Outbox& pGameText)
{
	uint8 row = mPlayer.mPosition.row;
	uint8 col = mPlayer.mPosition.col;

	CodeHelp::Vector2D temp;

	stringstream ss;

	ss << "Planks: " << mPlayer.mPlanks << "  |  Arrows: " << mPlayer.mArrows << endl;
	ss << "\nYou are in room " << (int)mCave[row][col].mRoomNum;
	ss << ". There are tunnels to the following rooms: ";
	if (mCave[row - 1][col].key == eTUNNEL)
	{
		ss << "\n - " << (int)mCave[row - 4][col].mRoomNum;
		switch (mCave[row - 4][col].guess)
		{
		case eBAT:
			ss << "  (maybe a bat?)";
			break;
		case ePIT:
			ss << "  (maybe a pit?)";
			break;
		}
		temp.row = row - 4;
		temp.col = col;
		temp.mDir = eUP;
		pRooms.push_back(temp);
	}
	if (mCave[row][col + 1].key == eTUNNEL)
	{
		ss << "\n - " << (int)mCave[row][col + 4].mRoomNum;
		switch (mCave[row][col + 4].guess)
		{
		case eBAT:
			ss << "  (maybe a bat?)";
			break;
		case ePIT:
			ss << "  (maybe a pit?)";
			break;
		}
		temp.row = row;
		temp.col = col + 4;
		temp.mDir = eRIGHT;
		pRooms.push_back(temp);
	}
	if (mCave[row + 1][col].key == eTUNNEL)
	{
		ss << "\n - " << (int)mCave[row + 4][col].mRoomNum;
		switch (mCave[row + 4][col].guess)
		{
		case eBAT:
			ss << "  (maybe a bat?)";
			break;
		case ePIT:
			ss << "  (maybe a pit?)";
			break;
		}
		temp.row = row + 4;
		temp.col = col;
		temp.mDir = eDOWN;
		pRooms.push_back(temp);
	}
	if (mCave[row][col - 1].key == eTUNNEL)
	{
		ss << "\n - " << (int)mCave[row][col - 4].mRoomNum;
		switch (mCave[row][col - 4].guess)
		{
		case eBAT:
			ss << "  (maybe a bat?)";
			break;
		case ePIT:
			ss << "  (maybe a pit?)";
			break;
		}
		temp.row = row;
		temp.col = col - 4;
		temp.mDir = eLEFT;
		pRooms.push_back(temp);
	}

	for (uint32_t i = 0; i < pRooms.size(); ++i)
	{

		switch (mCave[pRooms[i].row][pRooms[i].col].key)
		{
		case eBAT:
			ss << "\nI hear a bat." << endl;
			break;
		case ePIT:
			ss << "\nI feel a breeze." << endl;
			break;
		case eWUMPUS:
			ss << "\nI smell the wumpus." << endl;
			break;
		}
	}

	ss << "\nMove or shoot?" << endl;
	pGameText.put(ss.str());
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

void Cave::setGuess(int pRoomNum, CaveKey pGuess)
{
	for (int row = 0; row < mHeight; ++row)
	{
		for (int col = 0; col < mWidth; ++col)
		{
			if (mCave[row][col].mRoomNum == pRoomNum)
				mCave[row][col].guess = pGuess;
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
		cout << "\nThe Wumpus found you!";
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

void Cave::batLoot(stringstream& ss)
{
	int weight = rand() % 10;

	switch (weight)
	{
	case 8: case 4: case 5: case 7:
		ss << " The bat dropped an arrow!" << endl;
		break;
	case 1: case 3: case 6:
		ss << " The bat dropped a plank!" << endl;
		--mPlayer.mArrows;
		++mPlayer.mPlanks;
		break;
	case 9: case 0: case 2: default:
		ss << " The bat did not drop anything." << endl;
		--mPlayer.mArrows;
		break;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
