// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 12
/*
	Define a File_handle class with a constructor that takes a string argument 
	(the file name), opens the file in the constructor, and closes it in the 
	destructor.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"
#include "MyVector.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

class FileHandle
{
public:
	// ---- constructors
	FileHandle(const string& pFileName)
		: mFile(pFileName)
	{
		cout << "//constructor" << endl;
		if (!mFile)
			cout << "Error opening: " << pFileName << endl;
	}

	~FileHandle()
	{
		cout << "//destructor" << endl;
		mFile.close();
	}

	// ---- operators


	// ---- methods
	void printFile()
	{
		cout << mFile.rdbuf() << endl;
	}

private:
	ifstream mFile;
	
};

void file()
{
	FileHandle file("Textfile.txt");
	file.printFile();
}

// -----------------------------------------------------------------------------

int main()
{
	file();

	keep_window_open();
	_CrtDumpMemoryLeaks();		// maps malloc and free, checks for memory leaks
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
