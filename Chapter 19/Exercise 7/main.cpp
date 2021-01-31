// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 7
/*
	Try your solution to exercise 2 with some Numbers. 
	
	Will produce some nasty looking template warnings but it's basically telling
	you about data loss.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "NumberClass.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

template<typename T1, typename T2>
typename common_type<T1, T2>::type f2(vector<T1>& vt, vector<T2>& vu)
{
	uint32 s = (vt.size() <= vu.size()) ? vt.size() : vu.size();
	typename common_type<T1, T2>::type sum = 0;

	for (uint32 i = 0; i < s; ++i)
		sum += vt[i] * vu[i];

	return sum;
}

// -----------------------------------------------------------------------------

int main()
{
	vector<Number<int>> v1{ 10, 1, 24, 50, 98, 4, 345, 10 };
	vector<Number<int>> v2(8, 10);

	vector<Number<double>> v3{ 10.1, 100.1, 73.5, 9.765, 8, 9001, 86.5, 78.3, 9.2, 11 };
	vector<Number<double>> v4(9, 10.5);

	vector<Number<char>> v5{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	vector<Number<char>> v6{ 11, 'z' };

	cout << "Sum: " << f2(v1, v4);
	cout << endl;

	cout << "Sum: " << f2(v3, v6);
	cout << endl;

	cout << "Sum: " << f2(v2, v5);
	cout << endl;

	vector<int> v11{ 10, 1, 24, 50, 98, 4, 345, 10 };
	vector<int> v22(8, 10);

	vector<double> v33{ 10.1, 100.1, 73.5, 9.765, 8, 9001, 86.5, 78.3, 9.2, 11 };
	vector<double> v44(9, 10.5);

	vector<char> v55{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	vector<char> v66{ 11, 'z' };

	// will not compile as strings cannot be multiplied together
	//vector<string> v7{ "apple", "banana", "cantaloupe", "dingleberry" };
	//vector<string> v8{ 10, "-smoothie" };

	cout << "Sum: " << f2(v11, v44);
	cout << endl;

	cout << "Sum: " << f2(v33, v66);
	cout << endl;

	cout << "Sum: " << f2(v55, v22);
	cout << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
