//Luka Popovic SV4/2021
//6.1.2023.
//komentarisanje ce biti iznad linije koja mozda nije jasna i iznad svake funkcije
#include "RacunanjeIzraza.h"

vector<vector<int>> brojevi;
vector<int> red;
int duzina_niza = 0;

//sluzi za ucitavanje txt dadoteke
//iskorisceno ucitavanje za vezbi gde su se ucili vectors i list
//tip je void i in je putanja fajla iz kog ce se ucitavati podaci
void loadBrojevi(ifstream& in)
{
	while (!in.eof())
	{
		int broj = 0;
		string data;
		// @TODO: read id, name and surname from input file stream
		getline(in, data);
		string tmp = "";
		for (char c : data) {
			if (c == ' ') {
				broj = stoi(tmp);
				red.push_back(broj);
				tmp = "";
			}
			else if (c == '\t') {
				broj = stoi(tmp);
				red.push_back(broj);
				tmp = "";
				brojevi.push_back(red);
				duzina_niza = red.size();
				red.clear();
			}
			else {
				tmp += c;
			}
		}
	}
}

//sluzilo za proveru je l dobro ucitan file
void printBrojevi()
{	
	cout << brojevi.size() << endl;
	cout << red.size() << endl;
	for (int i = 0; i < brojevi.size(); i++) {
		for (int j = 0; j < duzina_niza; j++) {
			cout << brojevi[i][j] << " ";
		}
		cout << endl;
	}
}


