// -----------------------------------------------------------------------------
#ifndef MailFile_H
#define MailFile_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

typedef vector<string>::const_iterator LineIt;

// -----------------------------------------------------------------------------

class Message
{
	// a message points to the first and last lines of a message
public:
	Message(LineIt p1, LineIt p2)
		: mFirst(p1)
		, mLast(p2)
	{}

	LineIt begin() const { return mFirst; }
	LineIt end() const { return mLast; }

private:
	LineIt mFirst;
	LineIt mLast;
};

// -----------------------------------------------------------------------------

using MsgIt = vector<Message>::const_iterator;

// -----------------------------------------------------------------------------

struct MailFile 
{
	// a MailFile holds all the lines from a file and simplifies access to
	// messages

	MailFile(const string& pFile);

	MsgIt begin() const { return mMessages.begin(); }
	MsgIt end() const { return mMessages.end(); }

	vector<Message> mMessages;			// the messages in order
	vector<string> mLines;				// the lines in order
	string mName;
};

// -----------------------------------------------------------------------------

int isPrefix(const string& pString, const string& pLine);

// -----------------------------------------------------------------------------

// find the name of the sender in a message, return true if found
// if found, place the sender's name in pString
bool findFromAddr(const Message& pMsg, string& pString);

// -----------------------------------------------------------------------------

// return the subject of the message, if any, otherwise ""
string findSubject(const Message& mMsg);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MailFile_H
