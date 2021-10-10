// -----------------------------------------------------------------------------
#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"
#include "Order.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// Order window is a window that provides a simple GUI for orders

	struct OrderWindow : public Window
	{
	public:
		OrderWindow(Point xy, int w, int h, const char* title);

	private:
		// actions
		void quitPressed();
		void addPurchasePressed();
		void checkoutPressed();
    
		// objects
		vector<Order> mOrders;

		Button mQuitBtn, mAddPurchaseBtn, mCheckoutBtn;

		Multiline_Outbox mPurchaseOutbox;
		In_box mNameInput;
		In_box mAddressInput;
		In_box mPurchaseInput;
		In_box mPriceInput;
		In_box mQuantityInput;

		bool mCheckedOut;

	};

} // !namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ORDERWINDOW_H
