#pragma once
#include "Date.h"
#include "Course.h"
#include <string>
#include <string.h>

class Student
{
private:

	string password;
	string ID;
	string firstName;
	string lastName;
	string address;
	string class_;
	bool gender;                    //false is male, true is female
	double GPA;
	Date DateOfBirth;
	Date AdmissionDate;
	Course SubList;
	Student* next;

public:

	//DEFFAULT CONSTRUCTOR
	Student();

	//SET METHODS
	void setPassword(string);
	void setNext(Student*);
	void setID(string);
	void setfirstName(string);
	void setlastName(string);
	void setGender(int);
	void setAddress(string);
	void setClass_(string);
	void setGPA(double);
	void setDateOfBirth(Date);
	void setAdmissionDate(Date);
	void setSubList(Course);

	//GET METHODS
	string getPassword();
	Student* getNext();
	string getID();
	string getfirstName();
	string getlastName();
	void getGender();
	int getGender_();
	string getAddress();
	string getGenderr();
	string getClass_();
	double getGPA();
	Date getDateOfBirth();
	Date getAdmissionDate();
	Course getSubList();

};
