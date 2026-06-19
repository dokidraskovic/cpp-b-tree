#include "stablo.h"
#include <fstream>

int main()
{
	bool kraj = false;
	Stablo* s = nullptr;
	while (!kraj)
	{
		ifstream ulaz;
		cout << "Izaberite opciju:" << endl;
		cout << "1.Stvaranje stabla sa korenom" << endl;
		cout << "2.Trazenje kljuca u stablu" << endl;
		cout << "3.Ispisivanje stabla" << endl;
		cout << "4.Dodavanje kljuca u stablo" << endl;
		cout << "5.Brisanje kljuca iz stabla" << endl;
		cout << "6.Koliko ima kljuceva leksikografski manjih od zadatkog kljuca" << endl;
		cout << "0.Prekid programa" << endl;
		int opcija;
		cin >> opcija;
		switch (opcija)
		{
		case 1:
		{
			int n;
			string naziv;
			cout << "Unesite red stabla i naziv datoteke" << endl;
			cin >> n >> naziv;
			if (n < 3 || n>10)
			{
				cout << "Neispravni podaci" << endl;
				continue;
			}
			s=new Stablo(n);
			ulaz.open(naziv);
			char a;
			a = ulaz.get();
			if (a == '\n')
				a = ulaz.get();
			while (!ulaz.eof() && a != '\n')
			{
				string pom;
				pom += a;
				string st;
				getline(ulaz, st);
				st.insert(0, pom);
				s->dodaj(st);
				a = ulaz.get();
			}
			break;
		}
		case 2:
		{
			cout << "Unesite naziv kljuca" << endl;
			string pom;
			int a = -1;
			cin >> pom;
			bool r = s->nadji(pom,s->uzmiN(),a);
			if (r) cout << "Kljuc je nadjen" << endl;
			else cout << "Kljuc nije pronadjen" << endl;
			break;
		}
		case 3:
		{
			cout << *s;
			break;
		}
		case 4:
		{
			string naziv;
			cin >> naziv;
			s->dodaj(naziv);
			break;
		}
		case 5:
		{

		}
		case 6:
		{
			string naziv;
			cin >> naziv;
			int rez = s->obrada(naziv);
			cout << "Postoji " << rez << " takvih kljuceva" << endl;
			break;
		}
		case 0:
			kraj = true;
			break;
		}
	}
}