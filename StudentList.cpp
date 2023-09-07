#include "StudentList.h"
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>

#include <conio.h>
#include <Windows.h>

using namespace std;

void textcolorrr(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void gotoxyrrr(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int cursorrr(int& select, int minH, int maxH, int maxSe, int posCur)
{
	char x;
	int y = minH;
	gotoxyrrr(posCur, y);
	textcolorrr(12);
	cout << char(17);
	textcolorrr(7);
	gotoxyrrr(0, 0);

	gotoxyrrr(posCur, y);
	x = ' ';
	select = 1;
	while (true)
	{
		x = _getch();
		if (x == 13) break;
		if (x == 224) x = _getch();
		if (x == 80) //DOWN
		{
			if (y == maxH)
			{
				gotoxyrrr(posCur, y);
				cout << "  ";
				y = minH;
				gotoxyrrr(posCur, y);
				textcolorrr(12);
				cout << char(17);
				textcolorrr(7);
				select = 1;
			}
			else
			{
				gotoxyrrr(posCur, y);
				cout << "  ";
				gotoxyrrr(posCur, y += 1);
				textcolorrr(12);
				cout << char(17);
				textcolorrr(7);
				select++;
			}
		}
		if (x == 72) //UP
		{
			if (y == minH)
			{
				gotoxyrrr(posCur, y);
				cout << "  ";
				y = maxH;
				gotoxyrrr(posCur, y);
				textcolorrr(12);
				cout << char(17);
				textcolorrr(7);
				select = maxSe;
			}
			else
			{
				gotoxyrrr(posCur, y);
				cout << "  ";
				gotoxyrrr(posCur, y -= 1);
				textcolorrr(12);
				cout << char(17);
				textcolorrr(7);
				select--;
			}
		}
	}
	return select;
}


//DEFFAULT CONSTRUCTOR
StudentList::StudentList()
{
	head = tail = NULL;
}

//SET METHODS
void StudentList::setHead(Student* newHead)
{
	this->head = newHead;
}
void StudentList::setTail(Student* newTail)
{
	this->tail = newTail;
}

//GET METHODS
Student* StudentList::getHead()
{
	return head;
}
Student* StudentList::getTail()
{
	return tail;
}
Subject* StudentList::GetSubjectWithID_Std(string ID_)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		int count = 0;
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == ID_)
			{
				count++;
				return k;
			}
		}
		if (count == 0)
		{
			cout << "\nSubject Not Found!\n";
			system("pause");
			return NULL;
		}

	}
	return NULL;
}

//CHECK METHODS
bool StudentList::checkID(string ID)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID) { return 0; }
	}
	return 1;
}
bool StudentList::checkGender(int gender)
{
	if (gender != 0 && gender != 1) return 0;
	return 1;
}
bool StudentList::checkGPA(double GPA)
{
	if (GPA < 0.0 || GPA>10.0) return 0;
	return 1;
}
bool StudentList::checkDate(int day, int month, int year)
{
	if (day > 31 || day <= 0 || month <= 0 || month > 12 || year < 1900 || year > 2022) return 0;
	switch (month)
	{
	case 2:
	{
		if (day > 29) return 0;
		if (year % 400 != 0 && day > 28) return 0;
	}
	case 4: if (day > 30) return 0;
	case 6: if (day > 30) return 0;
	case 9: if (day > 30) return 0;
	case 11: if (day > 30) return 0;
	default:
		break;
	}
	return 1;
}
bool StudentList::login(string id, string password)
{
	for (Student* i = head; i != NULL; i = i->getNext()) if (i->getID() == id && i->getPassword() == password) return 1;
	return 0;
}

//CREATE - ADD METHOD
Student* StudentList::createNewStudent(string ID, string firstName, string lastName, int gender, string address, string class_, double GPA, Date DateOfBirth, Date AdmissionDate, string password, Course sublist)
{
	Student* newStudent = new Student[1];
	newStudent->setPassword(password);
	newStudent->setID(ID);
	newStudent->setfirstName(firstName);
	newStudent->setlastName(lastName);
	newStudent->setGender(gender);
	newStudent->setAddress(address);
	newStudent->setClass_(class_);
	newStudent->setGPA(GPA);
	newStudent->setDateOfBirth(DateOfBirth);
	newStudent->setAdmissionDate(AdmissionDate);
	newStudent->setSubList(sublist);
	newStudent->setNext(NULL);
	return newStudent;
}
void StudentList::addNewStudent(int n, Subject* pHead)
{
	string ID, firstName, lastName, address, class_, password;
	int gender_choice;
	double GPA;
	for (int i = 1; i <= n; i++)
	{
		system("cls");
		cout << "-----INPUT INFORMATION FOR STUDENT " << i << "-----" << endl;
		do
		{
			cout << "ID: ";
			getline(cin, ID);
			if (checkID(ID) == 0) cout << "Duplicated ID! Please try again!" << endl;
		} while (checkID(ID) == 0);
		cout << "Create password: ";
		getline(cin, password);
		cout << "First name: "; getline(cin, firstName);
		cout << "Last name: "; getline(cin, lastName);
		do
		{
			cout << "Gender:\n0. Male\n1.Female\n-->"; cin >> gender_choice;
			if (checkGender(gender_choice) == 0) cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl;
		} while (checkGender(gender_choice) == 0);
		cin.ignore();
		cout << "Address: "; getline(cin, address);
		cout << "Class: "; getline(cin, class_);
		do
		{
			cout << "GPA: "; cin >> GPA;
			if (checkGPA(GPA) == 0) cout << "Error input! Please try again! (GPA must be >= 0.0 or <= 10.0)" << endl;
		} while (checkGPA(GPA) == 0);
		cin.ignore();
		cout << "\nInput Date Of Birthday\n";
		int day;
		cout << "Day Of BirthDay: ";
		cin >> day;
		int month;
		cout << "Month Of BirthDay: ";
		cin >> month;
		int year;
		cout << "Year Of BirthDay: ";
		cin >> year;
		Date DateOfBirth(day, month, year);
		cout << "\nInput Admission Date\n";
		int day_;
		cout << "Day Of AdmissionDate: ";
		cin >> day_;
		int month_;
		cout << "Month Of AdmissionDate: ";
		cin >> month_;
		int year_;
		cout << "Year Of AdmissionDate: ";
		cin >> year_;
		Date AdmissionDate(day_, month_, year_);
		cin.ignore();

		Course sublist;
		int sl;
		cout << "\nEnter Number Subject: ";
		cin >> sl;
		cin.ignore();

		for (int i = 1; i <= sl; i++)
		{
			bool flag;
			do
			{
				flag = false;
				string IDS;
				cout << "\nInput ID Subject You Want To Add: "; getline(cin, IDS);
				for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
				{
					if (k->getIDS() == IDS)
					{
						flag = true;
						string IDS_, name_, CT;
						int unit, limit;
						IDS_ = k->getIDS();
						name_ = k->getName();
						CT = k->getClassTeacher();
						unit = k->getUnit();
						limit = k->getLimit();
						Subject* temp = sublist.createNewSubject(IDS_, name_, CT, unit, limit);
						if (sublist.getCourseHead() == NULL)
						{
							sublist.setCourseHead(temp);
							sublist.setCourseTail(temp);
							cout << "\n\t\t==================Added Successfully====================\n";
							break;
						}
						sublist.getCourseTail()->setNextSubject(temp);
						sublist.setCourseTail(temp);
						cout << "\n\t\t==================Added Successfully====================\n";
						break;
					}
				}
				if (flag == false)
				{
					cout << "\nIncorrect ID Subject!Please Try Again\n";
				}
			} while (flag == false);
		}

		Student* newStudent = createNewStudent(ID, firstName, lastName, gender_choice, address, class_, GPA, DateOfBirth, AdmissionDate, password, sublist);
		if (head == NULL) head = tail = newStudent;
		else
		{
			tail->setNext(newStudent);
			tail = newStudent;
		}
	}
}

