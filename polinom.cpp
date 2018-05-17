#include "polinom.h"
#include "ringlist.h"

ostream& operator<<(ostream& ost, const Polinom& p)
{
	cout << p.monoms << endl;
	return ost;
}


Polinom::Polinom(const string &str) {
	
	int len = str.length();
	int i = 0;
	int j = 0;
	string sub;
	sub.resize(35);
	int svertka = 0;
	while (1) {
		svertka = 0;
		Monom tmp;
		if (str[i] == '\0') {
			break;
		}

		if ((str[i] == '+') || (str[i] == '-')) {
			
		

			j = 0;
			while (str[i] != 'x') {


				sub[j] = str[i];
				i++;
				j++; //после цикла i будет на позиции x
			}
			int cff = std::stoi(sub);

			tmp.SetCoeff(cff);

			sub.resize(0);
			sub.resize(35);

			i = i + 2;

			j = 0;
			while (str[i] != 'y') {

				sub[j] = str[i];
				i++;
				j++; //после цикла i будет на позиции y
			}
			svertka = svertka + 400 * std::stoi(sub);

			sub.resize(0);
			sub.resize(35);

			i = i + 2;

			j = 0;
			while (str[i] != 'z') {

				sub[j] = str[i];
				i++;
				j++; //после цикла i будет на позиции z
			}

			svertka = svertka + 20 * std::stoi(sub);

			sub.resize(0);
			sub.resize(35);

			i = i + 2;

			j = 0;
			while (1) {
				if (((str[i] == '\0')||(str[i] == '+') || (str[i] == '-'))) {
					break;
				}
				
				
				sub[j] = str[i];
				i++;
				j++; //после цикла i будет на позиции либо знака либо \0
			}

			svertka = svertka + std::stoi(sub);

			sub.resize(0);
			sub.resize(35);

			tmp.SetIndex(svertka);
			
			monoms.InsertToTail(tmp);
		}


	}

}

Polinom::Polinom(const Polinom &p1) {
	s = p1.s;
	monoms = p1.monoms;
}
string Polinom::returnstr()
{
	return s;
}
Polinom Polinom::operator+(const Polinom &p1) {
	Polinom tmp(p1);
	Polinom Res;
	Link <Monom> *m1, *m2,*m3;
	Monom val;
	monoms.Reset();
	m1 = monoms.GetNext();
	while (!monoms.IsEnded()) {
		val = monoms.GetValue();
		Res.monoms.Insert(val);
		m1 = monoms.GetNext();
	}
	tmp.monoms.Reset();
	m2 = tmp.monoms.GetNext();
	while (!tmp.monoms.IsEnded()) {
		val = tmp.monoms.GetValue();
		Res.monoms.Insert(val);
		m2 = tmp.monoms.GetNext();
	}
	Res.monoms.Reset();
	m3 = Res.monoms.GetNext();
	string ss="";
	while (!Res.monoms.IsEnded()) {
		val = Res.monoms.GetValue();
		int stx = (int)val.abc / 400;
		int sty = (int)(val.abc/ 20 - stx * 20);
		int stz = (int)(val.abc % 20);
		if (val.cf >=0) ss = ss + "+";
		ss = ss+to_string(val.cf) + "x^" + to_string(stx) + "y^" + to_string(sty) + "z^" + to_string(stz);
		m3 = Res.monoms.GetNext();
	}
	Res.s = ss;
	return Res;
}
Polinom Polinom::operator-(const Polinom &p1) {
	Polinom tmp(p1);
	Polinom Res;
	Link <Monom> *m1, *m2,*m3;
	Monom val;
	monoms.Reset();
	m1 = monoms.GetNext();
	while (!monoms.IsEnded()) {
		val = monoms.GetValue();
		Res.monoms.Insert(val);
		m1 = monoms.GetNext();
	}
	tmp.monoms.Reset();
	m2 = tmp.monoms.GetNext();
	while (!tmp.monoms.IsEnded()) {
		val = tmp.monoms.GetValue();
		val.SetCoeff(val.GetCoeff()*(-1));
		Res.monoms.Insert(val);
		m2 = tmp.monoms.GetNext();
	}
	Res.monoms.Reset();
	m3 = Res.monoms.GetNext();
	string ss = "";
	while (!Res.monoms.IsEnded()) {
		val = Res.monoms.GetValue();
		int stx = (int)val.abc / 400;
		int sty = (int)(val.abc / 20 - stx * 20);
		int stz = (int)(val.abc % 20);
		if (val.cf >=0) ss = ss + "+";
		ss = ss + to_string(val.cf) + "x^" + to_string(stx) + "y^" + to_string(sty) + "z^" + to_string(stz);
		m3 = Res.monoms.GetNext();
	}
	Res.s = ss;
	return Res;
}
Polinom Polinom::operator*(const Polinom &p1) {
	Polinom tmp(p1);
	Polinom Res;
	Monom MAX(1000, 99999);
	Link <Monom> *m1, *m2,*m3;
	monoms.Reset();
	m1 = monoms.GetNext();
	tmp.monoms.Reset();
	m2 = tmp.monoms.GetNext();
	while (!monoms.IsEnded()) {
		while (!tmp.monoms.IsEnded()) {
			Monom rm = monoms.GetValue()*tmp.monoms.GetValue();
			if (rm < MAX) {
				Res.monoms.Insert(rm);
			}
			m2 = tmp.monoms.GetNext();
		}
		m1 = monoms.GetNext();
		m2 = tmp.monoms.GetNext();
	}
	Res.monoms.Reset();
	m3 = Res.monoms.GetNext();
	string ss = "";
	while (!Res.monoms.IsEnded()) {
		MAX = Res.monoms.GetValue();
		int stx = (int)MAX.abc / 400;
		int sty = (int)(MAX.abc / 20 - stx * 20);
		int stz = (int)(MAX.abc % 20);
		if (MAX.cf >=0) ss = ss + "+";
		ss = ss + to_string(MAX.cf) + "x^" + to_string(stx) + "y^" + to_string(sty) + "z^" + to_string(stz);
		m3 = Res.monoms.GetNext();
	}
	Res.s = ss;
	return Res;
}
Polinom Polinom::operator*(const double &d) {
	Link<Monom> *tmp;
	monoms.Reset();
	tmp = monoms.GetNext();
	while (!monoms.IsEnded()) {
		tmp->data = tmp->data*d;
		tmp = monoms.GetNext();
	}
	return *this;
}
const Polinom& Polinom::operator=(const Polinom &p1) {
	if (this != &p1) {
		s = p1.s;
		monoms = p1.monoms;
	}
	return *this;
}

double Polinom::xyz(double x, double y, double z)
{
	double total=0;
	Link<Monom> *m;
	this->monoms.Reset();
	Monom val;
	m = this->monoms.GetNext();
	while (!this->monoms.IsEnded())
	{
		val = this->monoms.GetValue();
		int stx = (int)val.abc / 400;
		int sty = (int)(val.abc / 20 - stx * 20);
		int stz = (int)(val.abc % 20);
		total += val.cf*pow(x, stx)*pow(y, sty)*pow(z, stz);
		m = this->monoms.GetNext();
	}
	return total;
}
