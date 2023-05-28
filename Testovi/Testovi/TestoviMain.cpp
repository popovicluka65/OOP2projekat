//Luka Popovic SV4/2021
//testiranje
#include "RacunanjeIzraza.h"

vector<vector<int>> brojevi;
vector<int> red;
int duzina_niza = 0;

void loadTest(ifstream& in)
{
	while (!in.eof())
	{
		int broj = 0;
		string data;
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

int main(int argc, char** argv) {
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "ERROR: wrong input file name!";
		exit(-1);
	}

	loadTest(in);

	int broj_runde = 0;
	vector<int> ispis_ponudjenih;

	//testiranje preko ulazne dadoteke
	while (broj_runde != brojevi.size()) {

		ispis_ponudjenih = brojevi[broj_runde];
		vector<int>::iterator ispisIt;
		cout << "Trazeni broj je :" << ispis_ponudjenih[ispis_ponudjenih.size() - 1] << endl;
		cout << "Ponudjeni brojevi su" << endl;
		for (ispisIt = ispis_ponudjenih.begin(); ispisIt != ispis_ponudjenih.end(); ispisIt++)
		{
			//stavljeno da ne bi zadnji ispisvao kao ponudjen (koji je trazen)
			if (*ispisIt != ispis_ponudjenih[ispis_ponudjenih.size() - 1])
				cout << *ispisIt << " ";
		}
		cout << endl;

		ifstream in("testovi.txt");
		if (!in)
		{
			cerr << "ERROR: wrong input file name!";
			exit(-1);
		}

		cout << "Resenje je: " << endl;
		ucitavanje_file<int>(in);
		read_ucitaj<int>();
		solve<int>();
		string resenje = izraz_resenje();

		broj_runde++;
	}
	
	cout << "Kraj prvog tesitranja\n\n\n\n\n\n\n\n";
	cout << "Drugo testiranje"<<endl;
	cout << "Unesite broj koliko zelite da testirate" << endl;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double izraz = calculate();
		cout << "Resenje je: "<<izraz << endl;
	}
	
	string aaa;
	cin >> aaa;
	return 0;
}
