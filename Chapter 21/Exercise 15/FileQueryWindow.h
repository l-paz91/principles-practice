// -----------------------------------------------------------------------------
#ifndef FILEQUERYWINDOW_H
#define FILEQUERYWINDOW_H
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"
#include "FileCleanup.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	struct FileQueryWindow : public Window
	{
	public:
		FileQueryWindow(Point xy, int w, int h, const char* title);

	private:
		// actions
		void quitPressed();
		void openFilePressed();
		void findWordPressed();
		void listWordsStartingPressed();
		void listWordsOfSizePressed();

		// objects
		Button mQuitBtn, mOpenFileBtn;
		Button mFindWordBtn;
		Button mListWordsStartingBtn;
		Button mListWordsOfSizeBtn;

		In_box mFileNameInput;
		In_box mFindWordInput;
		In_box mListWordsStartingInput;
		In_box mListWordsOfSizeInput;

		MultilineScroll_Outbox mFileOutput;
		Out_box mMostFrequentOutput;
		Out_box mLongestOutput;
		Out_box mShortestOutput;
		Out_box mOccurrencesOutput;

		FileQuery mFileQuery;
	};

} // !namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !FILEQUERYWINDOW_H