//SEARCH METHODS
Student* StudentList::GetStudentWithID(string ID_)
{
	Student* temp;
	int count = 0;
	for (temp = head; temp != NULL; temp = temp->getNext())
	{
		if (temp->getID() == ID_)
		{
			count++;
			return temp;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent Not Found!\n";
		system("pause");
		return NULL;
	}
	return NULL;
}
void StudentList::SearchOneSV(string ID_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
			return;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_Firstname(string Firstname_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getfirstName() == Firstname_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_Fullname(string Fullname_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		string fullname = i->getlastName() + " " + i->getfirstName();
		if (fullname == Fullname_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_Gender(int gender_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getGender_() == gender_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_Address(string Address_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getAddress() == Address_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_Class(string Class_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getClass_() == Class_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_GPA(double GPA_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getGPA() == GPA_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_DateOfBirth(Date DateOfBirth_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getDateOfBirth().getDay() == DateOfBirth_.getDay() && i->getDateOfBirth().getMonth() == DateOfBirth_.getMonth() && i->getDateOfBirth().getYear() == DateOfBirth_.getYear())
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Search_With_AdmissionDate(Date AdmissionDate_)
{
	cout << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	int count = 0;
	for (Student* i = head; i != NULL; i = i->getNext())
	{

		if (i->getAdmissionDate().getDay() == AdmissionDate_.getDay() && i->getAdmissionDate().getMonth() == AdmissionDate_.getMonth() && i->getAdmissionDate().getYear() == AdmissionDate_.getYear())
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(5) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nStudent not found!\n";
	}
}
void StudentList::Menu_Search()
{
	int select;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 50; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(19) << left << "" << setw(31) << left << "MENU  SEARCH" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 1. Search One Student With ID " << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 2. Search With Fullname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 3. Search With Firstname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 4. Search With Gender" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 5. Search With Address" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 6. Search With Class" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 7. Search With GPA" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 8. Search With Date Of Birth" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 9. Search With AdmissionDate" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 10. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 50; i++)
			cout << char(205);
		cout << char(188);

		cursorrr(*&select, 4, 13, 10, 98);


		if (select == 1)
		{
			//cin.ignore();
			string ID_;
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
			do
			{
				cout << "Enter the \"ID\" you want to find: ";
				getline(cin, ID_);
				if (checkID(ID_) == 1) cout << "\nIncorrect ID! Please try again!\n" << endl;
			} while (checkID(ID_) == 1);
			system("cls");
			SearchOneSV(ID_);
			system("pause");
		}
		else if (select == 2)
		{
			//cin.ignore();
			string Fullname_;
			cout << "\n\n\n\n\n\n\n\n\n\nEnter the \"fullname\" you want to find: ";
			getline(cin, Fullname_);
			system("cls");
			Search_With_Fullname(Fullname_);
			system("pause");
		}
		else if (select == 3)
		{
			//cin.ignore();
			string Firstname_;
			cout << "\n\n\n\n\n\n\n\n\nEnter the \"firstname\" you want to find: ";
			getline(cin, Firstname_);
			system("cls");
			Search_With_Firstname(Firstname_);
			system("pause");
		}
		else if (select == 4)
		{
			int gender_;
			cout << "\n\n\n\n\n\n\n\nEnter the \"gender\" you want to find\n";

			do
			{
				cout << "Gender:\n0. Male\n1.Female\n-->"; cin >> gender_;
				if (checkGender(gender_) == 0) cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl;
			} while (checkGender(gender_) == 0);
			system("cls");
			Search_With_Gender(gender_);
			system("pause");
		}
		else if (select == 5)
		{
			//cin.ignore();
			string Address_;
			cout << "\n\n\n\n\n\n\nEnter the \"address\" you want to find: ";
			getline(cin, Address_);
			system("cls");
			Search_With_Address(Address_);
			system("pause");
		}
		else if (select == 6)
		{
			//cin.ignore();
			string Class_;
			cout << "\n\n\n\n\n\nEnter the \"class\" you want to find: ";
			getline(cin, Class_);
			system("cls");
			Search_With_Class(Class_);
			system("pause");
		}
		else if (select == 7)
		{
			double GPA_;
			cout << "\n\n\n\n\nEnter the \"GPA\" you want to find: ";
			cin >> GPA_;
			system("cls");
			Search_With_GPA(GPA_);
			system("pause");
		}
		else if (select == 8)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\n\nEnter Day Of Birthday: ";
			cin >> day;
			cout << "Enter Month Of Birthday: ";
			cin >> month;
			cout << "Enter Year Of Birthday: ";
			cin >> year;
			date = Date(day, month, year);
			system("cls");
			Search_With_DateOfBirth(date);
			system("pause");
		}
		else if (select == 9)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\nEnter Day Of AdmissionDate: ";
			cin >> day;
			cout << "Enter Month Of AdmissionDate: ";
			cin >> month;
			cout << "Enter Year Of AdmissionDate: ";
			cin >> year;
			date = Date(day, month, year);
			system("cls");
			Search_With_AdmissionDate(date);
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//MODIFY METHODS
void StudentList::ModifiedStudentWithID()
{
	string ID, firstName, lastName, address, class_;
	int gender_choice, day, month, year;
	double GPA;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Modified: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED INFORMATION FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	do
	{
		cout << "New ID: "; getline(cin, ID);
		if (checkID(ID) == 0) { cout << "Duplicated ID! Please try again!" << endl; }
		else {
			cout << "Valid ID!" << endl;
			selectedStudent->setID(ID);
			break;
		}
	} while (checkID(ID) == 0);
	cout << "New First name: "; getline(cin, firstName); selectedStudent->setfirstName(firstName);
	cout << "New Last name: "; getline(cin, lastName); selectedStudent->setlastName(lastName);
	do
	{
		cout << "New Gender:\n0. Male\n1.Female\n-->"; cin >> gender_choice;
		if (checkGender(gender_choice) == 0) { cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl; }
		else {
			selectedStudent->setGender(gender_choice);
			break;
		}
	} while (checkGender(gender_choice) == 0);
	cin.ignore();
	cout << "New Address: "; getline(cin, address); selectedStudent->setAddress(address);
	cout << "New Class: "; getline(cin, class_); selectedStudent->setClass_(class_);
	do
	{
		cout << "New GPA: "; cin >> GPA;
		if (checkGPA(GPA) == 0) { cout << "Error input! Please try again! (GPA must be >= 0.0 or <= 10.0" << endl; }
		else { selectedStudent->setGPA(GPA); }
	} while (checkGPA(GPA) == 0);
	cin.ignore();

	cout << "\n\2Input Date Of Birthday\2\n";
	cout << "Day Of BirthDay: ";
	cin >> day;
	cout << "Month Of BirthDay: ";
	cin >> month;
	cout << "Year Of BirthDay: ";
	cin >> year;
	Date DateOfBirth(day, month, year);
	selectedStudent->setDateOfBirth(DateOfBirth);

	cout << "\n\2Input  Of Admission Date\2\n";
	cout << "Day Of BirthDay: ";
	cin >> day;
	cout << "Month Of BirthDay: ";
	cin >> month;
	cout << "Year Of BirthDay: ";
	cin >> year;
	Date AdmissionDate(day, month, year);
	selectedStudent->setAdmissionDate(AdmissionDate);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_IDWithID()
{
	string ID;
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED ID FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	do
	{
		cout << "New ID: "; getline(cin, ID);
		if (checkID(ID) == 0) { cout << "Duplicated ID! Please try again!" << endl; }
		else {
			cout << "Valid ID! Done Changes!" << endl;
			selectedStudent->setID(ID);
			break;
		}
	} while (checkID(ID) == 0);
}
void StudentList::Modified_NameWithID()
{
	string firstName, lastName, ID;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search : "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED NAME FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "New First name: "; getline(cin, firstName); selectedStudent->setfirstName(firstName);
	cout << "New Last name: "; getline(cin, lastName); selectedStudent->setlastName(lastName);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_AddressWithID()
{
	string address, ID;
	cout << "\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED ADDRESS FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "New Address: "; getline(cin, address); selectedStudent->setAddress(address);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_ClassWithID()
{
	string class_, ID;
	cout << "\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}	system("cls");
	cout << "-----MODIFIED CLASS FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "New Class: "; getline(cin, class_); selectedStudent->setClass_(class_);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_GPAWithID()
{
	double GPA;
	string ID;
	cout << "\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED GPA FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	do
	{
		cout << "New GPA: "; cin >> GPA;
		if (checkGPA(GPA) == 0) { cout << "Error input! Please try again! (GPA must be >= 0.0 or <= 10.0" << endl; }
		else { selectedStudent->setGPA(GPA); }
	} while (checkGPA(GPA) == 0);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_GenderWithID()
{
	int gender_choice;
	string ID;
	cout << "\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED GENDER FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	do
	{
		cout << "New Gender:\n0. Male\n1.Female\n-->"; cin >> gender_choice;
		if (checkGender(gender_choice) == 0) { cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl; }
		else {
			selectedStudent->setGender(gender_choice);
			break;
		}
	} while (checkGender(gender_choice) == 0);
	cout << "Done Changes!" << endl;
}
void StudentList::Modified_DOBWithID()
{
	string ID;
	Date DOB;
	cout << "\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED DATE OF BIRTH FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "\n\2Input Date Of Birthday\2\n";
	int day;
	cout << "Day Of BirthDay: ";
	cin >> day;
	int month;
	cout << "Month Of BirthDay: ";
	cin >> month;
	int year;
	cout << "Year Of BirthDay: ";
	cin >> year;
	Date DateOfBirth(day, month, year);
	selectedStudent->setDateOfBirth(DateOfBirth);
	cout << "Done Changes!" << endl;

}
void StudentList::Modified_ADWithID()
{
	string ID;
	Date AD;
	cout << "\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Student! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Student* selectedStudent = GetStudentWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED Admission DATE FOR STUDENT WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "\n\2Input  Of Admission Date\2\n";
	int day;
	cout << "Day Of BirthDay: ";
	cin >> day;
	int month;
	cout << "Month Of BirthDay: ";
	cin >> month;
	int year;
	cout << "Year Of BirthDay: ";
	cin >> year;
	Date AdmissionDate(day, month, year);
	selectedStudent->setAdmissionDate(AdmissionDate);
	cout << "Done Changes!" << endl;

}
void StudentList::Menu_Modifier()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(22) << left << "" << setw(36) << left << "MODIFIED  MENU" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Modified Student with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Modified ID with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 3. Modified Name with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 4. Modified Address with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 5. Modified Class with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 6. Modified GPA with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 7. Modified Gender with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 8. Modified Day Of Birth with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 9. Modified Admission Day with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 10.Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 11.Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(188);

		cursorrr(*&choice, 4, 14, 11, 106);

		if (choice == 1)
		{
			//cin.ignore();
			ModifiedStudentWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 2)
		{
			//cin.ignore();
			Modified_IDWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 3)
		{
			//cin.ignore();
			Modified_NameWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 4)
		{
			//cin.ignore();
			Modified_AddressWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 5)
		{
			//cin.ignore();
			Modified_ClassWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 6)
		{
			//cin.ignore();
			Modified_GPAWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 7)
		{
			//cin.ignore();
			Modified_GenderWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 8)
		{
			//cin.ignore();
			Modified_DOBWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 9)
		{
			//cin.ignore();
			Modified_ADWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 10)
		{
			system("cls");
			display();
			system("pause");
		}
		else
		{
			break;
		}

	}
}

//DELETE METHODS
void StudentList::Delete_One_SV(string ID_)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else if (head->getID() == ID_)
	{
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; i = i->getNext())
		{
			if (i->getNext()->getID() == ID_)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
				return;
			}
		}
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_Firstname(string firstname)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getfirstName() == firstname)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getfirstName() == firstname)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_Fullname(string fullname)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			//string fullname_ = i->getNext()->getlastName() + " " + i->getNext()->getfirstName();
			if ((i->getNext()->getlastName() + " " + i->getNext()->getfirstName()) == fullname)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if ((head->getlastName() + " " + head->getfirstName()) == fullname)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_Gender(int gender)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getGender_() == gender)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getGender_() == gender)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_Address(string address)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getAddress() == address)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getAddress() == address)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_Class(string class_)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getClass_() == class_)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getClass_() == class_)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_GPA(double gpa)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getGPA() == gpa)
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getGPA() == gpa)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_DateOfBirth(Date dateofbirth)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getDateOfBirth().getDay() == dateofbirth.getDay() && i->getNext()->getDateOfBirth().getMonth() == dateofbirth.getMonth() && i->getNext()->getDateOfBirth().getYear() == dateofbirth.getYear())
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getDateOfBirth().getDay() == dateofbirth.getDay() && head->getDateOfBirth().getMonth() == dateofbirth.getMonth() && head->getDateOfBirth().getYear() == dateofbirth.getYear())
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_With_AdmissionDate(Date Admissiondate)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Student* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getAdmissionDate().getDay() == Admissiondate.getDay() && i->getNext()->getAdmissionDate().getMonth() == Admissiondate.getMonth() && i->getNext()->getAdmissionDate().getYear() == Admissiondate.getYear())
			{
				Student* h = i->getNext();
				if (h == tail)
				{
					tail = i;
				}
				i->setNext(h->getNext());
				delete[] h;
				count++;
			}
			else
			{
				i = i->getNext();
			}
		}
	}
	if (head->getAdmissionDate().getDay() == Admissiondate.getDay() && head->getAdmissionDate().getMonth() == Admissiondate.getMonth() && head->getAdmissionDate().getYear() == Admissiondate.getYear())
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Student* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find students to delete!\n";
		system("pause");
	}
}
void StudentList::Delete_All()
{
	while (head != NULL)
	{
		if (head == tail)
			head = tail = NULL;
		Student* p = head;
		head = head->getNext();
		delete[] p;
	}
}
void StudentList::Menu_Delete()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 60; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(24) << left << "" << setw(36) << left << "MENU  DELETE" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 1. Delete One Student With ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 2. Delete With Fullname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 3. Delete With Firstname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 4. Delete With Gender" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 5. Delete With Address" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 6. Delete With Class" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 7. Delete With GPA" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 8. Delete With Date Of Birth" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 9. Delete With AdmissionDate" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 10.Delete All" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 11.Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(60) << left << " 12.Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 60; i++)
			cout << char(205);
		cout << char(188);

		cursorrr(*&choice, 4, 15, 12, 108);

		if (choice == 1)
		{
			//cin.ignore();
			string ID_;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\nEnter the \"ID\" you want to delete: ";
			getline(cin, ID_);
			Delete_One_SV(ID_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 2)
		{
			//cin.ignore();
			string Fullname_;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\nEnter the \"fullname\" you want to delete: ";
			getline(cin, Fullname_);
			Delete_With_Fullname(Fullname_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");

		}
		else if (choice == 3)
		{
			//cin.ignore();
			string Firstname_;
			cout << "\n\n\n\n\n\n\n\n\n\n\nEnter the \"firstname\" you want to delete: ";
			getline(cin, Firstname_);
			Delete_With_Firstname(Firstname_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");

		}
		else if (choice == 4)
		{
			int gender_;
			cout << "\n\n\n\n\n\n\n\n\n\nEnter the \"gender\" you want to delete\n";

			do
			{
				cout << "Gender:\n0. Male\n1.Female\n-->"; cin >> gender_;
				if (checkGender(gender_) == 0) cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl;
			} while (checkGender(gender_) == 0);
			Delete_With_Gender(gender_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");

		}
		else if (choice == 5)
		{
			//cin.ignore();
			string Address_;
			cout << "\n\n\n\n\n\n\n\n\nEnter the \"address\" you want to delete: ";
			getline(cin, Address_);
			Delete_With_Address(Address_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 6)
		{
			//cin.ignore();
			string Class_;
			cout << "\n\n\n\n\n\n\n\nEnter the \"class\" you want to delete: ";
			getline(cin, Class_);
			Delete_With_Class(Class_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 7)
		{
			double GPA_;
			cout << "\n\n\n\n\n\n\nEnter the \"GPA\" you want to delete: ";
			cin >> GPA_;
			Delete_With_GPA(GPA_);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 8)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\n\n\n\nEnter Day Of Birthday: ";
			cin >> day;
			cout << "Enter Month Of Birthday: ";
			cin >> month;
			cout << "Enter Year Of Birthday: ";
			cin >> year;
			date = Date(day, month, year);
			Delete_With_DateOfBirth(date);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 9)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\n\n\nEnter Day Of AdmissionDate: ";
			cin >> day;
			cout << "Enter Month Of AdmissionDate: ";
			cin >> month;
			cout << "Enter Year Of AdmissionDate: ";
			cin >> year;
			date = Date(day, month, year);
			Delete_With_AdmissionDate(date);
			cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 10)
		{
			Delete_All();
			cout << "\n\n\n\n\t\t===============Deleted Successfully!================\n\n";
			system("pause");
		}
		else if (choice == 11)
		{
			display();
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//SORT METHODS
void StudentList::Swap(Student*& x, Student*& y)
{
	string ID, firstname, lastname, address, class_;
	int gender;
	double GPA;
	Date DOB, AD;

	ID = x->getID();
	firstname = x->getfirstName();
	lastname = x->getlastName();
	address = x->getAddress();
	class_ = x->getClass_();
	gender = x->getGender_();
	GPA = x->getGPA();
	DOB = x->getDateOfBirth();
	AD = x->getAdmissionDate();

	x->setID(y->getID());
	x->setfirstName(y->getfirstName());
	x->setlastName(y->getlastName());
	x->setAddress(y->getAddress());
	x->setClass_(y->getClass_());
	x->setGender(y->getGender_());
	x->setGPA(y->getGPA());
	x->setDateOfBirth(y->getDateOfBirth());
	x->setAdmissionDate(y->getAdmissionDate());

	y->setID(ID);
	y->setfirstName(firstname);
	y->setlastName(lastname);
	y->setAddress(address);
	y->setClass_(class_);
	y->setGender(gender);
	y->setGPA(GPA);
	y->setDateOfBirth(DOB);
	y->setAdmissionDate(AD);
}
void StudentList::Sort_By_ID()
{
	for (Student* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Student* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getID()) > (h->getID()))
			{
				Swap(k, h);
			}
		}
	}
}
void StudentList::Sort_By_Firstname()
{
	for (Student* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Student* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getfirstName()) > (h->getfirstName()))
			{
				Swap(k, h);
			}
		}
	}
}
void StudentList::Sort_By_Class()
{
	for (Student* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Student* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getClass_()) > (h->getClass_()))
			{
				Swap(k, h);
			}
		}
	}
}
void StudentList::Sort_By_GPA()
{
	for (Student* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Student* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getGPA()) > (h->getGPA()))
			{
				Swap(k, h);
			}
		}
	}
}
void StudentList::Menu_Sort()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 48; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(19) << left << "" << setw(29) << left << "MENU  SORT" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 1. Sort by ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 2. Sort by firstname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 3. Sort by class" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 4. Sort by GPA" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 5. Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 6. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 48; i++)
			cout << char(205);
		cout << char(188);


		cursorrr(*&choice, 4, 9, 6, 96);

		//system("pause");
		if (choice == 1)
		{
			Sort_By_ID();
			cout << "\n\n\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
			system("pause");
		}
		else if (choice == 2)
		{
			Sort_By_Firstname();
			cout << "\n\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
			system("pause");
		}
		else if (choice == 3)
		{
			Sort_By_Class();
			cout << "\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
			system("pause");
		}
		else if (choice == 4)
		{
			Sort_By_GPA();
			cout << "\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
			system("pause");
		}
		else if (choice == 5)
		{
			display();
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//DISPLAY METHODS
void StudentList::MENU()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\2 \2 \2 \2 \2 \2 \2 \2 \2 \2 \2 Welcome to \"Student Management Project\" \2 \2 \2 \2 \2 \2 \2 \2 \2";
		cout << "\n\t\t1.Add students to the list";
		cout << "\n\t\t2.Display";
		cout << "\n\t\t3.Menu search";
		cout << "\n\t\t4.Menu modifier";
		cout << "\n\t\t5.Menu delete";
		cout << "\n\t\t6.Menu sort";
		cout << "\n\t\t7.Import from file";
		cout << "\n\t\t8.Export to file";
		cout << "\n\t\t0.Log out";
		cout << "\n\t\t=====================================\2\2\2\2\2\2\2\2\2\2\2================================";

		cout << "\nYour choice: ";
		cin >> choice;
		if (choice < 0 || choice > 8)
		{
			cout << "Invalid choice!Please try again";
			system("pause");
		}
		else if (choice == 1)
		{
			//MENU NAY KHONG XAI TOI NEN BO CUNG DC
			int n;
			cout << "Enter the number of students: ";
			cin >> n;
			cin.ignore();
			//addNewStudent(n);
		}
		else if (choice == 2)
		{
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 3)
		{
			Menu_Search();
		}
		else if (choice == 4)
		{
			Menu_Modifier();
		}
		else if (choice == 5)
		{
			Menu_Delete();
		}
		else if (choice == 6)
		{
			Menu_Sort();
		}
		else if (choice == 7)
		{
			//Import_from_file(Import);
			system("pause");
		}
		else if (choice == 8)
		{
			//Export_to_file(Export);
			system("pause");
		}
		else
		{
			break;
		}
	}
}
void StudentList::Display_Acc()
{
	if (head == NULL)
	{
		cout << "LIST IS EMPTY\n";
		return;
	}
	cout << endl;
	cout << "\t\t\t\t\t\t" << setw(10) << left << "";
	for (int i = 1; i <= 5; i++)
		cout << char(205);
	cout << "ACCOUNT  INFORMATION";
	for (int i = 1; i <= 5; i++)
		cout << char(205);
	cout << endl << endl;

	cout << "\t\t\t\t\t\t" << setw(25) << left << "        Username" << setw(25) << left << "        Password" << endl;

	cout << "\t\t\t\t\t\t";
	for (int i = 1; i <= 50; i++)
		cout << char(196);

	for (Student* k = head; k != NULL; k = k->getNext())
	{
		cout << "\n\t\t\t\t\t\t" << setw(8) << left << "" << setw(17) << left << k->getID() << setw(8) << left << "" << setw(17) << left << k->getPassword() << endl;

		cout << "\t\t\t\t\t\t";
		for (int i = 1; i <= 50; i++)
			cout << char(196);
	}
}
void StudentList::display_account(string ID)
{
	cout << "\n\n\t\t\t\t\t\t\t\t===================ACCOUNT INFORMATION====================\n\n";
	cout << "\t\t\t\t\t\t\t\t\t" << setw(20) << left << "Username" << setw(20) << left << "Password" << endl;
	for (Student* k = head; k != NULL; k = k->getNext())
	{
		if (k->getID() == ID)
		{
			cout << "\t\t\t\t\t\t\t\t\t" << setw(20) << left << k->getID() << setw(20) << left << k->getPassword() << endl;
		}
	}
}
void StudentList::display()
{
	if (head == NULL)
	{
		cout << "\nLIST IS EMPTY\n";
		return;
	}
	cout << endl;
	cout << setw(85) << left << "";
	for (int i = 1; i <= 10; i++)
		cout << char(205);
	cout << "INFORMATION  STUDENT";
	for (int i = 1; i <= 10; i++)
		cout << char(205);

	cout << "\n\n" << char(218);
	for (int i = 2; i <= 208; i++)
	{
		if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131 || i == 157 || i == 183)
			cout << char(194);
		else
			cout << char(196);
	}
	cout << char(191);


	cout << "\n" << char(179) << setw(25) << left << "           ID" << char(179) << setw(25) << left << "         Fullname" << char(179) << setw(25) << left << "         Gender" << char(179) << setw(25) << left << "         Address" << char(179) << setw(25) << left << "         Class" << char(179)
		<< setw(25) << left << "           GPA" << char(179) << setw(25) << left << "     Date Of Birthday" << char(179) << setw(25) << left << "      AdmissionDate" << char(179) << endl;


	cout << char(195);
	for (int i = 2; i <= 208; i++)
	{
		if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131 || i == 157 || i == 183)
			cout << char(197);
		else
			cout << char(196);
	}
	cout << char(180);


	for (Student* i = head; i != NULL; i = i->getNext())
	{
		cout << "\n" << char(179) << setw(7) << left << "" << setw(18) << left << i->getID() << char(179) << setw(3) << left << "" << setw(22) << left << i->getlastName() + " " + i->getfirstName() << char(179) << setw(10) << left << "" << setw(15) << left << i->getGenderr() << char(179) << setw(8) << left << "" << setw(17) << left << i->getAddress() << char(179) << setw(8) << left << "" << setw(17) << left << i->getClass_() << char(179)
			<< setw(11) << left << "" << setw(14) << left << i->getGPA() << char(179) << setw(7) << left << "";
		i->getDateOfBirth().Display();
		cout << setw(8) << left;
		cout << "";
		cout << char(179);
		cout << setw(7) << left << "";
		i->getAdmissionDate().Display();
		cout << setw(8) << left;
		cout << "";
		cout << char(179);
		cout << endl;

		if (i == tail)
		{
			cout << char(192);
			for (int i = 2; i <= 208; i++)
			{
				if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131 || i == 157 || i == 183)
					cout << char(193);
				else
					cout << char(196);
			}
			cout << char(217);
		}
		else
		{
			cout << char(195);
			for (int i = 2; i <= 208; i++)
			{
				if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131 || i == 157 || i == 183)
					cout << char(197);
				else
					cout << char(196);
			}
			cout << char(180);
		}
	}
	cout << endl << endl;

}
void StudentList::Display_SubjectList()
{
	for (Student* k = head; k != NULL; k = k->getNext())
	{
		Subject* pHead = k->getSubList().getCourseHead();
		if (pHead == NULL)
		{
			cout << "\n\t\t\tEMPTY!\n\n";
			continue;
		}
		cout << "\n\n\t\t\t\t\t\t\t===============LIST OF SUBJECTS OF STUDENTS WITH ID<" << k->getID() << ">================\n\n";
		cout << "\t\t\t\t\t" << setw(20) << left << "Sub ID" << setw(40) << left << "Sub Name" << setw(30) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
		for (Subject* p = pHead; p != NULL; p = p->getNextSubject())
		{
			cout << "\t\t\t\t\t" << setw(20) << left << p->getIDS() << setw(40) << left << p->getName() << setw(30) << left << p->getClassTeacher() << setw(10) << left << p->getUnit() << setw(5) << left << p->getLimit() << endl;
		}
		cout << "\n\n";
	}
}
void StudentList::display_(string ID)
{
	cout << "\n\n\t\t\t\t\t\t\t\t===============\2INFORMATION STUDENT\2================\n\n";
	cout << "\t\t\t\t\t" << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
		<< setw(8) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID)
		{
			cout << "\t\t\t\t\t" << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(8) << left << i->getGPA();
			i->getDateOfBirth().Display();
			cout << setw(15) << left;
			cout << "";
			i->getAdmissionDate().Display();
			cout << endl;
			break;

		}
	}
}
void StudentList::display_subjects_One_Student(string ID)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID)
		{
			if (i->getSubList().getCourseHead() == NULL)
			{
				cout << "\nLIST IS EMPTY!\n";
				break;
			}
			cout << "\n\n\t\t\t\t\t\t\t===============LIST OF SUBJECTS OF STUDENTS WITH ID<" << i->getID() << ">================\n\n";
			cout << "\t\t\t\t\t" << setw(20) << left << "Sub ID" << setw(40) << left << "Sub Name" << setw(30) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
			for (Subject* k = i->getSubList().getCourseHead(); k != NULL; k = k->getNextSubject())
			{
				cout << "\t\t\t\t\t" << setw(20) << left << k->getIDS() << setw(40) << left << k->getName() << setw(30) << left << k->getClassTeacher() << setw(10) << left << k->getUnit() << setw(5) << left << k->getLimit() << endl;
			}
		}
	}
}
void StudentList::DISPLAY_ALL()
{
	cout << "\t\t\t===============\2STUDENT LIST\2================\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "FULLNAME" << setw(10) << left << "GENDER" << setw(15) << left << "ADDRESS" << setw(20) << left << "CLASS"
		<< setw(5) << left << "GPA" << setw(25) << left << "DATE OF BIRTHDAY" << setw(25) << left << "ADMISSIONDATE" << endl << endl;
	cout << setw(20) << left << "SUB ID" << setw(20) << left << "SUB NAME" << setw(20) << left << "TEACHER'S NAME" << setw(10) << left << "UNITS" << setw(5) << left << "LIMIT" << endl;
	cout << "=============================================================================================================================================================\n";
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
			<< setw(5) << left << i->getGPA();
		i->getDateOfBirth().Display();
		cout << setw(15) << left;
		cout << "";
		i->getAdmissionDate().Display();
		cout << endl << endl;

		//cout << "\n\n\t\t===============STUDENTLIST'S SUBJECTLIST================\n\n";
		Subject* pHead = i->getSubList().getCourseHead();
		if (pHead == NULL)
			return;
		for (Subject* p = pHead; p != NULL; p = p->getNextSubject())
		{
			cout << setw(20) << left << p->getIDS() << setw(20) << left << p->getName() << setw(20) << left << p->getClassTeacher() << setw(10) << left << p->getUnit() << setw(5) << left << p->getLimit() << endl;
		}
		cout << "\n\t\t\t----------------------------------------------------\n";
	}

}

