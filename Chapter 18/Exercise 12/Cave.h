// -----------------------------------------------------------------------------
#ifndef CAVE_H_
#define CAVE_H_

// ---- INCLUDES ---- //
#include "Player.h"
#include "std_lib_facilities.h"

#include <Windows.h> // for prettying the console window

// -----------------------------------------------------------------------------

typedef uint8_t uint8;

// ---- GLOBALS ---- //
const uint8 gWidth = 30;
const uint8 gHeight = 30;

// -----------------------------------------------------------------------------

enum CaveKey
{
	eEMPTY = 'e',
	eBAT = 'B',
	ePIT = 'P',
	eWUMPUS = 'W',
	eWALL = '-',
	eTUNNEL = 'T',
	eSTART = 'S',
	ePLAYER = '+',
	eERROR = '*',
	eDEFAULT = '.'
};

// -----------------------------------------------------------------------------

struct Square
{
	Square() {}
	Square(CaveKey ck, uint8 rn, uint8 pX, uint8 pY)
		: key(ck)
		, mRoomNum(rn)
		, mX(pX)
		, mY(pY)
	{}

	CaveKey key;
	uint8 mRoomNum, mX, mY;
};

// -----------------------------------------------------------------------------

struct Cave
{
	// --- constructors
	Cave()
		: mWidth(gWidth)
		, mHeight(gHeight)
	{
		initCave();
	}

	// --- methods
	void printCave();
	void emptyCave();
	void initCave();
	bool createRoom(int row, int col, uint8 localRoomNum);

	bool movePlayer();
	void getNearbyRooms(vector<CodeHelp::Vector2D>& pRooms);
	void getCenterOfRoom(CodeHelp::Vector2D& OutPosition);
	void setKeyGivenRoomNum(uint8 pRoomNum, CaveKey pCK);
	bool moveWumpus();

	CaveKey determineHazard(int roomNum, int row, int col);
	CaveKey wallOrTunnel();
	void batLoot();

	// --- variables
	Square mCave[gWidth][gHeight];
	Player mPlayer;
	CaveKey mPrevRoomKey, mPrevWumpusKey;
	const int mWidth, mHeight;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !CAVE_H_
