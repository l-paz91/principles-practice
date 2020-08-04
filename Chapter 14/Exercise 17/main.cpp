// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 17
/*
	The exceptions defined in the C++ standard library, such as exception, runtime_error,
	and out_of_range (section 5.6.3), are organised into a class hierarchy (with a 
	useful virtual function what() returning a string supposedly explaining what 
	went wrong). Search your information sources for the C++ standard exception class 
	hierarchy and draw a class hierarchy diagram of it.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::CustomBinaryTree CBT;

// -----------------------------------------------------------------------------

// this is awful but I procrastinated on this exercise for two months so i did this in 20 minutes
// just to get it finally over with

int main()
{
	Simple_window win{ Point{100,100}, 800, 900, "Exercise 17" };

	CBT cbt("std::exception");
	cbt.addEntry("logic_error", "std::exception", Color::green, 40);

	cbt.addEntry("invalid_argument", "logic_error", Color::yellow, 60);
	cbt.addEntry("domain_error", "logic_error", Color::yellow, 60);
	cbt.addEntry("length_error", "logic_error", Color::yellow, 60);
	cbt.addEntry("out_of_range", "logic_error", Color::yellow, 60);
	cbt.addEntry("future_error(c++11)", "logic_error", Color::yellow, 60);

	cbt.addEntry("bad_optional_access(c++17)", "std::exception", Color::yellow, 40);
	cbt.addEntry("runtime_error", "std::exception", Color::green, 40);

	cbt.addEntry("range_error", "runtime_error", Color::yellow, 60);
	cbt.addEntry("overflow_error", "runtime_error", Color::yellow, 60);
	cbt.addEntry("underflow_error", "runtime_error", Color::yellow, 60);
	cbt.addEntry("regex_error(c++11)", "runtime_error", Color::yellow, 60);
	cbt.addEntry("system_error(c++11)", "runtime_error", Color::green, 60);

	cbt.addEntry("ios_base::failure(c++11)", "system_error(c++11)", Color::yellow, 80);
	cbt.addEntry("filesystem::filesystem_error(c++17)", "system_error(c++11)", Color::yellow, 80);

	cbt.addEntry("tx_exception(TMTS)", "runtime_error", Color::yellow, 60);
	cbt.addEntry("nonexistent_local_time(c++20)", "runtime_error", Color::yellow, 60);
	cbt.addEntry("ambiguous_local_time(c++20)", "runtime_error", Color::yellow, 60);
	cbt.addEntry("format_error(c++20)", "runtime_error", Color::yellow, 60);

	cbt.addEntry("bad_typeid", "std::exception", Color::yellow, 40);
	cbt.addEntry("bad_cast", "std::exception", Color::green, 40);

	cbt.addEntry("bad_any_cast(c++17)", "bad_cast", Color::yellow, 60);

	cbt.addEntry("bad_weak_ptr(c++11)", "std::exception", Color::yellow, 40);
	cbt.addEntry("bad_function_call(c++11)", "std::exception", Color::yellow, 40);
	cbt.addEntry("bad_alloc", "std::exception", Color::green, 40);

	cbt.addEntry("bad_array_new_lengths(c++11)", "bad_alloc", Color::yellow, 60);

	cbt.addEntry("bad_exception", "std::exception", Color::yellow, 40);
	cbt.addEntry("ios_base::failure(until c++11)", "std::exception", Color::yellow, 40);
	cbt.addEntry("bad_variant_access(c++17)", "std::exception", Color::yellow, 40);
	
	win.attach(cbt);
	win.wait_for_button();

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