//MODIFY METHODS
void StudentList::Modified_All_InFormation_With_IDS_Std(Subject* sub, string ID_Sub)
{
	string IDS_;
	string name_, CT;
	int unit, limit;


	if (sub == NULL)
		return;
	IDS_ = sub->getIDS();
	name_ = sub->getName();
	CT = sub->getClassTeacher();
	unit = sub->getUnit();
	limit = sub->getLimit();

	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == ID_Sub)
			{
				k->setIDS(IDS_);
				k->setName(name_);
				k->setClassTeacher(CT);
				k->setUnits(unit);
				k->setLimit(limit);
			}
		}
	}
}
void StudentList::Modified_With_IDS_Std(Subject* sub, string id)
{
	string ID;
	if (sub == NULL)
		return;
	ID = sub->getIDS();
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == id)
			{
				k->setIDS(ID);
			}
		}

	}
}
void StudentList::Modified_With_Name_Std(Subject* sub, string id)
{
	if (sub == NULL)
		return;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == id)
			{
				k->setName(sub->getName());
			}
		}

	}

}
void StudentList::Modified_With_Teacher_Name_Std(Subject* sub, string id)
{
	if (sub == NULL)

		for (Student* i = head; i != NULL; i = i->getNext())
		{
			Subject* pHead = i->getSubList().getCourseHead();
			Subject* pTail = i->getSubList().getCourseTail();
			for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
			{
				if (k->getIDS() == id)
				{
					k->setClassTeacher(sub->getClassTeacher());
				}
			}

		}
}
void StudentList::Modified_With_Units_Std(Subject* sub, string id)
{
	if (sub == NULL)
		return;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == id)
			{
				k->setUnits(sub->getUnit());
			}
		}

	}

}
void StudentList::Modified_With_Limit_Std(Subject* sub, string id)
{
	if (sub == NULL)
		return;
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
		{
			if (k->getIDS() == id)
			{
				k->setLimit(sub->getLimit());
			}
		}

	}

}

