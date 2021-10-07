// -----------------------------------------------------------------------------
#ifndef ORDER_H
#define ORDER_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS
#include "std_lib_facilities.h"

#include <ctime>

// -----------------------------------------------------------------------------

class Purchase
{
public:
	Purchase() : mProductName(), mUnitPrice(), mQuantity() {}
	Purchase(string pName, double pPrice, int pAmount)
		: mProductName(pName)
		, mUnitPrice(pPrice)
		, mQuantity(pAmount)
	{}

	const double getPurchaseValue() const { return mUnitPrice * mQuantity; }

	friend ostream& operator<<(ostream& outStream, const Purchase& p)
	{
		outStream << p.mProductName << "*"
			<< p.mUnitPrice << "*"
			<< p.mQuantity << endl;
		return outStream;
	}

	friend istream& operator>>(istream& inStream, Purchase& p)
	{
		string line;
		getline(inStream, line);

		size_t star1 = line.find('*');
		p.mProductName = line.substr(0, star1);

		size_t star2 = line.find('*', star1 + 1);
		size_t diff = star2 - (star1 + 1);
		p.mUnitPrice = stod(line.substr(star1 + 1, diff));

		size_t newline = line.find('\n', star2 + 1);
		diff = newline - (star2 + 1);
		p.mQuantity = stoi(line.substr(star2 + 1, diff));

		return inStream;
	}

private:
	string mProductName;
	double mUnitPrice;
	int mQuantity;
};

// -----------------------------------------------------------------------------

class Order
{
public:
	Order() : mName(), mAddress(), mDate(), mPurchases() {}

	Order(string pName, string pAddress, time_t pDate, vector<Purchase>& pPurchases);
	Order(string pName, string pAddress, time_t pDate, std::initializer_list<Purchase> pList);
	Order(string pFileName);

	void writeToFile();
	friend ostream& operator<<(ostream& outStream, const Order& o);
	void readInFromFile(ifstream& readIn);
	const double getPurchaseValue() const;

	const string& getName() const { return mName; }
	const string& getAddress() const { return mAddress; }

private:
	ostream& writeOut(ostream& os) const;

	string mName;
	string mAddress;
	time_t mDate;
	vector<Purchase> mPurchases;
};

// -----------------------------------------------------------------------------

namespace OrderHelpers
{
	template<typename Container>
	void getOrdersFromFile(Container& pCont, string pFileName)
	{
		ifstream readIn{ pFileName };
		if (!readIn)
		{
			cout << "Error opening: " << pFileName << endl;
			return;
		}

		while (!readIn.eof())
		{
			Order order;
			order.readInFromFile(readIn);
			pCont.insert(pCont.begin(), order);
		}
	}

	struct sortByName
	{
		bool operator()(const Order& o1, const Order& o2)
		{
			return o1.getName() < o2.getName();
		}
	};

	struct sortByAddress
	{
		bool operator()(const Order& o1, const Order& o2)
		{
			return o1.getAddress() < o2.getAddress();
		}
	};
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ORDER_H
