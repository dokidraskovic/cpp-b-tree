#ifndef _stablo_h_
#define _stablo_h_
#include<iostream>
#include<string>
#include<queue>
#include<stack>

using namespace std;

class Stablo {
	struct Cvor {
		string* kljuc;
		Cvor** pok;
		Cvor* otac;
		int br = 0;
		Cvor() = default;
		Cvor(int m)
		{
			kljuc = nullptr;
			pok = nullptr;
		}
	};
	Cvor* koren = nullptr;
	Cvor* nebitan = nullptr;
	int redS;
	void brisi();
	void sortiraj(Cvor*& p, int i);
	Cvor* alociraj();
	int indS(Cvor* o,Cvor* p);
	void prelivanje(Cvor* o, Cvor* s1, Cvor* s2,string s);
	void prelamanje(Cvor* o, Cvor* s1,Cvor* s2,string& s);
public:
	Stablo(int m)
	{
		koren = new Cvor(m);
		koren->otac = nullptr;
		redS = m;
	}
	~Stablo() { brisi(); }
	Cvor*& uzmiN()  { return nebitan; }
	bool nadji(const string& s, Cvor*& p, int& i);
	bool dodaj(string& s);
	friend ostream& operator<<(ostream& os, const Stablo& s);
	int obrada(string s);
};

#endif