//DELETE METHODS
void StudentList::Delete_With_IDS_Std(string ID_)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		if (pHead->getIDS() == ID_ && pHead->getNextSubject() == NULL)
		{
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			pTail = NULL;
			delete[] p;
			Course c;
			i->setSubList(c);
			continue;
		}
		if (pHead->getIDS() == ID_ && pHead->getNextSubject() != NULL)
		{
			Subject* next = pHead->getNextSubject();
			SWAP(pHead, next);
		}
		for (Subject* i = pHead; i->getNextSubject() != NULL; i = i->getNextSubject())
		{
			if (i->getNextSubject()->getIDS() == ID_)
			{
				Subject* h = i->getNextSubject();
				if (h == pTail)
				{
					pTail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				break;
			}
		}
	}
}
void StudentList::Delete_With_Name_Std(string name)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		if (pHead->getName() == name && pHead->getNextSubject() == NULL)
		{
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			pTail = NULL;
			delete[] p;
			Course c;
			i->setSubList(c);
			continue;
		}
		if (pHead->getName() == name && pHead->getNextSubject() != NULL)
		{
			Subject* next = pHead->getNextSubject();
			SWAP(pHead, next);
		}
		for (Subject* i = pHead; i->getNextSubject() != NULL; i = i->getNextSubject())
		{
			if (i->getNextSubject()->getName() == name)
			{
				Subject* h = i->getNextSubject();
				if (h == pTail)
				{
					pTail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				break;
			}
		}
	}
}
void StudentList::Delete_With_Teacher_Name_Std(string tname)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		if (pHead->getClassTeacher() == tname && pHead->getNextSubject() == NULL)
		{
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			pTail = NULL;
			delete[] p;
			Course c;
			i->setSubList(c);
			continue;
		}
		if (pHead->getClassTeacher() == tname && pHead->getNextSubject() != NULL)
		{
			Subject* next = pHead->getNextSubject();
			SWAP(pHead, next);
		}
		for (Subject* i = pHead; i->getNextSubject() != NULL; i = i->getNextSubject())
		{
			if (i->getNextSubject()->getClassTeacher() == tname)
			{
				Subject* h = i->getNextSubject();
				if (h == pTail)
				{
					pTail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				break;
			}
		}
	}
}
void StudentList::Delete_With_Units_Std(int unit)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		if (pHead->getUnit() == unit && pHead->getNextSubject() == NULL)
		{
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			pTail = NULL;
			delete[] p;
			Course c;
			i->setSubList(c);
			continue;
		}
		if (pHead->getUnit() == unit && pHead->getNextSubject() != NULL)
		{
			Subject* next = pHead->getNextSubject();
			SWAP(pHead, next);
		}
		for (Subject* i = pHead; i->getNextSubject() != NULL; i = i->getNextSubject())
		{
			if (i->getNextSubject()->getUnit() == unit)
			{
				Subject* h = i->getNextSubject();
				if (h == pTail)
				{
					pTail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				break;
			}
		}
	}
}
void StudentList::Delete_With_Limit_Std(int limit)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		if (pHead->getLimit() == limit && pHead->getNextSubject() == NULL)
		{
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			pTail = NULL;
			delete[] p;
			Course c;
			i->setSubList(c);
			continue;
		}
		if (pHead->getLimit() == limit && pHead->getNextSubject() != NULL)
		{
			Subject* next = pHead->getNextSubject();
			SWAP(pHead, next);
		}
		for (Subject* i = pHead; i->getNextSubject() != NULL; i = i->getNextSubject())
		{
			if (i->getNextSubject()->getLimit() == limit)
			{
				Subject* h = i->getNextSubject();
				if (h == pTail)
				{
					pTail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				break;
			}
		}
	}
}
void StudentList::Delete_ALL()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		Subject* pTail = i->getSubList().getCourseTail();
		while (pHead != NULL)
		{
			if (pHead == pTail)
			{
				pTail = NULL;
				Course c;
				i->setSubList(c);
			}
			Subject* p = pHead;
			pHead = pHead->getNextSubject();
			delete[] p;
		}

	}
}
//SORT METHODS
void StudentList::SWAP(Subject*& x, Subject*& y)
{
	string IDS, name, Tname;
	int unit, limit;

	IDS = x->getIDS();
	name = x->getName();
	Tname = x->getClassTeacher();
	unit = x->getUnit();
	limit = x->getLimit();

	x->setIDS(y->getIDS());
	x->setName(y->getName());
	x->setClassTeacher(y->getClassTeacher());
	x->setUnits(y->getUnit());
	x->setLimit(y->getLimit());

	y->setIDS(IDS);
	y->setName(name);
	y->setClassTeacher(name);
	y->setUnits(unit);
	y->setLimit(limit);
}
void StudentList::Sort_With_IDS_Std()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
		{
			for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
			{
				if ((k->getIDS()) > (h->getIDS()))
				{
					SWAP(k, h);
				}
			}
		}

	}
}
void StudentList::Sort_With_Name_Std()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
		{
			for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
			{
				if (k->getName() > h->getName())
				{
					SWAP(k, h);
				}
			}
		}

	}
}
void StudentList::Sort_With_Teacher_Name_Std()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
		{
			for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
			{
				if (k->getClassTeacher() > h->getClassTeacher())
				{
					SWAP(k, h);
				}
			}
		}

	}
}
void StudentList::Sort_With_Unit_Std()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
		{
			for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
			{
				if (k->getUnit() > h->getUnit())
				{
					SWAP(k, h);
				}
			}
		}

	}
}
void StudentList::Sort_With_Limit_Std()
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		Subject* pHead = i->getSubList().getCourseHead();
		for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
		{
			for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
			{
				if (k->getLimit() > h->getLimit())
				{
					SWAP(k, h);
				}
			}
		}

	}
}

