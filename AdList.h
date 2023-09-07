#pragma once
#include "StudentList.h"
#include "Admin.h"
#include "Date.h"
#include "Student.h"
#include <fstream>

class AdList
{
private:

	Admin* head;
	Admin* tail;
	fstream Export, Import;

public:

	//DEFFAULT CONSTRUCTOR
	AdList();

	//SET METHODS
	void setHead(Admin*);
	void setTail(Admin*);

	//GET METHODS
	Admin* getHead();
	Admin* getTail();
	Admin* GetAdminWithID(string);

	//CHECK METHODS
	bool checkID(string);
	bool checkGender(int);
	bool checkDate(int, int, int);
	bool login(string, string);

	//CREATE - ADD METHODS
	Admin* createNewAdmin(string, string, string, string, int, Date, Date, string);
	void addNewAdmin(int);

	//SEARCH METHODS
	void Search_With_ID(string);
	void Search_With_Firstname(string);
	void Search_With_Fullname(string);
	void Search_With_Gender(int);
	void Search_With_Address(string);
	void Search_With_DateOfBirth(Date);
	void Search_With_AdmissionDate(Date);
	void Menu_Search();

	//DELETE METHODS
	void Delete_With_ID(string);
	void Delete_With_Firstname(string);
	void Delete_With_Fullname(string);
	void Delete_With_Gender(int);
	void Delete_With_Address(string);
	void Delete_With_DateOfBirth(Date);
	void Delete_With_AdmissionDate(Date);
	void Delete_All();
	void Menu_Delete();

	//MODIFY METHODS
	void Modified_AdminWithID();
	void Modified_NameWithID();
	void Modified_AddressWithID();
	void Modified_IDWithID();
	void Modified_GenderWithID();
	void Modified_DOBWithID();
	void Modified_ADWithID();
	void Menu_Modifier();

	//SORT METHODS
	void Swap(Admin*&, Admin*&);
	void Sort_By_ID();
	void Sort_By_Firstname();
	void Menu_Sort();

	//MENU
	void MENU();

	//DISPLAY METHODS
	void display();
	void displayAccStd(StudentList);

	//FILE INTERACTION
	void Export_to_file(fstream&);

};

