#include "Student.h"

#include <iostream>
using namespace std;

//DEFFAULT CONSTRUCTOR
Student::Student()
{
	this->password = "";
	this->ID = "Error";
	this->firstName = "Error";
	this->lastName = "Error";
	this->gender = false;
	this->address = "Error";
	this->class_ = "Error";
	this->GPA = 0.0;
	this->DateOfBirth = Date();
	this->AdmissionDate = Date();
	this->next = NULL;
}

//SET METHODS
void Student::setPassword(string password)
{
	this->password = password;
}
void Student::setNext(Student* next)
{
	this->next = next;
}
void Student::setID(string ID)
{
	this->ID = ID;
}
void Student::setfirstName(string firstName)
{
	this->firstName = firstName;
}
void Student::setlastName(string lastName)
{
	this->lastName = lastName;
}
void Student::setGender(int gender)
{
	this->gender = gender;
}
void Student::setAddress(string address)
{
	this->address = address;
}
void Student::setClass_(string class_)
{
	this->class_ = class_;
}
void Student::setGPA(double GPA)
{
	this->GPA = GPA;
}
void Student::setDateOfBirth(Date DateOfBirth)
{
	this->DateOfBirth = DateOfBirth;
}
void Student::setAdmissionDate(Date AdmissionDate)
{
	this->AdmissionDate = AdmissionDate;
}
void Student::setSubList(Course c)
{
	this->SubList = c;
}

//GET METHODS
string Student::getPassword()
{
	return password;
}
Student* Student::getNext()
{
	return next;
}
string Student::getID()
{
	return ID;
}
string Student::getfirstName()
{
	return firstName;
}
string Student::getlastName()
{
	return lastName;
}
void Student::getGender()
{
	if (!gender)
	{
		cout << "Male";
	}
	else cout << "Female";
}
int Student::getGender_()
{
	return (int)gender;
}
string Student::getGenderr()
{
	if (this->gender == 0)
	{
		string i = "Male";
		return i;
	}
	else
	{
		string i = "Female";
		return i;
	}
}
string Student::getAddress()
{
	return address;
}
string Student::getClass_()
{
	return class_;
}
double Student::getGPA()
{
	return GPA;
}
Date Student::getDateOfBirth()
{
	return DateOfBirth;
}
Date Student::getAdmissionDate()
{
	return AdmissionDate;
}
Course Student::getSubList()
{
	return SubList;
}
