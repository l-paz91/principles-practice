// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 12

	Provide a GUI interface for querying a file of Orders; e.g., "Find all orders 
	from Joe," "Find the total value of orders in file Hardware," and "List all 
	orders in file Clothing." Hint: First design a non-GUI interface; then, build 
	the GUI on top of that.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#include "std_lib_facilities.h"
#include "Order.h"

#include <numeric>
#include <map>
#include <unordered_map>
#include <set>

//--GLOBALS--//

// -----------------------------------------------------------------------------

void openOrderFile(vector<Order>& pOutVector, string& pOutFilename)
{
	if (!pOutVector.empty())
		pOutVector.clear();

	cout << "Please enter a filename to open: ";
	cin >> pOutFilename;

	OrderHelpers::getOrdersFromFile(pOutVector, pOutFilename);
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void searchName(const vector<Order>& pOrders)
{
	system("CLS");

	cout << "Search name: ";
	string searchName;
	cin.clear();
	cin.ignore(120, '\n');

	getline(cin, searchName);

	for (const Order o : pOrders)
	{
		if (OrderHelpers::searchByName(searchName, o))
		{
			cout << o;
		}
	}
}

// -----------------------------------------------------------------------------

void fct()
{
	string filename;
	vector<Order> orders;
	openOrderFile(orders, filename);

	bool quit = false;
	while (!quit)
	{
		cout << "//-------- " << filename << " --------//" << endl;
		cout << "Menu:\n"
			<< "\t1. List orders\n"
			<< "\t2. Display total purchase value\n"
			<< "\t3. Search orders by name\n"
			<< "\t4. Open new file\n"
			<< "\t5. Exit\n"
			<< ">> ";
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
		case 1:
			for (Order o : orders)
				cout << o << endl;
			break;
		case 2:
			OrderHelpers::printValueOfOrders(orders);
			break;
		case 3:
			searchName(orders);
			break;
		case 4:
			openOrderFile(orders, filename);
			break;
		case 5:
			quit = true;
			break;
		default:
			cout << "That's not a number between 1-5." << endl;
			break;
		}

		pressKeyToContinue();
		system("CLS");
	}
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	//keep_window_open();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
