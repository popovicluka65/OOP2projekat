//Luka Popovic SV4/2021
#include "Token.h"

Token::Token(char ch) : kind(ch), value(0) {}

Token::Token(char ch, double val) : kind(ch), value(val) {}

Token::Token(char ch, string val) : kind(ch), name(val) {}

