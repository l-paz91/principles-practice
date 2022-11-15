// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TokenStream.h"
#include "SymbolTable.h"

// -----------------------------------------------------------------------------

Token TokenStream::get()
{
	if (mBufferFull)
	{
		mBufferFull = false;
		return mBuffer;
	}

	char ch;
	cin.get(ch);

	while (isspace(ch))
	{
		if (ch == newLine)
		{
			return Token(print);
		}

		cin.get(ch);
	}

	switch (ch)
	{
		case '(': case ')':
		case '+': case '-':
		case '*': case '/': case '%':
		case '=': case ',':
		case let: case print:
		case Symbol::bitwiseAND: case Symbol::bitwiseNOT: case Symbol::bitwiseOR: case Symbol::bitwiseXOR:
		{
			return Token(ch);
		}

		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{	
			cin.unget();
			double val;
			cin >> val;

			return Token(val, Symbol::number);
		}

		default:
		{
			if (isalpha(ch) || ch == '_')
			{
				string s;
				s += ch;

				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
				{
					s += ch;
				}

				cin.unget();

				using namespace SymbolKeywords;

				if (s == letKey)
					return Token(Symbol::let);
				else if (s == quitKey || s == "Q" || s == "q")
					return Token(Symbol::quit);
				else if (s == sqrtKey)
					return Token(Symbol::sqrtCh);
				else if (s == powKey)
					return Token(Symbol::powCh);
				else if (s == constKey)
					return Token(Symbol::constCh);
				else if (s == helpKey || s == "H" || s == "h")
					return Token(Symbol::help);

				return Token(s, name);
			}
			
			return Token("Bad Token", Symbol::err);
		}
	}
}

// -----------------------------------------------------------------------------

void TokenStream::unGet(Token pToken)
{
	mBuffer = pToken;
	mBufferFull = true;
}

// -----------------------------------------------------------------------------

void TokenStream::ignore(char pType)
{
	mBufferFull = false;

	if (mBufferFull && pType == mBuffer.mType)
	{
		return;
	}

	cout << "Enter ';' to continue. ";
	char ch;
	while (cin >> ch)
	{
		if (ch == pType)
		{
			return;
		}
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
