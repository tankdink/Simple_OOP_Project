#pragma once
#include "Date.h"
#include <string>
#include <string.h>
using namespace std;

class Admin
{
private:

	string password;
	string ID;
	string firstName;
	string lastName;
	string address;
	bool gender;                    //false is male, true is female
	Date DateOfBirth;
	Date AdmissionDate;
	Admin* next;

public:

	//DEFFAULT CONSTRUCTOR
	Admin();

	//SET METHODS
	void setPassword(string);
	void setNext(Admin*);
	void setID(string);
	void setfirstName(string);
	void setlastName(string);
	void setAddress(string);
	void setGender(int);
	void setDateOfBirth(Date);
	void setAdmissionDate(Date);

	//GET METHODS
	string getPassword();
	Admin* getNext();
	string getID();
	string getfirstName();
	string getlastName();
	void getGender();
	int getGender_();
	string getAddress();
	string getGenderr();
	Date getDateOfBirth();
	Date getAdmissionDate();

};
