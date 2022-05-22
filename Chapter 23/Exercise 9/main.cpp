// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 9

	Using eof(), it is possible to determine which line of a table is the last. 
	Use that to (try to) simplify the table-checking program from section 23.9. 
	Be sure to test your program with files that end with empty lines after the 
	table and with files that don't end with a newline at all.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <regex>

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void fct()
{
	//ifstream inputFile{ "table.txt" };	// standard table
	//ifstream inputFile{ "table2.txt" };	// has new line after end of table
	ifstream inputFile{ "table3.txt" };		// has new lines in table and after
	
	string line;
	int lineNum = 0;

	regex header{ R"(^[\w ]+(	[\w ]+)*$)" };
	regex row{ R"(^[\w ]+(		\d+)( \d+)( \d+)$)" };

	if (getline(inputFile, line))
	{
		smatch matches;
		if (!regex_match(line, matches, header))
		{
			error("No header.");
		}
	}

	// column totals
	int boys = 0;
	int girls = 0;

	while (getline(inputFile, line))
	{
		if(line.empty())
			continue;	// will skip to next line

		++lineNum;
		smatch matches;
		if (!regex_match(line, matches, row))
		{
			cerr << "Bad line: " << lineNum << endl;
		}

		if (inputFile.eof())
		{
			cout << " at eof()\n";
		}

		// check row
		int currBoy = from_string<int>(matches[1]);
		int currGirl = from_string<int>(matches[2]);
		int currTotal = from_string<int>(matches[3]);
		if (currBoy + currGirl != currTotal)
		{
			error("Bad row sum.\n");
		}

		if (matches[0] == "Aile klasser \t\t184 202 386")
		{
			if (currBoy != boys)
				error("Boys don't add up!\n");
			if (currGirl != girls)
				error("Girls don't add up!\n");

			if (!(inputFile >> ws).eof())
				error("Characters after total line");

			cout << "Expected totals: 184\t202\t386\n";
			cout << "Totals: " << boys << "\t" << girls << "\t" << boys + girls << endl;

			return;
		}

		// update totals
		boys += currBoy;
		girls += currGirl;
	}
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
