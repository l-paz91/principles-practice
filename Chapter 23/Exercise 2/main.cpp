// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 2

	Add a multimap and have it hold subjects. Let the program take an input string 
	from the keyboard and print out every message with that string as its subject.

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

bool getSubjects(multimap<string, const Message*>& pSubjects)
{
	cout << "Subject line to search: ";
	string subject;
	getline(cin, subject);

	auto isPair = pSubjects.equal_range(subject);
	if (isPair.first == isPair.second)
	{
		cout << "No messages found." << endl;
	}
	else
	{
		for (auto p = isPair.first; p != isPair.second; ++p)
		{
			Message m = *p->second;
			m.printMsg();
		}
	}

	cout << "Search again? y/n\n>> ";
	char c;
	cin >> c;
	if (c == 'y')
	{
		cin.clear();
		cin.ignore(120, '\n');
		return true;
	}
	return false;
}

// -----------------------------------------------------------------------------

void fct()
{
	MailFile mailFile{ "emailMessages.txt" };
	//MailFile mailFile{ "emailMessages2.txt" };		// this is a file containing no ---- lines

	// first gather messages from each sender together in a multimap
	multimap<string, const Message*> sender;

	// gather subjects and messages together
	multimap<string, const Message*> subjects;

	for (const auto& msg : mailFile)
	{
		string s;
		if (findFromAddr(msg, s))
		{
			sender.insert(make_pair(s, &msg));
		}

		s = findSubject(msg);
		if (s != "")
		{
			subjects.insert(make_pair(s, &msg));
		}
	}

	// now iterate through the multimap and extract the subjects of John Doe's
	// messages
	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");		// i'm ashamed that auto pp made me laugh
	for (auto p = pp.first; p != pp.second; ++p)
	{
		cout << findSubject(*p->second) << endl;
	}

	while (getSubjects(subjects))
	{}
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	cout << "\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
