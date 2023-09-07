#pragma once
#include "Subject.h"
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

class Course
{
private:

	int Number_Of_Subject;
	int Total_Unit;
	string Course_Name;
	Subject* head;
	Subject* tail;

public:

	//DEFFAULT CONSTRUCTOR
	Course();

	//CHECK METHODS
	bool checkIDS(string);
	bool checkName(string);
	bool checkUnit(int);
	bool checkLimit(int);

	//SET METHODS
	void setNumOfSubject(int);
	void setTotalUnit(int);
	void setCourseName(string);
	void setCourseHead(Subject*);
	void setCourseTail(Subject*);

	//GET METHODS
	int getNumOfSubject();
	int getTotalUnit();
	string getCourseName();
	Subject* getCourseHead();
	Subject* getCourseTail();

	//CREATE-ADD METHODS
	Subject* createNewSubject(string, string, string, int, int);
	void addNewSubject(int);

	//GET SUBJECT'S DETAIL WITH ID
	Subject* GetSubjectWithID(string);

	//MODIFY METHODS
	void Modified_All_InFormation_With_IDS_COURSE(string);
	void Modified_With_IDS(string);
	void Modified_With_Name(string);
	void Modified_With_Teacher_Name(string);
	void Modified_With_Units(string);
	void Modified_With_Limit(string);
	void Menu_Modified();

	//DELETE METHODS
	void Delete_With_IDS(string);
	void Delete_With_Name(string);
	void Delete_With_Teacher_Name(string);
	void Delete_With_Units(int);
	void Delete_With_Limit(int);
	void Delete_All();
	void Menu_Delete();

	//SEARCH METHODS
	Subject* findSubject(string);
	void Search_With_IDS(string);
	void Search_With_Name(string);
	void Search_With_Teacher_Name(string);
	void Search_With_Units(int);
	void Search_With_Limit(int);
	void Menu_Search();

	//SORT METHODS
	void Swap(Subject*&, Subject*&);
	void Sort_With_IDS();
	void Sort_With_Name();
	void Sort_With_Teacher_Name();
	void Sort_With_Unit();
	void Sort_With_Limit();
	void Menu_Sort();

	//DISPLAY METHOS
	void DISPLAY();

	//FILE INTERACTION
	void Export_to_file(fstream&);

	//DESTRUCTOR
	~Course() {};

};

