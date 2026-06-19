#include "stablo.h"

void Stablo::brisi()
{
	queue<Cvor*> red;
	if (this->koren)
	red.push(this->koren);
	while (!red.empty())
	{
		Cvor* pom = red.front();
		red.pop();
		if(pom->pok)
		for (int i = 0; i < redS; i++)
			if (pom->pok[i]) red.push(pom->pok[i]);
		delete[] pom->kljuc;
		delete[] pom->pok;
		delete pom;
	}
	this->koren = nullptr;
}

void Stablo::sortiraj(Cvor*& p, int i)
{
	p->kljuc[i + 1] = p->kljuc[i];
	for (int j = i; j < p->br; j++)
		p->kljuc[j + 1] = p->kljuc[j];
}

Stablo::Cvor* Stablo::alociraj()
{
	Cvor* pom = new Cvor();
	pom->kljuc = new string[redS + 1];
	pom->pok = new Cvor*[redS];
	for (int i = 0; i < redS; i++)
		pom->pok[i] = nullptr;
	pom->kljuc[0] = "aaaaa";
	pom->kljuc[redS] = "zzzzz";
	return pom;
}

int Stablo::indS(Cvor * o, Cvor* p)
{
	for (int i = 0; i < o->br; i++)
		if (o->pok[i] == p) return i;
	return -1;
}

void Stablo::prelivanje(Cvor * o, Cvor * s1, Cvor * s2,string s)
{
	int n = 1 + s1->br + s2->br;
	string* pomS =new  string[n + 1];
	int sr = n / 2;
	int ind = indS(o, s1) + 1;
	int i;
	for (i = 1; i < s1->br + 1; i++)
		if (s1->kljuc[i].compare(s) < 0)
			pomS[i - 1] = s1->kljuc[i];
		else
		{
			pomS[i - 1] = s;
			pomS[i] = s1->kljuc[i];
		}
	pomS[i++] = o->kljuc[ind];
	for (int j = 1; j < s2->br + 1; j++)
		pomS[i + j - 1] = s2->kljuc[j];
	o->kljuc[ind] = pomS[sr];
	s1->br = 0;
	s2->br = 0;
	for (int i = 0; i < sr; i++)
	{
		s1->kljuc[i + 1] = pomS[i];
		s1->br++;
	}
	for (int i = sr + 1; i < n + 1; i++)
	{
		s2->kljuc[i - sr] = pomS[i];
		s2->br++;
	}
}

void Stablo::prelamanje(Cvor * o, Cvor * s1, Cvor* s2, string& s)
{
	int n = 2 + s1->br + s2->br;
	string* pomS = new string[n];
	int br = 0;
	int i1 = 0;
	int i2 = 0;
	int ind = indS(o, s1) + 1;
	bool stavljen = false;
	while (br < n)
	{
		if (i1 < s1->br)
			if (s1->kljuc[i1 + 1].compare(s) < 0 || stavljen)
				pomS[br] = s1->kljuc[i1 + 1];
			else
			{
				pomS[br] = s;
				i1--;
				stavljen = true;
			}
		else
		{
			if (o->kljuc[ind].compare(s) < 0 || stavljen && i2 == 0)
			{
				pomS[br] = o->kljuc[ind];
				br++;
			}
			if (s2->kljuc[i2 + 1].compare(s) < 0 || stavljen)
			{
				pomS[br] = s2->kljuc[i2 + 1];
				i2++;
			}
			else
			{
				pomS[br] = s;
				i2--;
				stavljen = true;
			}
		}
		i1++;
		br++;
	}
	int g1 = (2 * redS - 2) / 3;
	int g2 = (2 * redS - 1) / 3;
	int g3 = 2 * redS / 3;
	o->kljuc[ind] = pomS[g1];
	if (!o->kljuc[ind + 1].compare("zzzzz"))
	{
		s = pomS[g1 + g2 + 1];
		if (o == koren) o->br = 2 * (2 * redS - 2) / 3 + 1;
		else o->br = redS;
	}
	else
	o->kljuc[ind + 1] = pomS[g1 + g2 + 1];
	int i;
	s1->br = 0;
	s2->br = 0;
	delete[] s1->kljuc;
	delete[] s2->kljuc;
	s1->kljuc = new string[redS + 1];
	s1->kljuc[0] = "aaaaa";
	s1->kljuc[redS] = "zzzzz";
	s2->kljuc = new string[redS + 1];
	s2->kljuc[0] = "aaaaa";
	s2->kljuc[redS] = "zzzzz";
	for (i = 0; i < g1; i++)
	{
		s1->kljuc[i + 1] = pomS[i];
		s1->br++;
	}
	i++;
	for (i; i < g2 + g1 + 1; i++)
	{
		s2->kljuc[i - g1] = pomS[i];
		s2->br++;
	}
	i++;
	Cvor* pom = alociraj();
	pom->kljuc[0] = "aaaaa";
	pom->kljuc[redS] = "zzzzz";
	pom->otac = o;
	o->pok[ind + 1] = pom;
	for (i; i < n; i++)
	{
		pom->kljuc[i - g1 - g2 - 1] = pomS[i];
		pom->br++;
	}
}

