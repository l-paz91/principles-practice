// -----------------------------------------------------------------------------
#ifndef CAVE_H_
#define CAVE_H_

// ---- INCLUDES ---- //
#include "GUI.h"
#include "Player.h"

// -----------------------------------------------------------------------------

typedef uint8_t uint8;

// ---- GLOBALS ---- //
const uint8 gWidth = 30;
const uint8 gHeight = 30;
extern uint8 gNumRooms;

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

enum GameState
{
	eGETMOVE,
	eMOVE,
	eWIN,
	eGAMEOVER,
	eTITLE
};

// -----------------------------------------------------------------------------

struct Square
{
	Square() {}
	Square(CaveKey ck, uint8 rn, uint8 pX, uint8 pY)
		: key(ck)
		, mRoomNum(rn)
		, guess(eEMPTY)
		, mX(pX)
		, mY(pY)
	{}

	CaveKey key;
	CaveKey guess;
	uint8 mRoomNum, mX, mY;
};

// -----------------------------------------------------------------------------

using namespace Graph_lib;

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
	void emptyCave();
	void initCave();
	bool createRoom(int row, int col, uint8 localRoomNum);

	GameState movePlayer(vector<CodeHelp::Vector2D>& rooms, Multiline_Outbox& pGameText, In_box& pInput, 
		GameState& pGameState);
	void getNearbyRooms(vector<CodeHelp::Vector2D>& pRooms, Multiline_Outbox& pGameText);
	void getCenterOfRoom(CodeHelp::Vector2D& OutPosition);
	void setKeyGivenRoomNum(uint8 pRoomNum, CaveKey pCK);
	void setGuess(int roomNum, CaveKey pGuess);
	bool moveWumpus();

	CaveKey determineHazard(int pRoomNum, int row, int col);
	CaveKey wallOrTunnel();
	void batLoot(stringstream& ss);

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
