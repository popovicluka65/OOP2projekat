#pragma once
//Luka Popovic SV4/2021
// 6.1.2023.
#include "std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch);
	Token(char ch, double val);
	Token(char ch, string val);
};