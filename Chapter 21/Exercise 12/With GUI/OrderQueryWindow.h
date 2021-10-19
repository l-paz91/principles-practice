// -----------------------------------------------------------------------------
#ifndef ORDERQUERYWINDOW_H
#define ORDERQUERYWINDOW_H
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"
#include "Order.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	struct OrderQueryWindow : public Window 
	{
	public:
		OrderQueryWindow(Point xy, int w, int h, const char* title);

	private:
		// actions
		void quitPressed();
		void openFilePressed();
		void searchPressed();

		// callbacks


		// objects
		vector<Order> mOrders;

		MultilineScroll_Outbox mOrdersOutput;

		In_box mFileNameInput;
		Out_box mPurchaseTotalOutput;
		In_box mSearchNameInput;

		Button mOpenFileBtn, mQuitBtn, mSearchBtn;

	};

} // !namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ORDERQUERYWINDOW_H
