#pragma once
class Date
{
private:

	int day;
	int month;
	int year;

public:

	//DEFFAULT CONSTRUCT
	Date();
	Date(int, int, int);

	//SET METHODS
	void setDay(int);
	void setMonth(int);
	void setYear(int);

	//GET METHODS
	int getDay();
	int getMonth();
	int getYear();

	//OTHER METHODS
	bool CheckDate(int, int, int);
	void Display();

};

