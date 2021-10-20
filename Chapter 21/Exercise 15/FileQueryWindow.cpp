// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "FileQueryWindow.h"

// -----------------------------------------------------------------------------

Graph_lib::FileQueryWindow::FileQueryWindow(Point xy, int w, int h, const char* title)
	: Window(xy, w, h, title)
	, mQuitBtn(Point(double(x_max()) - 70, 10), 70, 20, "Quit",
		[](Address, Address addr) { reference_to<FileQueryWindow>(addr).quitPressed(); })
	, mOpenFileBtn(Point(270, 10), 110, 20, "Open + Clean",
		[](Address, Address addr) { reference_to<FileQueryWindow>(addr).openFilePressed(); })
	, mFindWordBtn(Point(430, 140), 70, 20, "Find",
		[](Address, Address addr) { reference_to<FileQueryWindow>(addr).findWordPressed(); })
	, mListWordsStartingBtn(Point(430, 170), 70, 20, "List",
		[](Address, Address addr) { reference_to<FileQueryWindow>(addr).listWordsStartingPressed(); })
	, mListWordsOfSizeBtn(Point(430, 210), 70, 20, "List",
		[](Address, Address addr) { reference_to<FileQueryWindow>(addr).listWordsOfSizePressed(); })
	//
	, mFileNameInput(Point(50, 10), 200, 20, "File: ")
	, mFindWordInput(Point(350, 140), 70, 20, "Find Occurrences: ")
	, mListWordsStartingInput(Point(350, 170), 70, 20, "List words\nstarting with: ")
	, mListWordsOfSizeInput(Point(350, 210), 70, 20, "List words of size: ")
	//
	, mFileOutput(Point(20, 50), 200, 300, "")
	, mMostFrequentOutput(Point(350, 50), 200, 20, "Most frequent:")
	, mLongestOutput(Point(350, 80), 200, 20, "Longest word:")
	, mShortestOutput(Point(350, 110), 200, 20, "Shortest word:")
	, mOccurrencesOutput(Point(510, 140), 70, 20, "")
{
	attach(mQuitBtn);
	attach(mOpenFileBtn);
	attach(mFindWordBtn);
	attach(mListWordsStartingBtn);
	attach(mListWordsOfSizeBtn);

	attach(mFileNameInput);
	attach(mFindWordInput);
	attach(mListWordsStartingInput);
	attach(mListWordsOfSizeInput);

	attach(mFileOutput);
	attach(mMostFrequentOutput);
	attach(mLongestOutput);
	attach(mShortestOutput);
	attach(mOccurrencesOutput);
}

// -----------------------------------------------------------------------------

void Graph_lib::FileQueryWindow::quitPressed()
{
	hide();
}

// -----------------------------------------------------------------------------

void Graph_lib::FileQueryWindow::openFilePressed()
{
	string filename = mFileNameInput.get_string();
	mFileQuery.cleanupFile(filename);

	mFileOutput.put(*mFileQuery.mFile);

	mOccurrencesOutput.put("");
	mListWordsStartingInput.put("");
	mListWordsOfSizeInput.put("");

	mMostFrequentOutput.put(mFileQuery.findMostOccurring());
	mLongestOutput.put(mFileQuery.findLongestWord());
	mShortestOutput.put(mFileQuery.findShortestWord());
}

// -----------------------------------------------------------------------------

void Graph_lib::FileQueryWindow::findWordPressed()
{
	mOccurrencesOutput.put(mFileQuery.findNumOfOccurrences(mFindWordInput.get_string()));
}

// -----------------------------------------------------------------------------

void Graph_lib::FileQueryWindow::listWordsStartingPressed()
{
	stringstream ss = mFileQuery.listAllWordsStartingWith(mListWordsStartingInput.get_char());
	mFileOutput.put(ss.str());
}

// -----------------------------------------------------------------------------

void Graph_lib::FileQueryWindow::listWordsOfSizePressed()
{
	stringstream ss = mFileQuery.listAllWordsOfSize(mListWordsOfSizeInput.get_int());
	mFileOutput.put(ss.str());
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
