#include "Course.h"

#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <fstream>

#include <conio.h>
#include <Windows.h>

using namespace std;


void textcolorx(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void gotoxyx(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int cursorx(int& select, int minH, int maxH, int maxSe, int posCur)
{
	char x;
	int y = minH;
	gotoxyx(posCur, y);
	textcolorx(12);
	cout << char(17);
	textcolorx(7);
	gotoxyx(0, 0);

	gotoxyx(posCur, y);
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
				gotoxyx(posCur, y);
				cout << "  ";
				y = minH;
				gotoxyx(posCur, y);
				textcolorx(12);
				cout << char(17);
				textcolorx(7);
				select = 1;
			}
			else
			{
				gotoxyx(posCur, y);
				cout << "  ";
				gotoxyx(posCur, y += 1);
				textcolorx(12);
				cout << char(17);
				textcolorx(7);
				select++;
			}
		}
		if (x == 72) //UP
		{
			if (y == minH)
			{
				gotoxyx(posCur, y);
				cout << "  ";
				y = maxH;
				gotoxyx(posCur, y);
				textcolorx(12);
				cout << char(17);
				textcolorx(7);
				select = maxSe;
			}
			else
			{
				gotoxyx(posCur, y);
				cout << "  ";
				gotoxyx(posCur, y -= 1);
				textcolorx(12);
				cout << char(17);
				textcolorx(7);
				select--;
			}
		}
	}
	return select;
}
//DEFFAULT CONSTRUCTOR
Course::Course()
{
	Number_Of_Subject = 0;
	Total_Unit = 0;
	Course_Name = "Error";
	head = NULL;
	tail = NULL;
}

//CHECK METHODS
bool Course::checkIDS(string IDS)
{
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getIDS() == IDS) { return 0; } //0: duplicate
	}
	return 1;
}
bool Course::checkName(string name)
{
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getName() == name) { return 0; } //0: duplicate
	}
	return 1;
}
bool Course::checkUnit(int Unit)
{
	if (Unit < 0 || Unit > 15)
	{
		return 0;
	}
	return 1;
}
bool Course::checkLimit(int limit)
{
	if (limit < 0 || limit > 300)
	{
		return 0;
	}
	return 1;
}

//SET METHODS
void Course::setNumOfSubject(int n)
{
	this->Number_Of_Subject = n;
}
void Course::setTotalUnit(int x)
{
	this->Total_Unit = x;
}
void Course::setCourseName(string name)
{
	this->Course_Name = name;
}
void Course::setCourseHead(Subject* p)
{
	head = p;
}
void Course::setCourseTail(Subject* p)
{
	tail = p;
}

//GET METHODS
int Course::getNumOfSubject()
{
	return this->Number_Of_Subject;
}
int Course::getTotalUnit()
{
	return this->Total_Unit;
}
string Course::getCourseName()
{
	return this->Course_Name;
}
Subject* Course::getCourseHead()
{
	return head;
}
Subject* Course::getCourseTail()
{
	return tail;
}

//CREATE - ADD METHOD
Subject* Course::createNewSubject(string IDS_, string name_, string CT, int unit, int limit)
{
	Subject* nSub = new Subject[1];
	nSub->setIDS(IDS_);
	nSub->setName(name_);
	nSub->setClassTeacher(CT);
	nSub->setUnits(unit);
	nSub->setLimit(limit);
	/*nSub->setBegin_Date(BD);
	nSub->setEnd_Date(ED);*/
	nSub->setNextSubject(NULL);
	return nSub;
}
void Course::addNewSubject(int n)
{
	string IDS_, name_, CT;
	int unit, limit;
	for (int i = 1; i <= n; i++)
	{
		system("cls");
		cout << "\t\t=============INPUT SUBJECT No." << i << "=================\n";
		do
		{
			cout << "Input Subject ID: "; getline(cin, IDS_);
			if (checkIDS(IDS_) == false)
			{
				cout << "Error ID! Please type another ID!\n";
			}
		} while (checkIDS(IDS_) == false);

		do
		{
			cout << "Input Subject's Name: "; getline(cin, name_);
			if (checkName(name_) == false)
			{
				cout << "Error ID! Please type another ID!\n";
			}
		} while (checkName(name_) == false);

		cout << "Input Class Teacher: "; getline(cin, CT);

		do {
			cout << "Input Number Of Unit (Only accept from 1 to 15 Units): "; cin >> unit;
			if (checkUnit(unit) == false)
				cout << "Invalid Unit! Please type again!\n";
		} while (checkUnit(unit) == false);

		do {
			cout << "Input Max NumberStudent: "; cin >> limit;
			if (checkLimit(limit) == false)
				cout << "Invalid Input! Please type again!\n";
		} while (checkLimit(limit) == false);
		cin.ignore();


		Subject* nSub = createNewSubject(IDS_, name_, CT, unit, limit);
		if (head == NULL)
			head = tail = nSub;
		else
		{
			tail->setNextSubject(nSub);
			tail = nSub;
		}

	}
}

