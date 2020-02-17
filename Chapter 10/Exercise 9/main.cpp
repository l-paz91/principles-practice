// -----------------------------------------------------------------------------
//
// C10 - Exercise 9
/*
	Write a program that takes two files containing sorted whitespace separated words
	and merges them, preserving order.
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

void mergeFiles(string& filename1, string& filename2, vector<string>& v)
{
	ifstream file1{ filename1 };
	ifstream file2{ filename2 };
	ofstream file3{ "mergedFile.txt", ios_base::app };

	string temp;
	while (file1 >> temp)
		v.push_back(temp);
	while (file2 >> temp)
		v.push_back(temp);

	sort(v);

	for (string s : v)
		file3 << s << " ";
}

// -----------------------------------------------------------------------------

int main()
{
	vector<string> v_words;
	string filename1, filename2;

	getFilenames(filename1, filename2);
	mergeFiles(filename1, filename2, v_words);

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