int main(int argc, char** argv) {

	cout << "Ucitala se dadoteka UlaznaDadoteka.txt" << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "ERROR: wrong input file name!";
		//ovo sam stavio da mi se ne bi zatvorio program
		string abc;
		cin >> abc;
		exit(-1);
	}

	//ucitavanje brojeva
	loadBrojevi(in);

	//broj runde sluzi zbog upisivanja u Rezultati.txt
	//u ispis_ponudjenih se nalaze brojevi u datoj rundi dati i koji se trazi (trocifren broj)
	int broj_runde = 0;
	vector<int> ispis_ponudjenih;
	int poeni_A = 0, poeni_B = 0;
	while (broj_runde != brojevi.size()) {

		ispis_ponudjenih = brojevi[broj_runde];
		vector<int>::iterator ispisIt;
		cout << "Takmicar A: poeni "<<poeni_A << endl;
		cout << "Takmicar B: poeni " << poeni_B << endl;

		cout << "NOVA RUNDA" << endl;
		cout << "Trazeni broj je :" << ispis_ponudjenih[ispis_ponudjenih.size() - 1]<<endl;
		cout << "Ponudjeni brojevi su" << endl;
		//ispis ponudjenih, samo iteriranje kroz vektor
		for (ispisIt = ispis_ponudjenih.begin();ispisIt != ispis_ponudjenih.end(); ispisIt++)
		{
			//stavljeno da ne bi zadnji ispisvao kao ponudjen (koji je trazen)
			if (*ispisIt != ispis_ponudjenih[ispis_ponudjenih.size() - 1])
				cout << *ispisIt << " ";
		}

		cout << endl;
		double vrIzraz_A = 0;
		double vrIzraz_B = 0;
		double razlika_A = 0;
		double razlika_B = 0;

		string pobednik = "";
		if (broj_runde % 2 == 0) {
			cout << "Na potezu je igrac A"<<endl;
			cout << "Unesite Vase resenje (sa ; na kraju)" << endl;
			//pozivanje funkcije calculate iz Kalkulator.cpp
			vrIzraz_A = calculate();
			cout << "Dobili ste vrednost ";
			cout << vrIzraz_A << endl;

			vector<double> korbrojevi = korisceniBrojevi();
			//ovde dodati proveru
			//ovaj vektor sluzi da npr ako imam jednu 25 a neko 2 unese da se proveri je l se vise puta iskoristilo
			vector<bool> iskoriceno;
			for (int i = 0; i < ispis_ponudjenih.size() - 1; i++)
				iskoriceno.push_back(false);
			
			vector<double>::iterator korbrojeviIt;

			brisanjeBrojevi();

			//ako je korisnik dobio tacan rezultat, tj razlika izmedju negovog i trazenog 0, dobija automatski poen
			//a ako nije onda se pamti za kolko je omasio i pogadja drugi takmicar
			if (ispis_ponudjenih[ispis_ponudjenih.size() - 1] - vrIzraz_A == 0){
				cout << "Takmicar A je pogodio tacan broj i dobija poen za pogodjenu rundu" << endl;
				pobednik = "Takmicar A";
				poeni_A++;
			}
			else {
				razlika_A = abs(double(ispis_ponudjenih[ispis_ponudjenih.size() - 1]) - vrIzraz_A);
				cout << "Takmicar A je omasio za " + to_string(llround(razlika_A)) << endl;
				cout << "Na potezu je igrac B" << endl;
				cout << "Unesite Vase resenje" << endl;
				//vec iskomentarisano na liniji 111 (mozda neko pomeranje se desi +-5 linija)
				vrIzraz_B = calculate();
				cout << "Dobili ste vrednost ";
				cout << vrIzraz_B << endl;
				vector<double> korbrojevi = korisceniBrojevi();
				brisanjeBrojevi();

				if (ispis_ponudjenih[ispis_ponudjenih.size() - 1] - vrIzraz_B == 0) {
					cout << "Takmicar B je pogodio tacan broj i dobija poen za pogodjenu rundu" << endl;
					pobednik = "Takmicar B";
					poeni_B++;
				}
				//u slucaju da je i takmicar B pogresio onda se gleda ko je manje pogresio
				//obicni ifovi
				else {
					razlika_B = abs(double(ispis_ponudjenih[ispis_ponudjenih.size() - 1]) - vrIzraz_B);
					cout << "Takmicar B je omasio za " + to_string(llround(razlika_B)) << endl;
					if (razlika_A < razlika_B) {
						cout << "Poene dobija takmicar A jer je manje omasio" << endl;
						pobednik = "Takmicar A";
						poeni_A++;
					}
					else if (razlika_A > razlika_B) {
						cout << "Poene dobija takmicar B jer je manje omasio" << endl;
						pobednik = "Takmicar B";
						poeni_B++;
					}
					else {
						cout << "Nijedan takmicar ne dobija poene" << endl;
					}
				}
			}
			//povecavamo rundu
			broj_runde++;

			//sluzi da se doda in da bi mogla da se pozove f-ja ucitavanje_file
			ifstream in("UlaznaDadoteka.txt");
			if (!in)
			{
				cerr << "ERROR: wrong input file name!";
				exit(-1);
			}

			//iskomentarisano u RacunanjeIzraza.h i RacunanjeIzraza.cpp
			cout << "Resenje je: "<<endl;
			ucitavanje_file<int>(in);
			read_ucitaj<int>();
			solve<int>();
		}
		//sve isto ima gore, samo primenjeno za takmicara B
		//ne mora se gledati do 240 linije
		else {
			cout << "Na potezu je igrac B"<<endl;
			cout << "Unesite Vase resenje" << endl;
			vrIzraz_B = calculate();
			cout << "Dobili ste vrednost ";
			cout << vrIzraz_B << endl;
			if (ispis_ponudjenih[ispis_ponudjenih.size() - 1] - vrIzraz_B == 0) {
				cout << "Takmicar B je pogodio tacan broj i dobija poen za pogodjenu rundu" << endl;
				pobednik = "Takmicar B";
				poeni_B++;
			}
			else {
				razlika_B = abs(double(ispis_ponudjenih[ispis_ponudjenih.size() - 1]) - vrIzraz_B);
				cout << "Takmicar B je omasio za " + to_string(llround(razlika_B)) << endl;
				cout << "Na potezu je igrac A" << endl;
				vrIzraz_A = calculate();
				cout << "Dobili ste vrednost ";
				cout << vrIzraz_A << endl;
				if (ispis_ponudjenih[ispis_ponudjenih.size() - 1] - vrIzraz_A == 0) {
					cout << "Takmicar A je pogodio tacan broj i dobija poen za pogodjenu rundu" << endl;
					pobednik = "Takmicar A";
					poeni_A++;
				}
				else {
					razlika_A = abs(double(ispis_ponudjenih[ispis_ponudjenih.size() - 1]) - vrIzraz_A);
					cout << "Takmicar A je omasio za " + to_string(llround(razlika_A)) << endl;
					if (razlika_A < razlika_B) {
						cout << "Poene dobija takmicar A jer je manje omasio" << endl;
						pobednik = "Takmicar A";
						poeni_A++;
					}
					else if (razlika_A > razlika_B) {
						cout << "Poene dobija takmicar B jer je manje omasio" << endl;
						pobednik = "Takmicar B";
						poeni_B++;
					}
					else {
						cout << "Nijedan takmicar ne dobija poene" << endl;
					}
				}
			}

			broj_runde++;
			cout << "Resenje je: " << endl;
			ucitavanje_file<int>(in);
			read_ucitaj<int>();
			solve<int>();
		}

		//na pocetku prazan string pa ce se na njega nalepljivati ostali stringovi tako da bi moglo da se upise
		//u Rezulati.txt
		string finalni_string = "";

		//broj runde
		finalni_string += "broj runde: ";
		finalni_string += to_string(broj_runde);
		//brojevi ponudjeni i trazeni
		finalni_string += ", brojevi: ";
		for (ispisIt = ispis_ponudjenih.begin(); ispisIt != ispis_ponudjenih.end(); ispisIt++)
		{
			finalni_string = finalni_string + to_string(*ispisIt) + " ";
		}

		//igrac A koji je rez dobio i kolko odstupa
		finalni_string += ", igrac A je dobio rezultat: ";
		finalni_string += to_string(llround(vrIzraz_A));
		finalni_string += ", a resenje odstupa za: ";
		finalni_string += to_string(llround(razlika_A));

		//igrac B koji je rez dobio i kolko odstupa
		finalni_string += ", igrac B je dobio rezultat: ";
		finalni_string += to_string(llround(vrIzraz_B));
		finalni_string += ", a resenje odstupa za: ";
		finalni_string += to_string(llround(razlika_B));

		//pobednik runde
		finalni_string += ", pobednik runde je: ";
		finalni_string += pobednik;

		//resenje kompjutera
		finalni_string += ", resenje kompjutera je: ";
		finalni_string += izraz_resenje();

		//da bi preslo u novi red
		finalni_string += "\n";

		//ovo sluzi za apendovanje tj citanje starog file i na to se dodaje nova linija
		//upisuje se u file nakon svake runde
		ofstream foutput;
		ifstream finput;
		finput.open(argv[2]);
		foutput.open(argv[2], ios::app);
		
		if (finput.is_open())
			foutput << finalni_string;

		cout << "\nData has been appended to file\n";

		finput.close();
		foutput.close();
	}

	//klasino poredjenje i ispisivanje koji je takmicar pobedio
	string kraj_dadoteke_str = "";
	cout << "KRAJ IGRE"<<endl;
	if (poeni_A > poeni_B) {
		cout << "Pobedio je takmicar A sa rezulatom "<<poeni_A<<":"<<poeni_B << endl;
		kraj_dadoteke_str = kraj_dadoteke_str + "Pobedio je takmicar A sa rezulatom " + to_string(poeni_A) + ":" + to_string(poeni_B);
	}
	else if (poeni_A < poeni_B) {
		cout << "Pobedio je takmicar B sa rezulatom " << poeni_B << ":" << poeni_A << endl;
		kraj_dadoteke_str = kraj_dadoteke_str + "Pobedio je takmicar B sa rezulatom " + to_string(poeni_B) + ":" + to_string(poeni_A);
	}
	else {
		cout << "Nereseno" << endl;
		kraj_dadoteke_str = kraj_dadoteke_str + "Nereseno je i rezultat je" + to_string(poeni_B) + ":" + to_string(poeni_A);
	}

	//na kraju file se upisuje koji je takmicar pobedio
	ofstream foutput;
	ifstream finput;
	finput.open(argv[2]);
	foutput.open(argv[2], ios::app);

	if (finput.is_open())
		foutput << kraj_dadoteke_str<<endl;

	cout << "\nU fajl se upisao pobednik\n";

	finput.close();
	foutput.close();
	
	//dodato da se ne bi zatvorio prozor
	string aaa;
	cin >> aaa;
	return 0;
}
