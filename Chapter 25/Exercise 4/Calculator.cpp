// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Calculator.h"

// -----------------------------------------------------------------------------

void Calculator::printHelp()
{
	cout << "//------------------------------------------------------------------------------//" << '\n';
	cout << "Operators available: {}, (), +, -, /, *" << '\n';
	cout << "Square root available. Example: 5 + sqrt(25)" << '\n';
	cout << "Pow available. Example: 5 + pow(2, 3)" << '\n';
	cout << "Bitwise AND available. Example: 5 & 5" << '\n';
	cout << "Bitwise OR available. Example: 5 | 5" << '\n';
	cout << "Bitwise XOR available. Example: 5 ^ 5" << '\n';
	cout << "Bitwise NOT available. Example: ~(3) + ~(10)" << '\n';

	cout << "\nPre-defined names: k = 1000 || sqrt() || pow(,)" << '\n';
	cout << "Define your own names using " << SymbolKeywords::letKey << " name = number;" << '\n';
	cout << "Define const names using " << SymbolKeywords::letKey << " const name = number;" << '\n';
	cout << "Use enter to print and 'exit' to quit" << '\n';
	cout << "//------------------------------------------------------------------------------//" << endl;
}

// -----------------------------------------------------------------------------

void Calculator::calculate()
{
	const string prompt = "> ";
	const string result = "= ";


	cout << "//------------------------------------------------------------------------------//" << endl;
	cout << "Welcome to our simple calculator.\nPress H for instructions." << endl;
	cout << "//------------------------------------------------------------------------------//" << endl;


	cout << prompt;

	while (true)
	try
	{
		Token t = mTokenStream.get();

		while (t.mType == Symbol::print)
		{
			cout << prompt;
			t = mTokenStream.get();
		}

		if (t.mType == Symbol::help)
		{
			printHelp();
			cin.clear(); cin.ignore();		// flush out everything in cin to 'reset' calculator
			cout << prompt;
			t = mTokenStream.get();
		}

		if (t.mType == Symbol::quit)
			return;
		mTokenStream.unGet(t);

		cout << result << statement() << endl;
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
		cleanUpMess();
	}
}

// -----------------------------------------------------------------------------

double Calculator::defineName(string pName, double pValue, bool pIsConst)
{
	return mSymbolTable.defineName(pName, pValue, pIsConst);
}

// -----------------------------------------------------------------------------

double Calculator::squareRoot()
{
	Token t = mTokenStream.get();
	switch (t.mType)
	{
		case '(':
		{
			double d = expression();

			// handle if d is 0 or negative
			if (d <= 0)
			{
				error(to_string(d), " cannot be square routed.");
			}

			t = mTokenStream.get();
			if (t.mType != ')')
			{
				error(" ')' was expected.");
			}

			return std::sqrt(d);
		}

		default:
			error(" '(' was expected.");
			return t.mValue;
	}
}

// -----------------------------------------------------------------------------

double Calculator::powPow()
{
	Token t = mTokenStream.get();
	switch (t.mType)
	{
		case '(':
		{
			double d = expression(); // first expression

			t = mTokenStream.get();
			if (t.mType != ',')
			{	
				error(" ',' was expected.");
			}

			double d2 = expression(); //second expression

			t = mTokenStream.get();
			if (t.mType != ')')
			{	
				error(" ')' was expected.");
			}

			return std::pow(d, d2);
		}
		default:
			error(" '(' was expected.");
			return t.mValue;
	}
}

// -----------------------------------------------------------------------------

double Calculator::performNOT()
{
	Token t = mTokenStream.get();
	switch (t.mType)
	{
	case '(':
	{
		double d = expression();

		double dPointerType{};
		if (!(modf(d, &dPointerType) == 0.0))
		{
			cout << "\nWarning, attempting a bitwise operation on a double/float. Value will be cast to an int.";
		}

		int temp = ~(int)d;

		t = mTokenStream.get();
		if (t.mType != ')')
		{
			error(" ')' was expected.");
		}

		return temp;
	}
	default:
		error(" '(' was expected.");
		return t.mValue;
	}
}

// -----------------------------------------------------------------------------

