#pragma once
#include <iostream>
#include "monom.h"
#include "ringlist.h"

using namespace std;

class Polinom {
	string s;
	RingList<Monom> monoms;
public:
	Polinom() {};
	~Polinom() {};
	Polinom(const string &str); //конструктор, принимающий на вход строку
	Polinom(const Polinom &p1);// конструктор копирования
	string returnstr();
	Polinom operator+(const Polinom &p1);
	Polinom operator*(const Polinom &p1);
	Polinom operator-(const Polinom &p1);
	Polinom operator*(const double &d);
	const Polinom& operator=(const Polinom &p1);
	friend ostream& operator<<(ostream& ost, const Polinom& p);
	double xyz(double x, double y, double z);
};