bool Stablo::nadji(const string & s, Cvor*& p, int& i)
{
	int i1 = 0;
	Cvor* pom = this->koren;
	p = this->koren;
	while (pom != nullptr)
	{
		i1 = 0;
		int i2 = pom->br - 1;
		for (int j = 1; j < pom->br + 1; j++)
			if (!pom->kljuc[j].compare(s))
				return true;
		while (pom->kljuc[i1].compare(s) < 0 && i1<pom->br|| pom->kljuc[i2].compare(s) > 0)
		{
			if (pom->kljuc[i1].compare(s) < 0 )
				i1++;
			if (pom->kljuc[i2].compare(s) > 0)
				i2--;
		}
		i = i1;
		p = pom;
		pom = pom->pok[i2];
	}
	return false;
}

bool Stablo::dodaj(string & s)
{
	Cvor* pom = nullptr;
	int i = -1;
	bool f = false;
	if (!this->koren->pok)
	{
		Cvor* pom = new Cvor();
		pom->kljuc = new string[2 * (2 * redS - 2) / 3 + 2];
		pom->pok = new Cvor*[2 * (2 * redS - 2) / 3 + 1];
		for (int i = 0; i < 2 * (2 * redS - 2) / 3 + 1; i++)
			pom->pok[i] = nullptr;
		pom->kljuc[0] = "aaaaa";
		pom->kljuc[2 * (2 * redS - 2) / 3 + 1] = "zzzzz";
		this->koren = pom;
		this->koren->kljuc[1] = s;
		this->koren->br++;
		return true;
	}
	else f = this->nadji(s, pom, i);
	if (f) return false;
	else
	{
		if (pom == this->koren && pom->br < 2 * (2 * redS - 2) / 3)
		{
			this->sortiraj(pom, i);
			pom->kljuc[i] = s;
			pom->br++;
		}
		else if (pom == this->koren)
		{
			int faktor = 2 * (2 * redS - 2) / 3 + 1;
			string* pom1 = new string[faktor];
			int i;
			for (i = 1; i < pom->br + 1; i++)
			{
				if (pom->kljuc[i].compare(s) < 0)
					pom1[i - 1] = pom->kljuc[i];
				else
				{
					pom1[i - 1] = s;
					break;
				}
			}
			if (i == pom->br + 1)
				pom1[i - 1] = s;
			else
				for (i; i < pom->br + 1; i++)
					pom1[i] = pom->kljuc[i];
			int g1 = faktor / 2;
			int g2 = faktor / 2;
			Cvor* p1 = alociraj();
			Cvor* p2 = alociraj();
			p2->otac = pom;
			p1->otac = pom;
			pom->pok[0] = p1;
			pom->pok[1] = p2;
			for (int i = 0; i < g1; i++)
			{
				p1->kljuc[i + 1] = pom1[i];
				p1->br++;
			}
			for (int i = 0; i < g2; i++)
			{
				p2->kljuc[i + 1] = pom1[g1 + i + 1];
				p2->br++;
			}
			delete[] pom->kljuc;
			pom->kljuc = new string[faktor + 2];
			pom->kljuc[0] = "aaaaa";
			pom->kljuc[faktor + 1] = "zzzzz";
			pom->kljuc[1] = pom1[g1];
		}
		else if (pom->br < redS - 1)
		{
			sortiraj(pom, i);
			pom->kljuc[i] = s;
			pom->br++;
		}
		else
		{
			Cvor* otac = pom->otac;
			int i = indS(otac, pom);
			if (((otac == koren) ? i < redS + 1 : i < redS) && otac->pok[i + 1]->br < redS - 1 && otac->pok[i + 1]->br != 0)
				prelivanje(otac, pom, otac->pok[i + 1], s);
			else if (i > 0 && otac->pok[i - 1]->br < redS && otac->pok[i - 1]->br != 0)
				prelivanje(otac, otac->pok[i - 1], pom, s);
			else
			{
				prelamanje(otac, pom, otac->pok[i + 1], s);
				while (otac->br == redS || otac->br == 2 * (2 * redS - 2) / 3 + 1)
				{
					pom = otac;
					otac = otac->otac;
					if (pom == this->koren)
					{
						int faktor = 2 * (2 * redS - 2) / 3 + 1;
						string* pom1 = new string[f];
						for (int i = 0; i < pom->br; i++)
							pom1[i] = pom->kljuc[i];
						pom1[pom->br] = s;
						int g1 = faktor / 2;
						int g2 = faktor / 2 - 1;
						Cvor* p1 = alociraj();
						Cvor* p2 = alociraj();
						p2->otac = pom;
						p1->otac = pom;
						for (int i = 0; i < g1; i++)
							p1->kljuc[i + 1] = pom1[i];
						for (int i = 0; i < g2; i++)
							p2->kljuc[i + 1] = pom1[f + i + 1];
						delete[] pom->kljuc;
						pom->kljuc = new string[f + 2];
						pom->kljuc[0] = "aaaaa";
						pom->kljuc[f + 1] = "zzzzz";
						pom->kljuc[1] = pom1[f / 2];
						break;
					}
					else
						prelamanje(otac, pom, otac->pok[i + 1], s);
				}
			}
		}
	}
}

