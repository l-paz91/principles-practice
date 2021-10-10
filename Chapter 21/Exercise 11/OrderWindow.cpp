// -----------------------------------------------------------------------------

//----INCLUDES----//
#define _CRT_SECURE_NO_WARNINGS
#include "OrderWindow.h"

// -----------------------------------------------------------------------------

namespace OrderPrivate
{
	namespace
	{
		static stringstream ss;
	}
}

// -----------------------------------------------------------------------------

Graph_lib::OrderWindow::OrderWindow(Point xy, int w, int h, const char* title)
	: Window(xy, w, h, title)
	, mQuitBtn(Point(double(x_max()) - 70, 0), 70, 20, "Quit",
		[](Address, Address addr) { reference_to<OrderWindow>(addr).quitPressed(); })
	, mAddPurchaseBtn(Point(390, 110), 100, 20, "Add Purchase",
		[](Address, Address addr) { reference_to<OrderWindow>(addr).addPurchasePressed(); })
	, mCheckoutBtn(Point(390, 340), 70, 20, "Checkout",
		[](Address, Address addr) { reference_to<OrderWindow>(addr).checkoutPressed(); })
	, mPurchaseOutbox(Point(77, 110), 300, 250, "")
	, mNameInput(Point(77, 20), 200, 20, "Name: ")
	, mAddressInput(Point(77, 50), 300, 20, "Address: ")
	, mPurchaseInput(Point(77, 80), 250, 20, "Purchase: ")
	, mPriceInput(Point(380, 80), 70, 20, "Price: ")
	, mQuantityInput(Point(530, 80), 50, 20, "Quantity: ")
	, mCheckedOut(true)
{
	attach(mQuitBtn);
	attach(mAddPurchaseBtn);
	attach(mCheckoutBtn);
	attach(mPurchaseOutbox);
	attach(mNameInput);
	attach(mAddressInput);
	attach(mPurchaseInput);
	attach(mPriceInput);
	attach(mQuantityInput);
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderWindow::quitPressed()
{
	time_t t = std::time(nullptr);
	string date = ctime(&t);
	date.erase(10, date.size()-1);
	ofstream out(date + " Orders.txt");
	for (Order o : mOrders)
		out << o;

	hide();
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderWindow::addPurchasePressed()
{
	if (mCheckedOut)
	{
		OrderPrivate::ss << mNameInput.get_string() << endl;
		OrderPrivate::ss << mAddressInput.get_string() << endl;

		time_t t = std::time(nullptr);
		OrderPrivate::ss << ctime(&t);

		mCheckedOut = false;
	}

	// get purchase
	OrderPrivate::ss << mPurchaseInput.get_string() << "*" 
					 << mPriceInput.get_string() << "*" 
					 << mQuantityInput.get_string() << endl;

	mPurchaseOutbox.put(OrderPrivate::ss.str());
	mPurchaseInput.put("");
	mPriceInput.put("");
	mQuantityInput.put("");
}

// -----------------------------------------------------------------------------

void Graph_lib::OrderWindow::checkoutPressed()
{
	mCheckedOut = true;

	Order order;
	order.readInFromFile(OrderPrivate::ss);
	mOrders.push_back(order);

	// clear fields
	OrderPrivate::ss.str("");
	OrderPrivate::ss.clear();
	mNameInput.put("");
	mAddressInput.put("");
	mPurchaseInput.put("");
	mPriceInput.put("");
	mQuantityInput.put("");
	mPurchaseOutbox.put("");
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
