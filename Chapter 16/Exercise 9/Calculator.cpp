// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Calculator.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	const string sqrtKey = "sqrt";
	const string letKey = "let";
	const string powKey = "pow";
	const string constKey = "const";

	// -----------------------------------------------------------------------------

	Token Token_stream::get()
	{
		if (full) { full = false; return buffer; }
		char ch;

		cin.get(ch);		//doesn't skip whitespace characters

		//check if ch is space
		while (isspace(ch))
		{
			//if '\n' then return
			if (ch == newLine)
				return Token(print);

			//skip whitespace characters
			cin.get(ch);
		}
		switch (ch)
		{
		case '(': case ')':
		case '+': case '-': case ',':
		case '*': case '/': case '%':
		case let: case print:
			return Token(ch);

		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.unget();
			double val;
			cin >> val;
			return Token(number, val);
		}

		default:
			if (isalpha(ch) || ch == '_')
			{
				string s;
				s += ch;

				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
					s += ch;
				cin.unget();

				if (s == letKey)
					return Token(Symbol::let);
				else if (s == sqrtKey)
					return Token(Symbol::sqrtCh);
				else if (s == powKey)
					return Token(Symbol::powCh);
				else if (s == constKey)
					return Token(Symbol::constCh);

				return Token(name, s);
			}
			error("Bad token");
		}
	}

	// -----------------------------------------------------------------------------

	void Token_stream::ignore()
	{
		if (full)
		{
			full = false;
			return;
		}
	}

	// -----------------------------------------------------------------------------

	double Symbol_table::get_value(string s)
	{
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == s) return names[i].value;
		error(s, " is undefined.");
	}

	// -----------------------------------------------------------------------------

	void Symbol_table::set_value(string s, double d)
	{
		for (int i = 0; i < names.size(); ++i)
		{
			if (names[i].name == s)
			{
				names[i].value = d;
				return;
			}
		}

		error(s, " is undefined.");
	}

	// -----------------------------------------------------------------------------

	int Symbol_table::is_declared(string s)
	{
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == s) return true;
		return false;
	}

	// -----------------------------------------------------------------------------

	int Symbol_table::isSetConst(string s)
	{
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == s)
			{
				if (names[i].isConst == true)
					return true;
			}
		return false;
	}

	// -----------------------------------------------------------------------------

	void Symbol_table::reassignVariable(string name, double val, bool b)
	{
		for (int i = 0; i < names.size(); ++i)
			if (names[i].name == name)
			{
				names[i].value = val;
				names[i].isConst = b;
			}
		cout << "\nValue re-assigned." << endl;
	}

	// -----------------------------------------------------------------------------

	double Symbol_table::define_name(string var, double val, bool isConst)
	{
		if (is_declared(var))
		{
			if (!isSetConst(var))
				Symbol_table::reassignVariable(var, val, isConst);
			else
				cout << "\nValue cannot be re-assigned." << endl;
			return val;
		}

		names.push_back(Variable{ var,val, isConst });

		return val;
	}

	// -----------------------------------------------------------------------------

	Token_stream ts;			//excellent variable names
	Symbol_table st;			//much description

	double expression();

	//handle sqrt(expression)
	double squareRoot()
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '(':
		{
			double d = expression();

			//handle if d is 0 or negative
			if (d <= 0)
				error(to_string(d), " cannot be square routed.");

			t = ts.get();
			if (t.kind != ')')
				error(" ')' was expected.");
			return std::sqrt(d);
		}
		default:
			error(" '(' was expected.");
		}
	}

	// -----------------------------------------------------------------------------

	//handle pow(expression, expression)
	double powpow()
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '(':
		{
			double d = expression(); // first expression

			t = ts.get();
			if (t.kind != ',')
				error(" ',' was expected.");

			double d2 = expression(); //second expression

			t = ts.get();
			if (t.kind != ')')
				error(" ')' was expected.");

			return std::pow(d, d2);
		}
		default:
			error(" '(' was expected.");
		}
	}

	// -----------------------------------------------------------------------------

	double primary()
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '(':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')')
				error(" ')' was expected.");
			return d;
		}
		case '-':
			return -primary();
		case Symbol::number:
			return t.value;
		case Symbol::name:
			return st.get_value(t.name);
		case Symbol::sqrtCh:
			return squareRoot();
		case Symbol::powCh:
			return powpow();
		default:
			error("primary expected.");
		}
	}

	// -----------------------------------------------------------------------------

	double term()
	{
		double left = primary();
		while (true)
		{
			Token t = ts.get();
			switch (t.kind)
			{
			case '*':
				left *= primary();
				break;
			case '/':
			{
				double d = primary();
				if (d == 0) error("divide by zero. ");
				left /= d;
				break;
			}
			case '%':
			{
				double d = primary();
				if (d == 0) error("Divide by zero. ");
				left = fmod(left, d);
				break;
			}
			default:
				ts.unget(t);
				return left;
			}
		}
	}

	// -----------------------------------------------------------------------------

	double expression()
	{
		double left = term();
		while (true)
		{
			Token t = ts.get();
			switch (t.kind)
			{
			case '+':
				left += term();
				break;
			case '-':
				left -= term();
				break;
			default:
				ts.unget(t);
				return left;
			}
		}
	}

	// -----------------------------------------------------------------------------

	double declaration()
	{
		double d(0);
		Token t = ts.get();

		switch (t.kind)
		{
		case Symbol::name:
		{
			string name = t.name;
			if (st.is_declared(name))
			{
				if (st.isSetConst(name))
					error("variable is set to const and cannot be changed.");

				Token t2 = ts.get();
				if (t2.kind != '=')
					error(name, "= missing in declaration. ");

				d = expression();
				st.reassignVariable(name, d, false);
			}
			else
			{
				Token t2 = ts.get();
				if (t2.kind != '=')
					error(name, "= missing in declaration. ");

				d = expression();
				st.addName(name, d, false);
			}
			break;
		}
		case Symbol::constCh:
		{
			Token t = ts.get();
			if (t.kind != name)
				error("name expected in declaration. ");

			//check to see if already declared
			string name = t.name;
			if (st.is_declared(name))
			{
				//now check to see if it was const
				if (st.isSetConst(name))
				{
					error("That variable cannot be changed.");
				}
				else
				{
					Token t2 = ts.get();
					if (t2.kind != '=')
						error(name, "= missing in declaration.");

					//variable wasn't const, allow it to be overwritten && set to const
					d = expression();
					st.reassignVariable(name, d, true);
				}
			}
			else
			{
				//no existing variable - create a new const one
				Token t2 = ts.get();
				if (t2.kind != '=')
					error(name, "= missing in declaration. ");

				d = expression();
				st.addName(name, d, true);
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

	double statement()
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case Symbol::let:
			return declaration();
		default:
			ts.unget(t);
			return expression();
		}
	}

	// -----------------------------------------------------------------------------

	string calculate(string input)
	{
		//put the input "into" cin
		//streambuf* backup;
		istringstream oss(input);
		//backup = cin.rdbuf();
		cin.rdbuf(oss.rdbuf());

		//now do normal calculator stuff as we have "characters in the buffer"
		//Token t = ts.get();
		string answer = to_string(statement());
		
		//clean up token stream
		ts.ignore();

		return answer;
	}

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
