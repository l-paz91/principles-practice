// -----------------------------------------------------------------------------
#ifndef Calculator_H
#define Calculator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------

struct Token
{
	Token(char ch) : kind(ch), value(0) { }
	Token(char ch, double val) : kind(ch), value(val) { }
	Token(char ch, string s) : kind(ch), value(), name(s) {}

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

namespace Calculator
{
	double squareRoot();
	double powpow();
	double primary();
	double term();
	double expression();
	double declaration();
	double statement();
	string calculate(const string& input);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Calculator_H
