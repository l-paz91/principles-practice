// -----------------------------------------------------------------------------
#ifndef TokenStream_H
#define TokenStream_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Token.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

class TokenStream
{
public:
	TokenStream() : mBuffer(0), mBufferFull(false) {}

	Token get();

	void unGet(Token pToken);
	void ignore(char pType);

private:
	Token mBuffer;
	bool mBufferFull;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TokenStream_H
