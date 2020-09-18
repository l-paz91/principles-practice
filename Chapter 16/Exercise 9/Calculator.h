// -----------------------------------------------------------------------------
#ifndef CALCULATOR_H_
#define CALCULATOR_H_

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// introduced in C++11, enums can now have a type instead of just being an integer
	// it does add a little extra text but groups them together nicely
	enum Symbol : const char
	{
		let = '#',
		quit = 'Q',
		print = '=',
		number = '8',
		name = 'a',
		sqrtCh = 's',
		powCh = 'p',
		constCh = 'c',
		help = 'H',
		newLine = '\n'
	};

	struct Token
	{
		Token(char ch) : kind(ch), value(0) { }
		Token(char ch, double val) : kind(ch), value(val) { }
		Token(char ch, string s) : kind(ch), name(s) {}

		char kind;
		double value;
		string name;
	};

	// -----------------------------------------------------------------------------

	class Token_stream
	{
	public:
		Token_stream() 
			: full(0)
			, buffer(0) 
		{ }

		Token get();
		void unget(Token t) { buffer = t; full = true; }
		void ignore();

	private:
		bool full;
		Token buffer;
	};

	// -----------------------------------------------------------------------------

	struct Variable
	{
		Variable(string n, double v) 
			: name(n)
			, value(v) 
		{ }
		
		Variable(string n, double v, bool b) 
			: name(n)
			, value(v)
			, isConst(b) 
		{ }

		string name;
		double value;
		bool isConst;
	};

	// -----------------------------------------------------------------------------

	class Symbol_table
	{
	public:
		Symbol_table() {}
		~Symbol_table() {}

		vector<Variable> getNames() { return names; }
		void addName(string s, double d, bool b) { names.push_back(Variable(s, d, b)); }

		double get_value(string s);
		void set_value(string s, double d);
		int is_declared(string s);
		int isSetConst(string s);
		void reassignVariable(string name, double val, bool b);
		double define_name(string var, double val, bool isConst);

	private:
		vector<Variable> names;
	};

	// -----------------------------------------------------------------------------

	double squareRoot();
	double powpow();
	double primary();
	double term();
	double expression();
	double declaration();
	double statement();
	string calculate(string input);

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !CALCULATOR_H_