int Stablo::obrada(string s)
{
	queue<Cvor*> red;
	Cvor* sled = koren;
	string* pom = new string[100];
	int g;
	int br = 0;
	if (sled == koren) g = 2 * (2 * redS - 2) / 3 + 1;
	else g = redS;
	red.push(sled);
	while (!red.empty())
	{
		sled = red.front();
		red.pop();
		if (sled == koren) g = 2 * (2 * redS - 2) / 3 + 1;
		else g = redS;
		for (int i = 1; i < sled->br + 1; i++)
			pom[br++] = sled->kljuc[i];
		for (int i = 0; i < g; i++)
			if (sled->pok[i]) red.push(sled->pok[i]);
	}
	for (int i = 0; i < br - 1; i++)
		for (int j = i + 1; j < br; j++)
			if (pom[i].compare(pom[j]) > 0)
			{
				string p = pom[i];
				pom[i] = pom[j];
				pom[j] = p;
			}
	int i = 0;
	while (pom[i].compare(s) < 0 && i < br)
		i++;
	delete[] pom;
	return i;
}

ostream & operator<<(ostream & os, const Stablo & s)
{
	queue<Stablo::Cvor*> red;
	if (s.koren)
		red.push(s.koren);
	int sirina = 0;
	int g;
	int max = sirina;
	int t, sl;
	t = 1;
	sl = 0;
	while (!red.empty())
	{
		Stablo::Cvor* pom = red.front();
		red.pop();
		if (pom == s.koren) g = 2 * (2 * s.redS - 2) / 3 + 1;
		else g = s.redS;
		for (int i = 0; i < g; i++)
			if (pom->pok[i])
			{
				sl++;
				red.push(pom->pok[i]);
				sirina++;
			}
		t--;
		if (t == 0)
		{
			if (sirina > max) max = sirina;
			t = sl;
			sl = 0;
		}
	}
	Stablo::Cvor* last = s.koren;
	sirina = sirina / 2;
	red.push(s.koren);
	int stariN = 0;
	int nivo = 0;
	t = 1;
	int blanko;
	int koef = 20;
	sl = 0;
	bool prvi = true;
	int a = 0;
	while (!red.empty())
	{
		string bl = "";
		if (nivo > stariN)
		{
			cout << endl << endl;
			prvi = true;
			sirina = sirina / 2;
		}
		bl = "";
		Stablo::Cvor* pom = red.front();
		red.pop();
		t--;
		if (pom != nullptr)
		{
			if (prvi == true)
			{
				if (sirina != 0)
					blanko = sirina * koef / 2;
				else
					blanko = 0;
			}
			else
			{
				if (sirina != 0)
				{
					if (last != nullptr)
						if (last->otac != pom->otac)
							blanko = sirina * koef / 2;
						else
							blanko = sirina * koef;
				}
				else if (last != nullptr)
					if (last->otac != pom->otac)
						blanko = koef / 4;
					else blanko = koef / 2;
			}
			if (pom == s.koren) a = 5;
			else a = 0;
			for (int i = 0; i < blanko + a; i++)
				bl += " ";
			prvi = false;
			os << bl;
			for (int i = 1; i < pom->br + 1; i++)
				os << pom->kljuc[i]<<"|";
		}
		else
		{
			if (prvi == true)
			{
				if (sirina != 0)
					blanko = sirina * koef;
				else blanko = koef / 2 + koef / 4;
			}
			else
			{
				if (sirina != 0)
					blanko = sirina * koef / 2;
				else blanko = koef / 2;
			}
			for (int i = 0; i < blanko; i++)
				bl += " ";
			os << bl;
		}
		stariN = nivo;
		last = pom;
		if (pom == s.koren) g = 2 * (2 * s.redS - 2) / 3 + 1;
		else g = s.redS;
		for (int i = 0; i < g; i++)
			if (pom->pok[i] != nullptr && sirina != 0)
			{
				red.push(pom->pok[i]);
				sl++;
			}
		if (t == 0)
		{
			t = sl;
			sl = 0;
			nivo++;
		}
	}
	os << endl;
	return os;
}
