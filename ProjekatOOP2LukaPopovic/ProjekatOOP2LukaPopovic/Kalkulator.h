#pragma once
//Luka Popovic SV4/2021
// 6.1.2023.
//Advanced Calculator prepravljen sa vezbi 3
//Klase Token, TokenStream su bili spojeni u vezbama 3 (sve u jednom file),
// pa sam razdvojio cisto da bude preglednije tako da tamo nece biti nista komentarisano
//vec je poznat kod tako da necu objasnjavati
#include "TokenStream.h"
#include "Token.h"

double get_value(string);
void set_value(string, double);
bool is_declared(string );
double primary();
double term();
double expression();
double declaration();
double statement();
void clean_up_mess();
double calculate();
vector<double> korisceniBrojevi();
void brisanjeBrojevi();