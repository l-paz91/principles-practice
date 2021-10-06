// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 9

	Define an Order class with (customer) name, address, date, and vector<Purchase>
	members. 
	
	Purchase is a class with a (product) name, unit_price, and count 
	members. 
	
	Define a mechanism for reading and writing Orders to and from a file. 
	
	Define a mechanism for printing Orders. 
	
	Create a file of at least ten Orders, read it into a vector<Order>, sort it by 
	name (customer), and write it back out to a file. 
	
	Create another file of at least ten Orders of which about a third are the same 
	as in the first file, read it into a list<Order>, sort it by address (of customer), 
	and write it back out to a file. Merge the two files into a third using std::merge().

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

// -----------------------------------------------------------------------------

void fct()
{
	Order order(
		"Bjarne Stroustrup", 
		"1 Pointer Lane, Pointer Town, Pointershire, LP2 CTS, C++", 
		std::time(nullptr),
		{ Purchase("Book", 45.95, 1), Purchase("Laptop", 950.50, 1) }
	);

	cout << order << endl;
	order.writeToFile();
	cout << "// -----------------------------------------------------------------------------" << endl;

	Order order2("Bjarne Stroustrup Order.txt");
	cout << order2 << endl;
	cout << "// -----------------------------------------------------------------------------" << endl;

	vector<Order> orders;
	OrderHelpers::getOrdersFromFile(orders, "Orders.txt");
	for (Order o : orders)
		cout << o << endl;
	cout << "// -----------------------------------------------------------------------------" << endl;

	sort(orders.begin(), orders.end(), OrderHelpers::sortByName());
	ofstream out("Multiple Orders.txt");
	for (Order o : orders)
		out << o;
	cout << "// -----------------------------------------------------------------------------" << endl;

	list<Order> listOrders;
	OrderHelpers::getOrdersFromFile(listOrders, "Orders2.txt");
	listOrders.sort(OrderHelpers::sortByAddress());

	listOrders.sort(OrderHelpers::sortByName());	// need to sort otherwise it will crash
	vector<Order> mergedVec;
	std::merge(orders.begin(), orders.end(), listOrders.begin(), listOrders.end(), back_inserter(mergedVec), OrderHelpers::sortByName());
	ofstream mergedOut("MergedFile.txt");
	for (Order o : mergedVec)
		mergedOut << o;
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	keep_window_open();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
