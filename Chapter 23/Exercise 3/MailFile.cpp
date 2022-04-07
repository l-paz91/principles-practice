// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MailFile.h"

#include <regex>

// -----------------------------------------------------------------------------

MailFile::MailFile(const string& pFile)
{
	// open file named pFile
	// read the lines from pFile into mLines
	// find the messages in the lines and compose them in mMessages
	// for simplicity assume every message is ended by a ---- line

	ifstream in{ pFile };
	if (!in)
	{
		cerr << "no file: " << pFile << endl;
		exit(1);
	}

	for (string s; getline(in, s);)
	{
		mLines.push_back(s);
	}

	auto first = mLines.begin();
	for (auto p = mLines.begin(); p != mLines.end(); ++p)
	{
		if (*p == "----")
		{
			// end of message
			mMessages.push_back(Message(first, p));
			first = p + 1;		// ---- not part of message
		}
	}
}

// -----------------------------------------------------------------------------

int isPrefix(const string& pString, const string& pLine)
{
	// is pLine the first part of pString?
	int n = pLine.size();
	if (string(pString, 0, n)==pLine)
	{
		return n;
	}
	
	return 0;
}

// -----------------------------------------------------------------------------

bool findFromAddr(const Message& pMsg, string& pString)
{
	for (const string& msg : pMsg)
	{
		if (int n = isPrefix(msg, "From: "))
		{
			pString = string(msg, n);
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

bool FindFromAddrUsingRegex(const Message& pMsg, string& pString)
{
	// subject pattern
	// [fF]				(allow upper/lowercase f)
	// rom:				(literal match to these lowercase characters)
	regex subjectPattern{ R"([fF]rom:)" };
	const int length = 6;

	for (const string& msg : pMsg)
	{
		smatch matches;
		if (regex_search(msg, matches, subjectPattern))
		{
			pString = string(msg, length);
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

std::string findSubject(const Message& mMsg)
{
	for (const auto& msg : mMsg)
	{
		if (int n = isPrefix(msg, "Subject: "))
		{
			return string(msg, n);
		}
	}

	return "";
}

// -----------------------------------------------------------------------------

std::string findSubjectUsingRegex(const Message& mMsg)
{
	// subject pattern
	// [sS]				(allow upper/lowercase s)
	// ubject:			(literal match to these lowercase characters)
	regex subjectPattern{ R"([sS]ubject:)" };
	const int length = 9;

	for (const auto& msg : mMsg)
	{
		smatch matches;
		if (regex_search(msg, matches, subjectPattern))
		{
			return string(msg, length);
		}
	}

	return "";
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