//MODIFY METHODS
Subject* Course::GetSubjectWithID(string ID_)
{
	int count = 0;
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
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
	return NULL;
}
void Course::Modified_All_InFormation_With_IDS_COURSE(string IDS_)
{
	string name_, CT;
	int unit, limit;

	Subject* nSub = GetSubjectWithID(IDS_);

	if (nSub == NULL)
	{
		return;
	}
	system("cls");

	cout << "\t\t=============MODIFIED SUBJECT No." << IDS_ << "================ = \n";
	do
	{
		cout << "Input New Subject ID: "; getline(cin, IDS_);
		if (checkIDS(IDS_) == false)
		{
			cout << "Error ID! Please type another ID!\n";
		}
		else
		{
			cout << "Valid ID!\n";
			nSub->setIDS(IDS_);
			break;
		}
	} while (checkIDS(IDS_) == false);

	cout << "Input New Subject Name: "; getline(cin, name_); nSub->setName(name_);
	cout << "Input New Teacher's Name: "; getline(cin, CT); nSub->setClassTeacher(CT);
	do {
		cout << "Input New Number Of Unit (Only accept from 1 to 4 Units): "; cin >> unit;
		if (checkUnit(unit) == false) { cout << "Invalid Unit! Please type again!\n"; }
		else
		{
			cout << "Valid Unit!\n";
			this->Total_Unit = this->Total_Unit + unit - nSub->getUnit();
			nSub->setUnits(unit);
			break;
		}
	} while (checkUnit(unit) == false);

	do {
		cout << "Input New Max Student: "; cin >> limit;
		if (checkLimit(limit) == false) { cout << "Invalid Input! Please type again! (Max is 300 Students)\n"; }
		else
		{
			cout << "Valid Limit!\n";
			nSub->setLimit(limit);
			break;
		}
	} while (checkLimit(limit) == false);

}
void Course::Modified_With_IDS(string id)
{
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
	{
		if (k->getIDS() == id)
		{
			string IDS_;
			do
			{
				cout << "Input New Subject ID: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					cout << "Error ID! Please type another ID!\n";
				}
				else
				{
					cout << "Valid ID!\n";
					k->setIDS(IDS_);
					break;
				}
			} while (checkIDS(IDS_) == false);

		}
	}
	cout << "\nNot Found ID";
}
void Course::Modified_With_Name(string id)
{
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
	{
		if (k->getIDS() == id)
		{
			string name;
			do
			{
				cout << "Input New Name: "; getline(cin, name);
				if (checkName(name) == false)
				{
					cout << "Error ID! Please type another ID!\n";
				}
				else
				{
					cout << "Valid ID!\n";
					k->setName(name);
					break;
				}
			} while (checkName(name) == false);
		}
	}
}
void Course::Modified_With_Teacher_Name(string id)
{
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
	{
		if (k->getIDS() == id)
		{
			string newname;
			cout << "Input New Teacher's Name: ";
			getline(cin, newname);
			k->setClassTeacher(newname);
		}
	}
}
void Course::Modified_With_Units(string id)
{
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
	{
		if (k->getIDS() == id)
		{
			int unit;
			do {
				cout << "Input New Number Of Unit (Only accept from 1 to 4 Units): "; cin >> unit;
				if (checkUnit(unit) == false) { cout << "Invalid Unit! Please type again!\n"; }
				else
				{
					k->setUnits(unit);
					break;
				}
			} while (checkUnit(unit) == false);
		}
	}
}
void Course::Modified_With_Limit(string id)
{
	for (Subject* k = head; k != NULL; k = k->getNextSubject())
	{
		if (k->getIDS() == id)
		{
			int limit;
			do {
				cout << "Input New Max Student: "; cin >> limit;
				if (checkLimit(limit) == false) { cout << "Invalid Input! Please type again! (Max is 300 Students)\n"; }
				else
				{
					k->setLimit(limit);
					break;
				}
			} while (checkLimit(limit) == false);
		}
	}
}
void Course::Menu_Modified()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\t\t=======================MODIFIED MENU=======================\n";
		cout << "\t1. Modified Subject with matches IDS\n";
		cout << "\t2. Modified IDS with matches IDS\n";
		cout << "\t3. Modified Name with matches IDS\n";
		cout << "\t4. Modified Teacher's Name with matches IDS\n";
		cout << "\t5. Modified Units with matches IDS\n";
		cout << "\t6. Modified Limit with matches IDS\n";
		cout << "\t7. Display\n";
		cout << "\t0. Exit\n";
		cout << "\t\t============================END===========================";
		cout << "\nYour Selection: ";
		cin >> choice;

		if (choice < 0 || choice > 7)
		{
			cout << "\nInvalid Choice!\n";
			system("pause");
		}
		else if (choice == 1)
		{
			cin.ignore();
			//Modified_All_InFormation_With_IDS_COURSE();
			//system("cls");
			//display();
			//system("pause");
		}
		else if (choice == 2)
		{
			cin.ignore();
			string IDS_;
			do
			{
				cout << "Input ID Subject You Want To Modified: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					break;
				}
				else
					cout << "\nInvalid IDS.Please try again!\n\n";
			} while (checkIDS(IDS_) == true);
			Modified_With_IDS(IDS_);
			/*system("cls");
			display();
			system("pause");*/
		}
		else if (choice == 3)
		{
			cin.ignore();
			string IDS_;
			do
			{
				cout << "Input ID Subject You Want To Modified: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					break;
				}
				else
					cout << "\nInvalid IDS.Please try again!\n\n";
			} while (checkIDS(IDS_) == true);
			Modified_With_Name(IDS_);
			/*system("cls");
			display();
			system("pause");*/
		}
		else if (choice == 4)
		{
			cin.ignore();
			string IDS_;
			do
			{
				cout << "Input ID Subject You Want To Modified: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					break;
				}
				else
					cout << "\nInvalid IDS.Please try again!\n\n";
			} while (checkIDS(IDS_) == true);
			Modified_With_Teacher_Name(IDS_);
			/*	system("cls");
				display();
				system("pause");*/
		}
		else if (choice == 5)
		{
			string IDS_;
			cin.ignore();
			do
			{
				cout << "Input ID Subject You Want To Modified: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					break;
				}
				else
					cout << "\nInvalid IDS.Please try again!\n\n";
			} while (checkIDS(IDS_) == true);
			Modified_With_Units(IDS_);
			/*system("cls");
			display();
			system("pause");*/
		}
		else if (choice == 6)
		{
			string IDS_;
			cin.ignore();
			do
			{
				cout << "Input ID Subject You Want To Modified: "; getline(cin, IDS_);
				if (checkIDS(IDS_) == false)
				{
					break;
				}
				else
					cout << "\nInvalid IDS.Please try again!\n\n";
			} while (checkIDS(IDS_) == true);
			Modified_With_Limit(IDS_);
			/*system("cls");
			display();
			system("pause");*/
		}
		else if (choice == 7)
		{
			//DISplay
			DISPLAY();
			system("pause");
		}
		else
		{
			break;
		}

	}
}

