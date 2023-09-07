#include "Subject.h"

#include <string>
#include <string.h>
using namespace std;

//SET METHODS
void Subject::setIDS(string ID)
{
	this->IDS = ID;
}
void Subject::setName(string name)
{
	this->Name = name;
}
void Subject::setUnits(int units)
{
	this->Units = units;
}
void Subject::setLimit(int limit)
{
	this->Limit = limit;
}
void Subject::setNextSubject(Subject* p)
{
	this->next = p;
}
void Subject::setClassTeacher(string name)
{
	this->Class_Teacher = name;
}

//GET METHODS
string Subject::getIDS()
{
	return this->IDS;
}
string Subject::getName()
{
	return this->Name;
}
int Subject::getUnit()
{
	return this->Units;
}
int Subject::getLimit()
{
	return this->Limit;
}
Subject* Subject::getNextSubject()
{
	return this->next;
}
string Subject::getClassTeacher()
{
	return this->Class_Teacher;
}