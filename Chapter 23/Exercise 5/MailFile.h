// -----------------------------------------------------------------------------
#ifndef MailFile_H
#define MailFile_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <io.h>
#include <fcntl.h>

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

typedef vector<wstring>::const_iterator LineIt;

// -----------------------------------------------------------------------------

class Message
{
	// a message points to the first and last lines of a message
public:
	Message(LineIt p1, LineIt p2)
		: mFirst(p1)
		, mLast(p2)
	{}

	void printMsg()
	{
		// set output mode to allow unicode text
		_setmode(_fileno(stdout), _O_WTEXT);
		for (LineIt line = begin(); line != end(); ++line)
		{
			wcout << *line << endl;
		}
		wcout << "\n";
		_setmode(_fileno(stdout), _O_TEXT);
		// return output mode to normal
	}

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
	vector<wstring> mLines;				// the lines in order

	wstring mName;
};

// -----------------------------------------------------------------------------

int isPrefix(const wstring& pString, const wstring& pLine);

// -----------------------------------------------------------------------------

// find the name of the sender in a message, return true if found
// if found, place the sender's name in pString
bool findFromAddr(const Message& pMsg, wstring& pString);

bool FindFromAddrUsingRegex(const Message& pMsg, wstring& pString);

// -----------------------------------------------------------------------------

// return the subject of the message, if any, otherwise ""
wstring findSubject(const Message& mMsg);

wstring findSubjectUsingRegex(const Message& mMsg);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MailFile_H
