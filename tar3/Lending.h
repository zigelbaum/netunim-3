
#pragma once
#include <iostream>
#include<string>
using namespace std;
class Lending
{
	int ID;
	string name;
	string date;
	int code;
public:
	Lending();
	~Lending();
	bool operator==(const Lending & other)const;
	bool operator!=(const Lending & other)const;
	bool operator >(Lending &other);
	bool operator >=(Lending& other);
	bool operator <(Lending &other);
	bool operator <=(Lending &other);
	void set_date(string Date) { date = Date; };

	friend istream& operator>>(istream& is, Lending& l)
	{
		cout << "enter id name date item ";
		is >> l.ID >> l.name >> l.date >> l.code;
		return is;
	}
	friend ostream& operator<<(ostream& os, Lending& l)
	{
		os << endl << "Lending details: id: " << l.ID << " name: " << l.name << " date: " << l.date << " item: " << l.code << endl;
		return os;
	}

};