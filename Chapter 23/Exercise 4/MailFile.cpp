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
	// for simplicity assume the message file is ended by a ---- line

	wfstream in{ pFile };
	if (!in)
	{
		cerr << "no file: " << pFile << endl;
		exit(1);
	}

	for (wstring s; getline(in, s);)
	{
		mLines.push_back(s);
	}

	if (mLines.size() < 4)
	{
		wcout << "No messages. File formatted incorrectly." << endl;
		return;
	}

	auto first = mLines.begin();
	for (auto p = mLines.begin()+1; p != mLines.end(); ++p)
	{
		if (isPrefix(*p, L"From:") || isPrefix(*p, L"----"))
		{
			// end of message
			mMessages.push_back(Message(first, p-1));
			first = p;
		}
	}
}

// -----------------------------------------------------------------------------

int isPrefix(const wstring& pString, const wstring& pLine)
{
	// is pLine the first part of pString?
	int n = pLine.size();
	if (wstring(pString, 0, n)==pLine)
	{
		return n;
	}
	
	return 0;
}

// -----------------------------------------------------------------------------

bool findFromAddr(const Message& pMsg, wstring& pString)
{
	for (const wstring& msg : pMsg)
	{
		if (int n = isPrefix(msg, L"From: "))
		{
			pString = wstring(msg, n);
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

bool FindFromAddrUsingRegex(const Message& pMsg, wstring& pString)
{
	// subject pattern
	// [fF]				(allow upper/lowercase f)
	// rom:				(literal match to these lowercase characters)
	wregex subjectPattern{ L"([fF]rom:)" };
	const int length = 6;

	for (const wstring& msg : pMsg)
	{
		wsmatch matches;
		if (regex_search(msg, matches, subjectPattern))
		{
			pString = wstring(msg, length);
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

std::wstring findSubject(const Message& mMsg)
{
	for (const auto& msg : mMsg)
	{
		if (int n = isPrefix(msg, L"Subject: "))
		{
			return wstring(msg, n);
		}
	}

	return L"";
}

// -----------------------------------------------------------------------------

std::wstring findSubjectUsingRegex(const Message& mMsg)
{
	// subject pattern
	// [sS]				(allow upper/lowercase s)
	// ubject:			(literal match to these lowercase characters)
	wregex subjectPattern{ L"([sS]ubject:)" };
	const int length = 9;

	for (const auto& msg : mMsg)
	{
		wsmatch matches;
		if (regex_search(msg, matches, subjectPattern))
		{
			return wstring(msg, length);
		}
	}

	return L"";
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
