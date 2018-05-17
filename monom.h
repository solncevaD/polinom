#pragma once
#include <string>
#include <cstdlib>
#include  <cctype>
#include <iostream>

using namespace std;

class Monom {
public:
	double cf; //����������� 
	unsigned int abc; // ���������� �������

	Monom();// ����������� �� ���������
	Monom(double d, unsigned int st);// ����������� �����������
	void SetCoeff(double cval) { cf = cval; }// ������������� �����������
	double GetCoeff(void) { return cf; }// ���������� �����������
	void SetIndex(int ival) { abc = ival; }// ������������� ������
	unsigned int GetIndex(void) { return abc; }// ���������� ������
	Monom& operator=(const Monom &m);
	Monom& operator+(const Monom &m);
	Monom& operator*(const double &d);
	Monom& operator*(const Monom &m);
	bool operator==(const Monom &m) const;
	bool operator!=(const Monom &m) const;
	bool operator<(const Monom &m) const;
	string getMonom()
	{
		int stx = (int)this->abc / 400;
		int sty = (int)(this->abc / 20 - stx * 20);
		int stz = (int)(this->abc % 20);
		string s = to_string(this->abc)+"x^"+to_string(stx)+"y^" + to_string(sty)+"z^" + to_string(stz);
		return s;
	}
	friend ostream& operator<<(ostream& os, const Monom& m)
	{
		Monom Mon;
		Mon = m;
		int stx = (int)Mon.abc / 400;
		int sty = (int)(Mon.abc / 20 - stx * 20);
		int stz = (int)(Mon.abc % 20);
		cout << Mon.cf << "x^" << stx << "y^" << sty << "z^" << stz;
		return os;
	};
};