// -----------------------------------------------------------------------------
//
// C10 - Exercise 8
/*
	Write a program that accepts two file names and produces a new file that is 
	the contents of the first file followed by the contents of the second; 
	that is, the program concatenates the two files.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void checkFileFormat(string& filename)
{
	bool result = false;
	while (!result)
	{
		if ( filename.size() < 4 ||
			 filename.substr(filename.size() - 4, filename.size() - 1) != ".txt")
		{
			cout << "\nIncorrect file format. Try again:>> ";
			cin >> filename;
		}
		else
			result = true;
	}
}

// -----------------------------------------------------------------------------

void getFilenames(string& filename1, string& filename2)
{
	cout << "please enter the first filename in the format filename.txt:\n>>";
	cin >> filename1;
	checkFileFormat(filename1);
	cout << "please enter the second filename in the format filename.txt:\n>>";
	cin >> filename2;
	checkFileFormat(filename2);
}

// -----------------------------------------------------------------------------

void concatenateFiles(string& filename1, string& filename2)
{
	ifstream file1{ filename1 };
	ifstream file2{ filename2 };
	ofstream file3{ "concatenatedFile.txt", ios_base::app };

	file3 << file1.rdbuf();
	file3 << "\n";
	file3 << file2.rdbuf();
}

// -----------------------------------------------------------------------------

int main()
{
	string filename1, filename2;

	getFilenames(filename1, filename2);
	concatenateFiles(filename1, filename2);

	cout << endl;
	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
