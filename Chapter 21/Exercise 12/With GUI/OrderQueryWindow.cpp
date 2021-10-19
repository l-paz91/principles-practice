// -----------------------------------------------------------------------------

//----INCLUDES----//
#define _CRT_SECURE_NO_WARNINGS
#include "OrderQueryWindow.h"

// -----------------------------------------------------------------------------

Graph_lib::OrderQueryWindow::OrderQueryWindow(Point xy, int w, int h, const char* title)
	: Window(xy, w, h, title)
	, mOrdersOutput(Point(20, 50), 350, 300, "")
	, mFileNameInput(Point(50, 10), 200, 20, "File: ")
	, mPurchaseTotalOutput(Point(450, 100), 120, 30, "Purchase\nTotal: ")
	, mSearchNameInput(Point(450, 150), 120, 30, "Search by\n name: ")
	, mOpenFileBtn(Point(270, 10), 70, 20, "Open",
		[](Address, Address addr) { reference_to<OrderQueryWindow>(addr).openFilePressed(); })
	, mQuitBtn(Point(double(x_max()) - 70, 10), 70, 20, "Quit",
		[](Address, Address addr) { reference_to<OrderQueryWindow>(addr).quitPressed(); })
	, mSearchBtn(Point(450, 200), 70, 20, "Search",
		[](Address, Address addr) { reference_to<OrderQueryWindow>(addr).searchPressed(); })

{
	attach(mOrdersOutput);
	attach(mFileNameInput);
	attach(mPurchaseTotalOutput);
	attach(mSearchNameInput);
	attach(mOpenFileBtn);
	attach(mQuitBtn);
	attach(mSearchBtn);
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderQueryWindow::quitPressed()
{
	hide();
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderQueryWindow::openFilePressed()
{
	if (!mOrders.empty())
	{
		mOrders.clear();
	}

	string filename = mFileNameInput.get_string();
	OrderHelpers::getOrdersFromFile(mOrders, filename);

	stringstream ss;
	for (Order o : mOrders)
		ss << o << endl;

	mOrdersOutput.put(ss.str());

	double orderValue = OrderHelpers::getValueOfOrders(mOrders);
	string value = "£" + to_string(orderValue);
	mPurchaseTotalOutput.put(value);

	mSearchNameInput.put("");
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderQueryWindow::searchPressed()
{
	stringstream ss;
	string searchName = mSearchNameInput.get_string();

	for (const Order o : mOrders)
	{
		if (OrderHelpers::searchByName(searchName, o))
		{
			ss << o;
		}
	}

	// if there are characters waiting
	if (ss.rdbuf()->in_avail())
	{
		mOrdersOutput.put(ss.str());
	}
	else
	{
		const string s = "Not found. Press open to re-open the file.";	// not very efficient but I don't care
		mOrdersOutput.put(s);
	}

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
