#include "RacunanjeIzraza.h"

int redni_broj_ucitano = 0;
int n = 6, trazeni_broj;
template<typename T>
vector<T> vektor_brojeva;
template<typename T>
vector<vector<T>> brojevi_ucitavanje;
template<typename T>
vector<T> red_ucitavanje;
string ispis_resenja = "";

string concat(string& a, string& b, char op) {
    return "(" + a + " " + string(1, op) + " " + b + ")";
}

template<typename T>
map<T, string> all_values(T l, T r) {
    map<T, string> mp;
    if (l == r) {
        mp[vektor_brojeva<T>[l]] = to_string(vektor_brojeva<T>[l]);
        return mp;
    }

    for (T mid = l; mid < r; mid++) {
        map<T, string> mpa = all_values(l, mid);
        map<T, string> mpb = all_values(mid + 1, r);
        for (auto& x : mpa) {
            for (auto& y : mpb) {
                mp[x.first + y.first] = concat(x.second, y.second, '+');
                mp[x.first - y.first] = concat(x.second, y.second, '-');
                mp[x.first * y.first] = concat(x.second, y.second, '*');
                if (y.first && x.first % y.first == 0)
                    mp[x.first / y.first] = concat(x.second, y.second, '/');
            }
        }
    }
    return mp;
}
template <typename T>
void ucitavanje_file(ifstream& in) {
    while (!in.eof())
    {
        int broj = 0;
        string data;
        getline(in, data);
        string tmp = "";
        for (char c : data) {
            if (c == ' ') {
                broj = stoi(tmp);
                red_ucitavanje<T>.push_back(broj);
                tmp = "";
            }
            else if (c == '\t') {
                broj = stoi(tmp);
                red_ucitavanje<T>.push_back(broj);
                tmp = "";
                brojevi_ucitavanje<T>.push_back(red_ucitavanje<T>);
                red_ucitavanje<T>.clear();
            }
            else {
                tmp += c;
            }
        }
    }

}

template<typename T>
void read_ucitaj() {
    vektor_brojeva<T>.resize(n);
    for (int i = 0; i < 6; i++) {
        vektor_brojeva<T>[i] = brojevi_ucitavanje<T>[redni_broj_ucitano][i];
    }
    trazeni_broj = brojevi_ucitavanje<T>[redni_broj_ucitano][6];
}

template<typename T>
void solve() {
    redni_broj_ucitano++;
    //sortiranje
    //vektor brojeva su brojevi s kojim treba da se nadje resenje
    sort(vektor_brojeva<T>.begin(), vektor_brojeva<T>.end());
    do {
        map<T, string> mp = all_values(0, n - 1);
        //ako je mp.count od trazenog broja 1, onda je taj broj i ispisuje se a ako nije permutuje se
        if (mp.count(trazeni_broj)) {
            cout << trazeni_broj << " = ";
            //printa izraz
            cout << mp[trazeni_broj] << endl;
            ispis_resenja = mp[trazeni_broj];
            return;
        }
    } while (next_permutation(vektor_brojeva<T>.begin(), vektor_brojeva<T>.end()));
    //nakon sto se zavrsi ova petlja ako se izadje onda nema resenja
    //zato moramo naci prvi priblizan
    //tako sto moramo ici od trazenog broja za jedan gore i jedan dole pa sta prvo naidje izacice
    //ostalo je isto ko gore naveden kod samo sto imamo 2 ifa, za trazeni broj manje i trazeni broj veci
    cout << "Nema resenja" << endl;

    int trazeni_broj_manji = trazeni_broj;
    int trazeni_broj_veci = trazeni_broj;
    sort(vektor_brojeva<T>.begin(), vektor_brojeva<T>.end());
    do {
        trazeni_broj_manji -= 1;
        trazeni_broj_veci += 1;
        map<T, string> mp = all_values(0, n - 1);
        if (mp.count(trazeni_broj_manji)) {
            cout << trazeni_broj_manji << " = ";
            ispis_resenja = mp[trazeni_broj_manji];
            //printa izraz
            cout << mp[trazeni_broj_manji] << endl;
            return;
        }
        if (mp.count(trazeni_broj_veci)) {
            cout << trazeni_broj_veci << " = ";
            ispis_resenja = mp[trazeni_broj_veci];
            //printa izraz
            cout << mp[trazeni_broj_veci] << endl;
            return;
        }
    } while (next_permutation(vektor_brojeva<T>.begin(), vektor_brojeva<T>.end()));
}

string izraz_resenje() {
    return ispis_resenja;
}