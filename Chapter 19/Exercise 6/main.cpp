// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 6
/*
	Repeat the previous exercise, but with a class Number<T> where T can be any 
	numeric type. Try adding % to Number and see what happens when you try to 
	use % for Number<double> and Number<int>.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "NumberClass.h"

// -----------------------------------------------------------------------------

int main()
{
	Number<int> num(10);
	cout << num << endl;

	Number<double> numd(10.5f);
	cout << numd << endl;

	cout << "New number: "; cin >> num;
	cout << num << endl;

	num = num + 5;
	cout << num << endl;

	double i = num.get();
	cout << i << endl;

	num = 101;
	num = num % 2;
	cout << num << endl;

	num %= 2;
	cout << num << endl;

	//numd %= 2;
	cout << numd << endl;

	//num += 5;
	//cout << num << endl;

	//num = num * 10;
	//cout << num << endl;

	//num *= 10;
	//cout << num << endl;

	//num = num / 10;
	//cout << num << endl;

	//num /= 10;
	//cout << num << endl;

	//num = num - 100;
	//cout << num << endl;

	//num -= 100;
	//cout << num << endl;

	//Number<int> num2 = 20;
	//num = num2;
	//cout << num << endl;

	//num = num + num2;
	//cout << num << endl;

	//num = num - num2;
	//cout << num << endl;

	//num = num * num2;
	//cout << num << endl;

	//num = num / num2;
	//cout << num << endl;

	//num += num2;
	//cout << num << endl;

	//num -= num2;
	//cout << num << endl;

	//num *= num2;
	//cout << num << endl;

	//num /= num2;
	//cout << num << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
