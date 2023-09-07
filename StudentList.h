#pragma once
#include "Student.h"
#include "Date.h"
#include "Subject.h"
#include "Course.h"
#include <string>
#include <string.h>
#include <fstream>
using namespace std;

class StudentList : public Course
{
private:

	Student* head;
	Student* tail;
	fstream Export;

public:

	//DEFFAULT CONSTRUCTOR
	StudentList();

	//SET METHODS
	void setHead(Student*);
	void setTail(Student*);

	//GET METHODS
	Student* getHead();
	Student* getTail();
	Subject* GetSubjectWithID_Std(string);

	//CHECK METHODS
	bool checkID(string);
	bool checkGender(int);
	bool checkGPA(double);
	bool checkDate(int, int, int);
	bool login(string, string);

	//CREATE - ADD METHODS
	Student* createNewStudent(string, string, string, int, string, string, double, Date, Date, string, Course);
	void addNewStudent(int, Subject*);

	//SEARCH METHODS
	void SearchOneSV(string);
	void Search_With_Firstname(string);
	void Search_With_Fullname(string);
	void Search_With_Gender(int);
	void Search_With_Address(string);
	void Search_With_Class(string);
	void Search_With_GPA(double);
	void Search_With_DateOfBirth(Date);
	void Search_With_AdmissionDate(Date);
	void Menu_Search();

	//DELETE METHODS
	void Delete_One_SV(string);
	void Delete_With_Firstname(string);
	void Delete_With_Fullname(string);
	void Delete_With_Gender(int);
	void Delete_With_Address(string);
	void Delete_With_Class(string);
	void Delete_With_GPA(double);
	void Delete_With_DateOfBirth(Date);
	void Delete_With_AdmissionDate(Date);
	void Delete_All();
	void Menu_Delete();

	//MODIFY METHODS
	void ModifiedStudentWithID();
	void Modified_NameWithID();
	void Modified_AddressWithID();
	void Modified_ClassWithID();
	void Modified_GPAWithID();
	void Modified_IDWithID();
	void Modified_GenderWithID();
	void Modified_DOBWithID();
	void Modified_ADWithID();
	Student* GetStudentWithID(string);
	void Menu_Modifier();

	//SORT METHODS
	void Swap(Student*&, Student*&);
	void Sort_By_ID();
	void Sort_By_Firstname();
	void Sort_By_Class();
	void Sort_By_GPA();
	void Menu_Sort();

	//DISPLAY METHODS
	void MENU();
	void display();									//INFOR
	void Display_SubjectList();						//SUBJECT LIST
	void display_(string);							//INFOR ONE STD
	void display_subjects_One_Student(string);		//SUBJECT LIST ONE STD
	void DISPLAY_ALL();
	void Display_Acc();
	void display_account(string);					//ONE STUDENT 

	//ADD - DELETE - SEARCH SUBJECT FOR STUDENTS WITH STUDENT'S ID
	void Add_Subject_For_Student(string, string, Subject*);
	void Delete_Subject_For_Student(string, string);
	void Search_Subject_For_Student(string, string);

	//MODIFY METHODS
	void Modified_All_InFormation_With_IDS_Std(Subject*, string);
	void Modified_With_IDS_Std(Subject*, string);
	void Modified_With_Name_Std(Subject*, string);
	void Modified_With_Teacher_Name_Std(Subject*, string);
	void Modified_With_Units_Std(Subject*, string);
	void Modified_With_Limit_Std(Subject*, string);

	//DELETE METHODS
	void Delete_With_IDS_Std(string);
	void Delete_With_Name_Std(string);
	void Delete_With_Teacher_Name_Std(string);
	void Delete_With_Units_Std(int);
	void Delete_With_Limit_Std(int);
	void Delete_ALL();

	//SORT METHODS
	void SWAP(Subject*&, Subject*&);
	void Sort_With_IDS_Std();
	void Sort_With_Name_Std();
	void Sort_With_Teacher_Name_Std();
	void Sort_With_Unit_Std();
	void Sort_With_Limit_Std();

	//FILE INTERACTION
	void Export_to_file(fstream&);
	void Export_to_file_Acc(fstream&);
};