//ADD - DELETE - SEARCH SUBJECT FOR STUDENTS WITH STUDENT'S ID
void StudentList::Add_Subject_For_Student(string id, string IDS, Subject* pHead)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == id)
		{
			for (Subject* k = pHead; k != NULL; k = k->getNextSubject())
			{
				if (k->getIDS() == IDS)
				{
					string IDS_, name_, CT;
					int unit, limit;
					IDS_ = k->getIDS();
					name_ = k->getName();
					CT = k->getClassTeacher();
					unit = k->getUnit();
					limit = k->getLimit();
					Subject* temp = Course::createNewSubject(IDS_, name_, CT, unit, limit);
					if (i->getSubList().getCourseHead() == NULL)
					{
						Course c;
						c.setCourseHead(temp);
						c.setCourseTail(temp);
						i->setSubList(c);
						cout << "\n\n\t\t\t\t\t\t\t\t==================Registered successfully!!!====================\n";
						break;
					}
					else
					{
						Course c = i->getSubList();

						c.getCourseTail()->setNextSubject(temp);
						c.setCourseTail(temp);

						i->setSubList(c);

						cout << "\n\n\t\t\t\t\t\t\t\t==================Registered successfully====================\n";
						break;
					}
				}
			}
		}
	}
}
void StudentList::Delete_Subject_For_Student(string id, string id_sub)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == id)
		{
			Subject* pHead = i->getSubList().getCourseHead();
			Subject* pTail = i->getSubList().getCourseTail();
			if (pHead == NULL)
			{
				cout << "\nList is Empty!";
				system("pause");
				return;
			}
			if (pHead->getIDS() == id_sub && pHead->getNextSubject() == NULL)
			{
				Subject* p = pHead;
				pHead = pHead->getNextSubject();
				pTail = NULL;
				delete[] p;
				Course c;
				i->setSubList(c);
				return;
			}
			if (pHead->getIDS() == id_sub)
			{
				Subject* next = pHead->getNextSubject();
				SWAP(pHead, next);
			}
			for (Subject* k = pHead; k->getNextSubject() != NULL; k = k->getNextSubject())
			{
				if (k->getNextSubject()->getIDS() == id_sub)
				{
					Subject* h = k->getNextSubject();
					if (h == pTail)
					{
						pTail = k;
					}
					k->setNextSubject(h->getNextSubject());
					delete[] h;

					Course c;
					c.setCourseHead(pHead);
					c.setCourseTail(pTail);

					i->setSubList(c);
					return;
				}
			}
		}
	}
}
void StudentList::Search_Subject_For_Student(string id, string id_sub)
{
	for (Student* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == id)
		{
			Subject* pHead = i->getSubList().getCourseHead();
			Subject* pTail = i->getSubList().getCourseTail();
			int count = 0;
			for (Subject* p = pHead; p != NULL; p = p->getNextSubject())
			{
				if (p->getIDS() == id_sub)
				{
					cout << "\n\n\t\t\t\t\t\t\t\t===============LIST OF SUBJECTS OF STUDENTS WITH ID<" << i->getID() << ">================\n\n";
					cout << "\t\t\t\t\t\t\t" << setw(20) << left << "Sub ID" << setw(40) << left << "Sub Name" << setw(30) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
					cout << "\t\t\t\t\t\t\t" << setw(20) << left << p->getIDS() << setw(40) << left << p->getName() << setw(30) << left << p->getClassTeacher() << setw(10) << left << p->getUnit() << setw(5) << left << p->getLimit() << endl;
					count++;
				}
			}
			if (count == 0)
				cout << "\n\t\t\t\t\t\t\t\tSubject not found!\n";
		}
	}
}

