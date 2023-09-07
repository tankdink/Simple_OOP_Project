#include "Admin.h"

#include <iostream>
using namespace std;

//DEFFAULT CONSTRUCTOR
Admin::Admin()
{
	this->password = "";
	this->ID = "Error";
	this->firstName = "Error";
	this->lastName = "Error";
	this->gender = false;
	this->address = "Error";
	this->DateOfBirth = Date();
	this->AdmissionDate = Date();
}

//SET METHODS
void Admin::setPassword(string password)
{
	this->password = password;
}
void Admin::setNext(Admin* next)
{
	this->next = next;
}
void Admin::setID(string ID)
{
	this->ID = ID;
}
void Admin::setfirstName(string firstName)
{
	this->firstName = firstName;
}
void Admin::setlastName(string lastName)
{
	this->lastName = lastName;
}
void Admin::setGender(int gender)
{
	this->gender = gender;
}
void Admin::setAddress(string address)
{
	this->address = address;
}
void Admin::setDateOfBirth(Date DateOfBirth)
{
	this->DateOfBirth = DateOfBirth;
}
void Admin::setAdmissionDate(Date AdmissionDate)
{
	this->AdmissionDate = AdmissionDate;
}

//GET METHODS
string Admin::getPassword()
{
	return password;
}
Admin* Admin::getNext()
{
	return next;
}
string Admin::getID()
{
	return ID;
}
string Admin::getfirstName()
{
	return firstName;
}
string Admin::getlastName()
{
	return lastName;
}
void Admin::getGender()
{
	if (!gender)
	{
		cout << "Male";
	}
	else cout << "Female";
}
int Admin::getGender_()
{
	return (int)gender;
}
string Admin::getGenderr()
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
string Admin::getAddress()
{
	return address;
}
Date Admin::getDateOfBirth()
{
	return DateOfBirth;
}
Date Admin::getAdmissionDate()
{
	return AdmissionDate;
}