//DELETE METHODS
void Course::Delete_With_IDS(string ID_)
{
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Subject* i = head; i->getNextSubject() != NULL; )
		{
			if (i->getNextSubject()->getIDS() == ID_)
			{
				Subject* h = i->getNextSubject();
				if (h == tail)
				{
					tail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
				return;
			}
			else
			{
				i = i->getNextSubject();
			}
		}
	}
	if (head->getIDS() == ID_)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
		return;
	}
}
void Course::Delete_With_Name(string name)
{
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Subject* i = head; i->getNextSubject() != NULL; )
		{
			if (i->getNextSubject()->getName() == name)
			{
				Subject* h = i->getNextSubject();
				if (h == tail)
				{
					tail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
			}
			else
			{
				i = i->getNextSubject();
			}
		}
	}
	if (head->getName() == name)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
		return;
	}
}
void Course::Delete_With_Teacher_Name(string tname)
{
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Subject* i = head; i->getNextSubject() != NULL; )
		{
			if (i->getNextSubject()->getClassTeacher() == tname)
			{
				Subject* h = i->getNextSubject();
				if (h == tail)
				{
					tail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
			}
			else
			{
				i = i->getNextSubject();
			}
		}
	}
	if (head->getClassTeacher() == tname)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
		return;
	}
}
void Course::Delete_With_Units(int unit)
{
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Subject* i = head; i->getNextSubject() != NULL; )
		{
			if (i->getNextSubject()->getUnit() == unit)
			{
				Subject* h = i->getNextSubject();
				if (h == tail)
				{
					tail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
			}
			else
			{
				i = i->getNextSubject();
			}
		}
	}
	if (head->getUnit() == unit)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
		return;
	}
}
void Course::Delete_With_Limit(int limit)
{
	if (head == NULL)
	{
		cout << "\nList is Empty!";
		system("pause");
		return;
	}
	else
	{
		for (Subject* i = head; i->getNextSubject() != NULL; )
		{
			if (i->getNextSubject()->getLimit() == limit)
			{
				Subject* h = i->getNextSubject();
				if (h == tail)
				{
					tail = i;
				}
				i->setNextSubject(h->getNextSubject());
				delete[] h;
			}
			else
			{
				i = i->getNextSubject();
			}
		}
	}
	if (head->getLimit() == limit)
	{
		if (tail == head)
		{
			tail = NULL;
		}
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
		return;
	}
}
void Course::Delete_All()
{
	while (head != NULL)
	{
		Subject* p = head;
		head = head->getNextSubject();
		delete[] p;
	}
}
void Course::Menu_Delete()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\t\t===========================\2MENU_DELETE\2==================";
		cout << "\n\t\t1.Delete With IDS";
		cout << "\n\t\t2.Delete With Name";
		cout << "\n\t\t3.Delete With Teacher's Name";
		cout << "\n\t\t4.Delete With Unit";
		cout << "\n\t\t5.Delete With Limit";
		cout << "\n\t\t6.Delete All";
		cout << "\n\t\t7.Display";
		cout << "\n\t\t0.Exit";
		cout << "\n\t\t==============================END======================";

		cout << "\nEnter Choice: ";
		cin >> choice;

		if (choice < 0 || choice > 7)
		{
			cout << "\nInvalid Choice!\n";
			system("pause");
		}
		else if (choice == 1)
		{
			cin.ignore();
			string ID_;
			cout << "Enter the \"IDS\" you want to delete: ";
			getline(cin, ID_);
			Delete_With_IDS(ID_);
		}
		else if (choice == 2)
		{
			cin.ignore();
			string Fullname_;
			cout << "Enter the \"Name\" you want to delete: ";
			getline(cin, Fullname_);
			Delete_With_Name(Fullname_);
		}
		else if (choice == 3)
		{
			cin.ignore();
			string Firstname_;
			cout << "Enter the \"Teacher's Name\" you want to delete: ";
			getline(cin, Firstname_);
			Delete_With_Teacher_Name(Firstname_);
		}
		else if (choice == 4)
		{
			int unit;
			do {
				cout << "Input Number Of Unit (Only accept from 1 to 4 Units): "; cin >> unit;
				if (checkUnit(unit) == false)
					cout << "Invalid Unit! Please type again!\n";
			} while (checkUnit(unit) == false);
			Delete_With_Units(unit);
		}
		else if (choice == 5)
		{
			int limit;
			do {
				cout << "Input Max NumberStudent: "; cin >> limit;
				if (checkLimit(limit) == false)
					cout << "Invalid Input! Please type again!\n";
			} while (checkLimit(limit) == false);
			Delete_With_Limit(limit);
		}
		else if (choice == 6)
			Delete_All();
		else if (choice == 7)
		{
			DISPLAY();
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//SEARCH METHODS
Subject* Course::findSubject(string IDfind)
{
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getIDS() == IDfind) return i;
	}
	return NULL;
}
void Course::Search_With_IDS(string ID_)
{
	cout << "\n\n\t\t==============INFORMATION SUBJECT================\n\n";
	cout << setw(20) << left << "Sub ID" << setw(20) << left << "Sub Name" << setw(20) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
	int count = 0;
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getIDS() == ID_)
		{
			cout << setw(20) << left << i->getIDS() << setw(20) << left << i->getName() << setw(20) << left << i->getClassTeacher() << setw(10) << left << i->getUnit() << setw(5) << left << i->getLimit() << endl;
			count++;
			return;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nSubject not found!\n";
	}
}
void Course::Search_With_Name(string name)
{
	cout << "\n\n\t\t==============INFORMATION SUBJECT================\n\n";
	cout << setw(20) << left << "Sub ID" << setw(20) << left << "Sub Name" << setw(20) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
	int count = 0;
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getName() == name)
		{
			cout << setw(20) << left << i->getIDS() << setw(20) << left << i->getName() << setw(20) << left << i->getClassTeacher() << setw(10) << left << i->getUnit() << setw(5) << left << i->getLimit() << endl;
			count++;
			return;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nSubject not found!\n";
	}
}
void Course::Search_With_Teacher_Name(string Tname)
{
	cout << "\n\n\t\t==============INFORMATION SUBJECT================\n\n";
	cout << setw(20) << left << "Sub ID" << setw(20) << left << "Sub Name" << setw(20) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
	int count = 0;
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getClassTeacher() == Tname)
		{
			cout << setw(20) << left << i->getIDS() << setw(20) << left << i->getName() << setw(20) << left << i->getClassTeacher() << setw(10) << left << i->getUnit() << setw(5) << left << i->getLimit() << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nSubject not found!\n";
	}
}
void Course::Search_With_Units(int unit)
{
	cout << "\n\n\t\t==============INFORMATION SUBJECT================\n\n";
	cout << setw(20) << left << "Sub ID" << setw(20) << left << "Sub Name" << setw(20) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
	int count = 0;
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getUnit() == unit)
		{
			cout << setw(20) << left << i->getIDS() << setw(20) << left << i->getName() << setw(20) << left << i->getClassTeacher() << setw(10) << left << i->getUnit() << setw(5) << left << i->getLimit() << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nSubject not found!\n";
	}
}
void Course::Search_With_Limit(int limit)
{
	int count = 0;
	cout << "\n\n\t\t==============INFORMATION SUBJECT================\n\n";
	cout << setw(20) << left << "Sub ID" << setw(20) << left << "Sub Name" << setw(20) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
	for (Subject* i = head; i != NULL; i = i->getNextSubject())
	{
		if (i->getLimit() == limit)
		{
			cout << setw(20) << left << i->getIDS() << setw(20) << left << i->getName() << setw(20) << left << i->getClassTeacher() << setw(10) << left << i->getUnit() << setw(5) << left << i->getLimit() << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nSubject not found!\n";
	}
}
void Course::Menu_Search()
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
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 1. Search With IDS" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 2. Search With Name" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 3. Search With Teacher's Name" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 4. Search With Units" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 5. Search With Limit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 6. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 50; i++)
			cout << char(205);
		cout << char(188);

		cursorx(*&select, 4, 9, 6, 98);

		if (select == 1)
		{
			//cin.ignore();
			string ID_;
			cout << "\n\n\n\n\n\n\nEnter the \"IDS\" you want to find: ";
			getline(cin, ID_);
			system("cls");
			Search_With_IDS(ID_);
			system("pause");
		}
		else if (select == 2)
		{
			//cin.ignore();
			string Fullname_;
			cout << "\n\n\n\n\n\nEnter the \"Name\" you want to find: ";
			getline(cin, Fullname_);
			system("cls");
			Search_With_Name(Fullname_);
			system("pause");
		}
		else if (select == 3)
		{
			//cin.ignore();
			string Firstname_;
			cout << "\n\n\n\n\nEnter the \"Teacher's Name\" you want to find: ";
			getline(cin, Firstname_);
			system("cls");
			Search_With_Teacher_Name(Firstname_);
			system("pause");
		}
		else if (select == 4)
		{
			int unit;
			cout << "\n\n\n\n";
			do {
				cout << "Input Number Of Unit (Only accept from 1 to 10 Units): "; cin >> unit;
				if (checkUnit(unit) == false)
					cout << "Invalid Unit! Please type again!\n";
			} while (checkUnit(unit) == false);
			system("cls");
			Search_With_Units(unit);
			system("pause");
		}
		else if (select == 5)
		{
			int limit;
			cout << "\n\n\n";
			do {
				cout << "Input Max NumberStudent: "; cin >> limit;
				if (checkLimit(limit) == false)
					cout << "Invalid Input! Please type again!\n";
			} while (checkLimit(limit) == false);
			system("cls");
			Search_With_Limit(limit);
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//SORT METHODS
void Course::Swap(Subject*& x, Subject*& y)
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
void Course::Sort_With_IDS()
{
	for (Subject* k = head; k->getNextSubject() != NULL; k = k->getNextSubject())
	{
		for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
		{
			if ((k->getIDS()) > (h->getIDS()))
			{
				Swap(k, h);
			}
		}
	}
}
void Course::Sort_With_Name()
{
	for (Subject* k = head; k->getNextSubject() != NULL; k = k->getNextSubject())
	{
		for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
		{
			if ((k->getName()) > (h->getName()))
			{
				Swap(k, h);
			}
		}
	}
}
void Course::Sort_With_Teacher_Name()
{
	for (Subject* k = head; k->getNextSubject() != NULL; k = k->getNextSubject())
	{
		for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
		{
			if ((k->getClassTeacher()) > (h->getClassTeacher()))
			{
				Swap(k, h);
			}
		}
	}
}
void Course::Sort_With_Unit()
{
	for (Subject* k = head; k->getNextSubject() != NULL; k = k->getNextSubject())
	{
		for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
		{
			if ((k->getUnit()) > (h->getUnit()))
			{
				Swap(k, h);
			}
		}
	}
}
void Course::Sort_With_Limit()
{
	for (Subject* k = head; k->getNextSubject() != NULL; k = k->getNextSubject())
	{
		for (Subject* h = k->getNextSubject(); h != NULL; h = h->getNextSubject())
		{
			if ((k->getLimit()) > (h->getLimit()))
			{
				Swap(k, h);
			}
		}
	}
}
void Course::Menu_Sort()
{
	//iomanip lai
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t======================MENU SORT===================";
		cout << "\n\t\t1.Sort by IDS";
		cout << "\n\t\t2.Sort by Name";
		cout << "\n\t\t3.Sort by Teacher's Name";
		cout << "\n\t\t4.Sort by Units";
		cout << "\n\t\t5.Sort by Limit";
		cout << "\n\t\t6.Display";
		cout << "\n\t\t0.Exit";
		cout << "\n\t\t===================================================";


		cout << "\nEnter choice: ";
		cin >> choice;

		if (choice < 0 || choice > 6)
		{
			cout << "Invalid choice!";
			system("pause");
		}
		else if (choice == 1)
		{
			Sort_With_IDS();
			cout << "Sorted Successfully!\n";
			system("pause");
		}
		else if (choice == 2)
		{
			Sort_With_Name();
			cout << "Sorted Successfully!\n";
			system("pause");
		}
		else if (choice == 3)
		{
			Sort_With_Teacher_Name();
			cout << "Sorted Successfully!\n";
			system("pause");
		}
		else if (choice == 4)
		{
			Sort_With_Unit();
			cout << "Sorted Successfully!\n";
			system("pause");
		}
		else if (choice == 5)
		{
			Sort_With_Limit();
			cout << "Sorted Successfully!\n";
			system("pause");
		}
		else if (choice == 6)
		{
			DISPLAY();
			system("pause");
		}
		else
		{
			break;
		}
	}
}

//DISPLAY METHOD
void Course::DISPLAY()
{
	if (head == NULL)
	{
		cout << "\nLIST IS EMPTY\n";
		return;
	}
	cout << endl;
	cout << "\t\t" << setw(69) << left << "";
	for (int i = 1; i <= 11; i++)
		cout << char(205);
	cout << "INFORMATION SUBJECT";
	for (int i = 1; i <= 10; i++)
		cout << char(205);

	cout << "\n\n\t\t\t" << char(218);
	for (int i = 2; i <= 150; i++)
	{
		if (i == 27 || i == 63 || i == 99 || i == 125)
			cout << char(194);
		else
			cout << char(196);
	}
	cout << char(191);


	cout << "\n\t\t\t" << char(179) << setw(25) << left << "         Sub ID" << char(179) << setw(35) << left << "             Sub Name" << char(179) << setw(35) << left << "          Teacher's Name" << char(179) << setw(25) << left << "         Units"
		<< char(179) << setw(25) << left << "           Limit" << char(179) << endl;


	cout << "\t\t\t" << char(195);
	for (int i = 2; i <= 150; i++)
	{
		if (i == 27 || i == 63 || i == 99 || i == 125)
			cout << char(197);
		else
			cout << char(196);
	}
	cout << char(180);


	for (Subject* p = head; p != NULL; p = p->getNextSubject())
	{
		cout << "\n\t\t\t" << char(179) << setw(10) << left << "" << setw(15) << left << p->getIDS() << char(179) << setw(3) << left << "" << setw(32) << left << p->getName() << char(179) << setw(3) << left << "" << setw(32) << left << p->getClassTeacher() << char(179) << setw(11) << left << "" << setw(14) << left << p->getUnit() << char(179) << setw(11) << left << ""
			<< setw(14) << left << p->getLimit() << char(179) << endl;

		if (p == tail)
		{
			cout << "\t\t\t" << char(192);
			for (int i = 2; i <= 150; i++)
			{
				if (i == 27 || i == 63 || i == 99 || i == 125)
					cout << char(193);
				else
					cout << char(196);
			}
			cout << char(217);
		}
		else
		{
			cout << "\t\t\t" << char(195);
			for (int i = 2; i <= 150; i++)
			{
				if (i == 27 || i == 63 || i == 99 || i == 125)
					cout << char(197);
				else
					cout << char(196);
			}
			cout << char(180);
		}
	}
	cout << endl << endl;
}

//FILE INTERACTION
void Course::Export_to_file(fstream& Export)
{
	if (head == NULL)
	{
		Export << "\nLIST IS EMPTY\n";
		return;
	}
	else
	{
		Export.open("BAITAPLONEXPORTSUBLIST.txt", ios::out);
		if (!Export) Export << "Cannot open file!";

		Export << "\n\n\t\t\t\t\t\t\t\t\t\t==============INFORMATION SUBJECT================\n\n";
		Export << "\t\t\t\t\t\t" << setw(20) << left << "Sub ID" << setw(40) << left << "Sub Name" << setw(30) << left << "Teacher's Name" << setw(10) << left << "Units" << setw(5) << left << "Limit" << endl;
		for (Subject* p = head; p != NULL; p = p->getNextSubject())
		{
			Export << "\t\t\t\t\t\t" << setw(20) << left << p->getIDS() << setw(40) << left << p->getName() << setw(30) << left << p->getClassTeacher() << setw(10) << left << p->getUnit() << setw(5) << left << p->getLimit() << endl;
		}
	}
	Export.close();
}