double Calculator::primary()
{
	Token t = mTokenStream.get();
	switch (t.mType)
	{
	case '(':
	{
		double d = expression();
		t = mTokenStream.get();
		if (t.mType != ')')
		{	
			error(" ')' was expected.");
		}
		return d;
	}
	case '-':
		return -primary();
	case Symbol::number:
		return t.mValue;
	case Symbol::name:
		return mSymbolTable.getValue(t.mName);
	case Symbol::sqrtCh:
		return squareRoot();
	case Symbol::powCh:
		return powPow();
	case Symbol::bitwiseNOT:
		return performNOT();
	default:
		error("primary expected.");
		return t.mValue;
	}
}

// -----------------------------------------------------------------------------

double Calculator::term()
{
	double left = primary();
	while (true)
	{
		Token t = mTokenStream.get();
		switch (t.mType)
		{
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();

			if (d == 0)
			{
				error("divide by zero. ");
			}

			left /= d;
			break;
		}
		case '%':
		{
			double d = primary();

			if (d == 0)
			{
				error("Divide by zero. ");
			}

			left = fmod(left, d);
			break;
		}
		default:
			mTokenStream.unGet(t);
			return left;
		}
	}
}

// -----------------------------------------------------------------------------

double Calculator::expression()
{
	double left = term();
	while (true)
	{
		Token t = mTokenStream.get();
		switch (t.mType)
		{
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		case Symbol::bitwiseAND: case Symbol::bitwiseOR: case Symbol::bitwiseXOR:
		{
			double leftPointerType{};
			if (!(modf(left, &leftPointerType) == 0.0))
			{
				cout << "\nWarning, attempting a bitwise operation on a double/float. Value will be cast to an int.";
			}

			if (t.mType == Symbol::bitwiseAND)
			{
				left = (int)left & (int)term();
				break;
			}
			if (t.mType == Symbol::bitwiseOR)
			{
				left = (int)left | (int)term();
				break;
			}
			if (t.mType == Symbol::bitwiseXOR)
			{
				left = (int)left ^ (int)term();
				break;
			}
		}
		default:
			mTokenStream.unGet(t);
			return left;
		}
	}
}

// -----------------------------------------------------------------------------

double Calculator::declaration()
{
	double d(0);
	Token t = mTokenStream.get();

	switch (t.mType)
	{
	case Symbol::name:
	{
		string name = t.mName;
		if (mSymbolTable.isDeclared(name))
		{
			if (mSymbolTable.isSetConst(name))
			{	
				error("variable is set to const and cannot be changed.");
			}

			Token t2 = mTokenStream.get();
			if (t2.mType != '=')
			{
				error(name, "= missing in declaration. ");
			}

			d = expression();
			mSymbolTable.reassignVariable(name, d, false);
		}
		else
		{
			Token t2 = mTokenStream.get();
			if (t2.mType != '=')
			{
				error(name, "= missing in declaration. ");
			}

			d = expression();
			mSymbolTable.addName(name, d, false);
		}
		break;
	}
	case Symbol::constCh:
	{
		Token t = mTokenStream.get();
		if (t.mType != name)
		{
			error("name expected in declaration. ");
		}

		//check to see if already declared
		string name = t.mName;
		if (mSymbolTable.isDeclared(name))
		{
			//now check to see if it was const
			if (mSymbolTable.isSetConst(name))
			{
				error("That variable cannot be changed.");
			}
			else
			{
				Token t2 = mTokenStream.get();
				if (t2.mType != '=')
				{
					error(name, "= missing in declaration.");
				}

				//variable wasn't const, allow it to be overwritten && set to const
				d = expression();
				mSymbolTable.reassignVariable(name, d, true);
			}
		}
		else
		{
			//no existing variable - create a new const one
			Token t2 = mTokenStream.get();
			if (t2.mType != '=')
			{
				error(name, "= missing in declaration. ");
			}

			d = expression();
			mSymbolTable.addName(name, d, true);
		}
		break;
	}
	default:
		error("name expected in declaration or const name.");
		break;
	}

	return d;
}

// -----------------------------------------------------------------------------

double Calculator::statement()
{
	Token t = mTokenStream.get();
	switch (t.mType)
	{
	case Symbol::let:
		return declaration();
	default:
		mTokenStream.unGet(t);
		return expression();
	}
}

// -----------------------------------------------------------------------------

void Calculator::cleanUpMess()
{
	mTokenStream.ignore(print);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
