#pragma once
#include <string>
#include <string.h>
using namespace std;

class Subject
{
private:

	string IDS;
	string Name;
	string Class_Teacher;
	int Units;
	int Limit;
	Subject* next;

public:

	//SET METHODS
	void setIDS(string IDS);
	void setName(string);
	void setUnits(int);
	void setLimit(int);
	void setClassTeacher(string);
	void setNextSubject(Subject*);

	//GET METHODS
	string getIDS();
	string getName();
	int getUnit();
	int getLimit();
	string getClassTeacher();
	Subject* getNextSubject();

};