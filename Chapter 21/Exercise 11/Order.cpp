// -----------------------------------------------------------------------------
// 
//--INCLUDES--//
#include "Order.h"

// -----------------------------------------------------------------------------

Order::Order(string pName, string pAddress, time_t pDate, vector<Purchase>& pPurchases)
	: mName(pName)
	, mAddress(pAddress)
	, mDate(pDate)
	, mPurchases(pPurchases)
{}

// -----------------------------------------------------------------------------

Order::Order(string pName, string pAddress, time_t pDate, std::initializer_list<Purchase> pList)
	: mName(pName)
	, mAddress(pAddress)
	, mDate(pDate)
	, mPurchases(pList)
{}

// -----------------------------------------------------------------------------

Order::Order(string pFileName)
	: Order()
{
	ifstream readIn{ pFileName };
	if (!readIn)
	{
		cout << "Error opening: " << pFileName << endl;
		return;
	}
	readInFromFile(readIn);
}

// -----------------------------------------------------------------------------

void Order::writeToFile()
{
	ofstream out(mName + " Order.txt");
	writeOut(out);
}

// -----------------------------------------------------------------------------

ostream& operator<<(ostream& outStream, const Order& o)
{
	return o.writeOut(outStream);
}

// -----------------------------------------------------------------------------

void Order::readInFromFile(istream& readIn)
{
	if (!mName.empty())
	{
		cout << "This order already contains data and cannot be overwritten." << endl;
			return;
	}

	// get name
	getline(readIn, mName);
	if (mName.empty())
		return;

	// get address
	getline(readIn, mAddress);

	// get date
	string date;
	getline(readIn, date);
	istringstream ss(date);
	ss.imbue(locale("en_GB.UTF-8"));
	tm tm{};
	ss >> get_time(&tm, "%a %b  %d %H:%M:%S %Y");
	if (ss.fail())
		cout << "Date parsing failed. Incorrect format." << endl;
	else
		mDate = mktime(&tm);

	// get purchases
	string line;
	while (getline(readIn, line) && line != "")
	{
		istringstream is(line);
		Purchase temp;
		is >> temp;
		mPurchases.push_back(temp);
	}
}

// -----------------------------------------------------------------------------

const double Order::getPurchaseValue() const
{
	double d = 0.0;
	for (Purchase p : mPurchases)
		d += p.getPurchaseValue();
	return d;
}

// -----------------------------------------------------------------------------

std::ostream& Order::writeOut(ostream& os) const
{
	os << mName << "\n"
		<< mAddress << "\n";

	string time = ctime(&mDate);
	os << time;

	for (const Purchase& p : mPurchases)
		os << p;

	os << endl;
	return os;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
