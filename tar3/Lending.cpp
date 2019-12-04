#include "Lending.h"
Lending::Lending()
{}
Lending::~Lending()
{}
bool Lending::operator==(const Lending & other)const//operator ==
{
	if (this->ID != other.ID)
		return false;
	if (this->name != other.name)
		return false;
	if (this->date != other.date)
		return false;
	if (this->code != other.code)
		return false;
	return true;

}

bool Lending::operator !=(const Lending & other)const//operator !=
{
	if (!(this->operator==(other)))
		return true;
	return false;
}

bool Lending:: operator >(Lending &other)//operator >
{
	if (this->date != other.date)
	{
		int check = this->date.compare(6, 4, other.date, 6, 4);//could be we nees to change the 4 to 2
		if (check < 0)//compare year
			return true;
		if (check > 0)
			return false;
		else
		{
			check = this->date.compare(3, 2, other.date, 3, 2);//compare month
			if (check < 0)//compare year
				return true;
			if (check > 0)
				return false;
			else
			{
				check = this->date.compare(0, 2, other.date, 0, 2);//compare day
				if (check < 0)//compare year
					return true;
				if (check > 0)
					return false;
			}
		}
	}
	else//if dates are equal check by other values
	{
		if (this->code > other.code)//compares code
			return true;
		if (this->code < other.code)
			return false;
		else
		{
			if (this->ID > other.ID)//compares id
				return true;
			return false;
		}

	}

}

bool Lending:: operator >=(Lending& other)//operator >=
{
	if (this->operator>(other))
		return true;
	if (this->date == other.date)
		if (this->code == other.code)
			if (this->ID == other.ID)
				return true;
	return false;

}

bool Lending:: operator <(Lending &other) //operator<
{
	if (!(this->operator>=(other)))
		return true;
	return false;
}

bool Lending:: operator <=(Lending &other)//operator <=
{
	if (this->operator<(other))
		return true;
	if (this->date == other.date)
		if (this->code == other.code)
			if (this->ID == other.ID)
				return true;
	return false;
}