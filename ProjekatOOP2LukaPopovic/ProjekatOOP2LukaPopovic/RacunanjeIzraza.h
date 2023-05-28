#pragma once
//Luka Popovic SV4/2021
// 6.1.2023.
//Zaglavlje sa funkcijama zaduzeno za racunanje tacnog izraza
//void solve() je kao neki main i grupise ostale funkcije
//funkcija string concat sluzi samo za printovanje 
//ucitavanje_file, read_ucitaj i izraz_resenje sluzi samo da bi se videlo
//s kojim brojevima treba da radi solve i all_values
//moglo je bez te 3 f-je da sam to ubacio u main al sam stavio ovako da bi bilo organizovanije
#include "Kalkulator.h"
#include<map>

template <typename T>class Racunanje {
	string concat(string&, string&, char);
	map<T, string> all_values(T, T);
	void ucitavanje_file(ifstream&);
	void read_ucitaj();
	void solve();
	string izraz_resenje();
};

#include "RacunanjeIzraza.tpp"