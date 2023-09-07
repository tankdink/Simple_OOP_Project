#include "Date.h"

#include <iostream>
using namespace std;

//DEFFAULT CONSTRUCTORS
Date::Date()
{
	day = month = year = 0;
}
Date::Date(int day, int month, int year)
{
	bool k = CheckDate(day, month, year);
	do
	{
		if (k == false)
		{
			cout << "Invalid Date!\nPlease try again!";
			int day_, month_, year_;
			cout << "\nNew Day: ";
			cin >> day_;
			cout << "New Month: ";
			cin >> month_;
			cout << "New Year: ";
			cin >> year_;
			day = day_;
			month = month_;
			year = year_;
			k = CheckDate(day, month, year);
		}
		else
		{
			break;
		}
	} while (k == false);
	this->day = day;
	this->month = month;
	this->year = year;
}

//SET METHODS
void Date::setDay(int day)
{
	this->day = day;
}
int Date::getDay()
{
	return day;
}
void Date::setMonth(int month)
{
	this->month = month;
}
int Date::getMonth()
{
	return month;
}
void Date::setYear(int year)
{
	this->year = year;
}
int Date::getYear()
{
	return year;
}

//CHECK METHOD
bool Date::CheckDate(int day, int month, int year)
{
	if (day > 31 || day <= 0 || month <= 0 || month > 12 || year < 1900 || year > 2022) return 0;
	switch (month)
	{
	case 2:
	{
		if (day > 29) return 0;
		if (year % 400 != 0 && day > 28) return 0;
	}
	case 4: if (day > 30) return 0;
	case 6: if (day > 30) return 0;
	case 9: if (day > 30) return 0;
	case 11: if (day > 30) return 0;
	default:
		break;
	}
	return 1;
}

//DISPLAY
void Date::Display()
{
	if (month >= 1 && month <= 9)
	{
		if (day >= 1 && day <= 9)
		{
			cout << "0" << day << "/" << "0" << month << "/" << year;
			return;
		}
		else
		{
			cout << day << "/" << "0" << month << "/" << year;
			return;
		}
	}
	if (day >= 1 && day <= 9)
	{
		if (month >= 1 && month <= 9)
		{
			cout << "0" << day << "/" << "0" << month << "/" << year;
			return;
		}
		else
		{
			cout << "0" << day << "/" << month << "/" << year;
			return;
		}
	}
	if (day > 9 && month > 9)
	{
		cout << day << "/" << month << "/" << year;
		return;
	}
}