// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 1

	Get the email file example to run; test it using a large file of your own 
	creation. Be sure to include messages that are likely to trigger errors, 
	such as messages with two address lines, several messages with the same 
	address and/or same subject, and empty messages. Also test the program 
	with something that simply isn't a message according to that program's 
	specification, such as a large file contain no ---- lines.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MailFile.h"
#include "std_lib_facilities.h"

#include <iterator>
#include <map>
#include <regex>

// -----------------------------------------------------------------------------

void fct()
{
	//MailFile mailFile{ "emailMessages.txt" };
	MailFile mailFile{ "emailMessages2.txt" };		// this is a file containing no ---- lines

	// first gather messages from each sender together in a multimap
	multimap<string, const Message*> sender;

	for (const auto& msg : mailFile)
	{
		string s;
		if (findFromAddr(msg, s))
		{
			sender.insert(make_pair(s, &msg));
		}
	}

	// now iterate through the multimap and extract the subjects of John Doe's
	// messages
	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");		// i'm ashamed that auto pp made me laugh
	for (auto p = pp.first; p != pp.second; ++p)
	{
		cout << findSubject(*p->second) << endl;
	}
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