////---------------FILE INTERACTION----------------
void StudentList::Export_to_file(fstream& Export)
{
	Export.open("BAITAPLONEXPORTSTD.txt", ios::out);//Tu doi ten file
	if (!Export) cout << "Cannot open file!";
	else
	{
		string day, month, year;
		Export << "\n\n\t\t\t\t\t\t\t\t\t\t===============INFORMATION STUDENT================\n\n";
		Export << "\t\t\t\t" << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(20) << left << "Class"
			<< setw(10) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
		for (Student* i = head; i != NULL; i = i->getNext())
		{
			Export << "\t\t\t\t" << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress() << setw(20) << left << i->getClass_()
				<< setw(10) << left << i->getGPA();
			day = to_string(i->getDateOfBirth().getDay());
			month = to_string(i->getDateOfBirth().getMonth());
			if (i->getDateOfBirth().getDay() < 10) day = "0" + day;
			if (i->getDateOfBirth().getMonth() < 10) month = "0" + month;
			Export << day << "/" << month << "/" << i->getDateOfBirth().getYear();
			Export << setw(15) << left;
			Export << "";
			day = to_string(i->getAdmissionDate().getDay());
			month = to_string(i->getAdmissionDate().getMonth());
			if (i->getAdmissionDate().getDay() < 10) day = "0" + day;
			if (i->getAdmissionDate().getMonth() < 10) month = "0" + month;
			Export << day << "/" << month << "/" << i->getAdmissionDate().getYear();
			Export << endl;
		}
	}
	Export.close();
}
void StudentList::Export_to_file_Acc(fstream& Export)
{
	Export.open("BAITAPLONEXPORTACCSTD.txt", ios::out);
	if (!Export) cout << "Cannot open file!";
	else
	{
		Export << "\n\n\t\t\t\t\t\t\t===================ACCOUNT INFORMATION====================\n";
		Export << "\t\t\t\t\t\t\t" << setw(20) << left << "Username" << setw(20) << left << "Password" << endl;
		for (Student* k = head; k != NULL; k = k->getNext())
		{
			Export << "\t\t\t\t\t\t\t" << setw(20) << left << k->getID() << setw(20) << left << k->getPassword() << endl;
		}
	}
	Export.close();
}
