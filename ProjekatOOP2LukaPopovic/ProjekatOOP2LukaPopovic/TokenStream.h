#pragma once
//Luka Popovic SV4/2021
// 6.1.2023.
#include "Token.h"

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream();

	Token get();
	void unget(Token t);
	void ignore(char);
};
