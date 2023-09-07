#include "AdList.h"

#include <iostream>
#include <iomanip>

#include <conio.h>
#include <Windows.h>
using namespace std;

void textcolorrrr(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void gotoxyrrrr(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int cursorrrr(int& select, int minH, int maxH, int maxSe, int posCur)
{
	char x;
	int y = minH;
	gotoxyrrrr(posCur, y);
	textcolorrrr(12);
	cout << char(17);
	textcolorrrr(7);
	gotoxyrrrr(0, 0);

	gotoxyrrrr(posCur, y);
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
				gotoxyrrrr(posCur, y);
				cout << "  ";
				y = minH;
				gotoxyrrrr(posCur, y);
				textcolorrrr(12);
				cout << char(17);
				textcolorrrr(7);
				select = 1;
			}
			else
			{
				gotoxyrrrr(posCur, y);
				cout << "  ";
				gotoxyrrrr(posCur, y += 1);
				textcolorrrr(12);
				cout << char(17);
				textcolorrrr(7);
				select++;
			}
		}
		if (x == 72) //UP
		{
			if (y == minH)
			{
				gotoxyrrrr(posCur, y);
				cout << "  ";
				y = maxH;
				gotoxyrrrr(posCur, y);
				textcolorrrr(12);
				cout << char(17);
				textcolorrrr(7);
				select = maxSe;
			}
			else
			{
				gotoxyrrrr(posCur, y);
				cout << "  ";
				gotoxyrrrr(posCur, y -= 1);
				textcolorrrr(12);
				cout << char(17);
				textcolorrrr(7);
				select--;
			}
		}
	}
	return select;
}

//DEFFAULT CONSTRUCTOR
AdList::AdList()
{
	head = tail = NULL;
}

//SET METHODS
void AdList::setHead(Admin* newHead)
{
	this->head = newHead;
}
void AdList::setTail(Admin* newTail)
{
	this->tail = newTail;
}

//GET METHODS
Admin* AdList::getHead()
{
	return head;
}
Admin* AdList::getTail()
{
	return tail;
}
Admin* AdList::GetAdminWithID(string ID_)
{
	Admin* temp;
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
		cout << "\nAdmin Not Found!\n";
		system("pause");
		return NULL;
	}
	return NULL;
}

//CHECK METHODS
bool AdList::checkID(string ID)
{
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID) { return 0; }
	}
	return 1;
}
bool AdList::checkGender(int gender)
{
	if (gender != 0 && gender != 1) return 0;
	return 1;
}
bool AdList::checkDate(int day, int month, int year)
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
bool AdList::login(string id, string password)
{
	for (Admin* i = head; i != NULL; i = i->getNext()) if (i->getID() == id && i->getPassword() == password) return 1;
	return 0;
}

//CREATE - ADD METHOD
Admin* AdList::createNewAdmin(string ID, string firstName, string lastName, string address, int gender, Date DateOfBirth, Date AdmissionDate, string password)
{
	Admin* newAdmin = new Admin[1];
	newAdmin->setID(ID);
	newAdmin->setfirstName(firstName);
	newAdmin->setlastName(lastName);
	newAdmin->setGender(gender);
	newAdmin->setAddress(address);
	newAdmin->setDateOfBirth(DateOfBirth);
	newAdmin->setAdmissionDate(AdmissionDate);
	newAdmin->setNext(NULL);
	newAdmin->setPassword(password);
	return newAdmin;
}
void AdList::addNewAdmin(int n)
{
	string ID, firstName, lastName, address, password;
	int gender_choice;
	for (int i = 1; i <= n; i++)
	{
		system("cls");
		cout << "-----INPUT INFORMATION FOR ADMIN No." << i << "-----" << endl;
		cout << "Create password: ";
		getline(cin, password);
		do
		{
			cout << "ID: ";
			getline(cin, ID);
			if (checkID(ID) == 0) cout << "Duplicated ID! Please try again!" << endl;
		} while (checkID(ID) == 0);
		cout << "First name: "; getline(cin, firstName);
		cout << "Last name: "; getline(cin, lastName);
		do
		{
			cout << "Gender:\n0. Male\n1.Female\n-->"; cin >> gender_choice;
			if (checkGender(gender_choice) == 0) cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl;
		} while (checkGender(gender_choice) == 0);
		cin.ignore();
		cout << "Address: "; getline(cin, address);
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
		cout << "\nInput Date Start Work\n";
		int day_;
		cout << "Day Of DSW: ";
		cin >> day_;
		int month_;
		cout << "Month Of DSW: ";
		cin >> month_;
		int year_;
		cout << "Year Of DSW: ";
		cin >> year_;
		Date AdmissionDate(day_, month_, year_);
		cin.ignore();

		Admin* newAdmin = createNewAdmin(ID, firstName, lastName, address, gender_choice, DateOfBirth, AdmissionDate, password);
		if (head == NULL) head = tail = newAdmin;
		else
		{
			tail->setNext(newAdmin);
			tail = newAdmin;
		}
	}
}

//SEARCH METHODS
void AdList::Search_With_ID(string ID_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getID() == ID_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
			return;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_Firstname(string Firstname_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getfirstName() == Firstname_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_Fullname(string Fullname_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		string fullname = i->getlastName() + " " + i->getfirstName();
		if (fullname == Fullname_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_Gender(int gender_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getGender_() == gender_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_Address(string Address_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getAddress() == Address_)
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_DateOfBirth(Date DateOfBirth_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		if (i->getDateOfBirth().getDay() == DateOfBirth_.getDay() && i->getDateOfBirth().getMonth() == DateOfBirth_.getMonth() && i->getDateOfBirth().getYear() == DateOfBirth_.getYear())
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");

		cout << "\nAdmin not found!\n";
	}
}
void AdList::Search_With_AdmissionDate(Date AdmissionDate_)
{
	cout << "\n\n\t\t\t===============\2INFORMATION ADMIN\2================\n\n";
	cout << setw(15) << left << "ID" << setw(25) << left << "Fullname" << setw(15) << left << "Gender" << setw(20) << left << "Address" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "Date Start Work" << endl;
	int count = 0;
	for (Admin* i = head; i != NULL; i = i->getNext())
	{

		if (i->getAdmissionDate().getDay() == AdmissionDate_.getDay() && i->getAdmissionDate().getMonth() == AdmissionDate_.getMonth() && i->getAdmissionDate().getYear() == AdmissionDate_.getYear())
		{
			cout << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(15) << left << i->getGenderr() << setw(20) << left << i->getAddress();
			i->getDateOfBirth().Display();
			cout << setw(15) << left << "";
			i->getAdmissionDate().Display();
			cout << endl;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		cout << "\nAdmin not found!\n";
	}
}
void AdList::Menu_Search()
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
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 1. Search With ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 2. Search With Fullname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 3. Search With Firstname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 4. Search With Gender" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 5. Search With Address" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 6. Search With Date Of Birth" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 7. Search With Date Start Work" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 8. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 50; i++)
			cout << char(205);
		cout << char(188);

		cursorrrr(*&select, 4, 11, 8, 98);

		if (select == 1)
		{
			//cin.ignore();
			string ID_;
			cout << "\n\n\n\n\n\n\n\n\nEnter the \"ID\" you want to find: ";
			getline(cin, ID_);
			system("cls");
			Search_With_ID(ID_);
			system("pause");
		}
		else if (select == 2)
		{
			//cin.ignore();
			string Fullname_;
			cout << "\n\n\n\n\n\n\n\nEnter the \"fullname\" you want to find: ";
			getline(cin, Fullname_);
			system("cls");
			Search_With_Fullname(Fullname_);
			system("pause");
		}
		else if (select == 3)
		{
			//cin.ignore();
			string Firstname_;
			cout << "\n\n\n\n\n\n\nEnter the \"firstname\" you want to find: ";
			getline(cin, Firstname_);
			system("cls");
			Search_With_Firstname(Firstname_);
			system("pause");
		}
		else if (select == 4)
		{
			int gender_;
			cout << "\n\n\n\n\n\nEnter the \"gender\" you want to find\n";

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
			cout << "\n\n\n\n\nEnter the \"address\" you want to find: ";
			getline(cin, Address_);
			system("cls");
			Search_With_Address(Address_);
			system("pause");
		}
		else if (select == 6)
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
		else if (select == 7)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\nEnter Day Of DSW: ";
			cin >> day;
			cout << "Enter Month Of DSW: ";
			cin >> month;
			cout << "Enter Year Of DSW: ";
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

//MODIFIED METHODS
void AdList::Modified_AdminWithID()
{
	string ID, firstName, lastName, address;
	int gender_choice, day, month, year;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Modified: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED INFORMATION FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
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

	cout << "\n\2Input New Date Of Birthday\2\n";
	//int day;
	cout << "Day Of BirthDay: ";
	cin >> day;
	//int month;
	cout << "Month Of BirthDay: ";
	cin >> month;
	//int year;
	cout << "Year Of BirthDay: ";
	cin >> year;
	Date DateOfBirth(day, month, year);
	selectedStudent->setDateOfBirth(DateOfBirth);

	cout << "\n\2Input New  Date Start Work\2\n";
	//int day;
	cout << "Day Of DSW: ";
	cin >> day;
	//int month;
	cout << "Month Of DSW: ";
	cin >> month;
	//int year;
	cout << "Year Of DSW: ";
	cin >> year;
	Date AdmissionDate(day, month, year);
	selectedStudent->setAdmissionDate(AdmissionDate);
	cout << "Done Changes!" << endl;
}
void AdList::Modified_IDWithID()
{
	string ID;
	cout << "\n\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED ID FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
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
void AdList::Modified_NameWithID()
{
	string firstName, lastName, ID;
	cout << "\n\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED NAME FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "New First name: "; getline(cin, firstName); selectedStudent->setfirstName(firstName);
	cout << "New Last name: "; getline(cin, lastName); selectedStudent->setlastName(lastName);
	cout << "Done Changes!" << endl;
}
void AdList::Modified_AddressWithID()
{
	string address, ID;
	cout << "\n\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED ADDRESS FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "New Address: "; getline(cin, address); selectedStudent->setAddress(address);
	cout << "Done Changes!" << endl;
}
void AdList::Modified_GenderWithID()
{
	int gender_choice;
	string ID;
	cout << "\n\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED GENDER FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
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
void AdList::Modified_DOBWithID()
{
	string ID;
	Date DOB;
	cout << "\n\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED DATE OF BIRTH FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
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
void AdList::Modified_ADWithID()
{
	string ID;
	Date AD;
	cout << "\n\n\n\n";
	do
	{
		cout << "Input ID You Want To Search: "; getline(cin, ID);
		if (checkID(ID) == 0) { break; }
		else { cout << "No Admin! Try Again!" << endl; }
	} while (checkID(ID) == 1);

	Admin* selectedStudent = GetAdminWithID(ID);
	if (selectedStudent == NULL)
	{
		return;
	}
	system("cls");
	cout << "-----MODIFIED DATE START WORK FOR ADMIN WITH ID: " << selectedStudent->getID() << "-----" << endl;
	cout << "\n\2Input  Of Date Start Work\2\n";
	int day;
	cout << "Day Of DSW: ";
	cin >> day;
	int month;
	cout << "Month Of DSW: ";
	cin >> month;
	int year;
	cout << "Year Of DSW: ";
	cin >> year;
	Date AdmissionDate(day, month, year);
	selectedStudent->setAdmissionDate(AdmissionDate);
	cout << "Done Changes!" << endl;

}
void AdList::Menu_Modifier()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(22) << left << "" << setw(36) << left << "MENU  MODIFIED" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Modified ALL with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Modified ID with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 3. Modified Name with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 4. Modified Address with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 5. Modified Gender with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 6. Modified Day Of Birth with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 7. Modified Date Start Work with matches ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 8. Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 9. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(188);

		cursorrrr(*&choice, 4, 12, 9, 106);

		if (choice == 1)
		{
			//cin.ignore();
			Modified_AdminWithID();
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
			Modified_GenderWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 6)
		{
			//cin.ignore();
			Modified_DOBWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 7)
		{
			//cin.ignore();
			Modified_ADWithID();
			system("cls");
			display();
			system("pause");
		}
		else if (choice == 8)
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
void AdList::Delete_With_ID(string ID_)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else if (head->getID() == ID_)
	{
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; i = i->getNext())
		{
			if (i->getNext()->getID() == ID_)
			{
				Admin* h = i->getNext();
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
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_Firstname(string firstname)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getfirstName() == firstname)
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_Fullname(string fullname)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			//string fullname_ = i->getNext()->getlastName() + " " + i->getNext()->getfirstName();
			if ((i->getNext()->getlastName() + " " + i->getNext()->getfirstName()) == fullname)
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_Gender(int gender)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getGender_() == gender)
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_Address(string address)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getAddress() == address)
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_DateOfBirth(Date dateofbirth)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getDateOfBirth().getDay() == dateofbirth.getDay() && i->getNext()->getDateOfBirth().getMonth() == dateofbirth.getMonth() && i->getNext()->getDateOfBirth().getYear() == dateofbirth.getYear())
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_With_AdmissionDate(Date Admissiondate)
{
	int count = 0;
	if (head == NULL)
	{
		cout << "\nList is Empty!\n";
		system("pause");
		return;
	}
	else
	{
		for (Admin* i = head; i->getNext() != NULL; )
		{
			if (i->getNext()->getAdmissionDate().getDay() == Admissiondate.getDay() && i->getNext()->getAdmissionDate().getMonth() == Admissiondate.getMonth() && i->getNext()->getAdmissionDate().getYear() == Admissiondate.getYear())
			{
				Admin* h = i->getNext();
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
		Admin* p = head;
		head = head->getNext();
		delete[] p;
		return;
	}
	if (count == 0)
	{
		cout << "\nCan't find Admin to delete!\n";
		system("pause");
	}
}
void AdList::Delete_All()
{
	while (head != NULL)
	{
		Admin* p = head;
		head = head->getNext();
		delete[] p;
	}
}
void AdList::Menu_Delete()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\t\t\t\t" << char(201);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(187);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(23) << left << "" << setw(35) << left << "MENU  DELETE" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Delete With ID" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Delete With Fullname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 3. Delete With Firstname" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 4. Delete With Gender" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 5. Delete With Address" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 6. Delete With Date Of Birth" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 7. Delete With Date Start Work" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 8. Delete All" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 9. Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 10.Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 58; i++)
			cout << char(205);
		cout << char(188);

		cursorrrr(*&choice, 4, 13, 10, 106);

		if (choice == 1)
		{
			//cin.ignore();
			string ID_;
			cout << "\n\n\n\n\n\n\n\n\n\n\nEnter the \"ID\" you want to delete: ";
			getline(cin, ID_);
			Delete_With_ID(ID_);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 2)
		{
			//cin.ignore();
			string Fullname_;
			cout << "\n\n\n\n\n\n\n\n\n\nEnter the \"fullname\" you want to delete: ";
			getline(cin, Fullname_);
			Delete_With_Fullname(Fullname_);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 3)
		{
			//cin.ignore();
			string Firstname_;
			cout << "\n\n\n\n\n\n\n\n\nEnter the \"firstname\" you want to delete: ";
			getline(cin, Firstname_);
			Delete_With_Firstname(Firstname_);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 4)
		{
			int gender_;
			cout << "\n\n\n\n\n\n\n\nEnter the \"gender\" you want to delete\n";

			do
			{
				cout << "Gender:\n0. Male\n1.Female\n-->"; cin >> gender_;
				if (checkGender(gender_) == 0) cout << "Error choice! Please try again! (Your choice must be 0 or 1)" << endl;
			} while (checkGender(gender_) == 0);
			Delete_With_Gender(gender_);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 5)
		{
			//cin.ignore();
			string Address_;
			cout << "\n\n\n\n\n\n\nEnter the \"address\" you want to delete: ";
			getline(cin, Address_);
			Delete_With_Address(Address_);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 6)
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
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 7)
		{
			Date date;
			int day, month, year;
			cout << "\n\n\n\n\nEnter Day Of DSW: ";
			cin >> day;
			cout << "Enter Month Of DSW: ";
			cin >> month;
			cout << "Enter Year Of DSW: ";
			cin >> year;
			date = Date(day, month, year);
			Delete_With_AdmissionDate(date);
			cout << "Deleted Successfully!\n";
			system("pause");
		}
		else if (choice == 8)
		{
			Delete_All();
			cout << "\n\n\n\nDeleted Successfully!\n";
			system("pause");
		}
		else if (choice == 9)
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
void AdList::Swap(Admin*& x, Admin*& y)
{
	string ID, firstname, lastname, address;
	int gender;
	Date DOB, AD;

	ID = x->getID();
	firstname = x->getfirstName();
	lastname = x->getlastName();
	address = x->getAddress();
	gender = x->getGender_();
	DOB = x->getDateOfBirth();
	AD = x->getAdmissionDate();

	x->setID(y->getID());
	x->setfirstName(y->getfirstName());
	x->setlastName(y->getlastName());
	x->setAddress(y->getAddress());
	x->setGender(y->getGender_());
	x->setDateOfBirth(y->getDateOfBirth());
	x->setAdmissionDate(y->getAdmissionDate());

	y->setID(ID);
	y->setfirstName(firstname);
	y->setlastName(lastname);
	y->setAddress(address);
	y->setGender(gender);
	y->setDateOfBirth(DOB);
	y->setAdmissionDate(AD);
}
void AdList::Sort_By_ID()
{
	for (Admin* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Admin* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getID()) > (h->getID()))
			{
				Swap(k, h);
			}
		}
	}
}
void AdList::Sort_By_Firstname()
{
	for (Admin* k = head; k->getNext() != NULL; k = k->getNext())
	{
		for (Admin* h = k->getNext(); h != NULL; h = h->getNext())
		{
			if ((k->getfirstName()) > (h->getfirstName()))
			{
				Swap(k, h);
			}
		}
	}
}
void AdList::Menu_Sort()
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
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 3. Display" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 4. Exit" << char(186);
		cout << "\n\t\t\t\t\t\t" << char(200);
		for (int i = 1; i <= 48; i++)
			cout << char(205);
		cout << char(188);

		cursorrrr(*&choice, 4, 7, 4, 96);

		if (choice == 1)
		{
			Sort_By_ID();
			cout << "\n\n\n\n\nSorted Successfully!\n";
			system("pause");
		}
		else if (choice == 2)
		{
			Sort_By_Firstname();
			cout << "\n\n\n\nSorted Successfully!\n";
			system("pause");

		}
		else if (choice == 3)
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

//MENU
void AdList::MENU()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\t\t\2 \2 \2 \2 \2 \2 \2 \2 \2 \2 \2MENU WORK WITH ADMIN INFORMATION\" \2 \2 \2 \2 \2 \2 \2 \2 \2";
		cout << "\n\t\t1.Add Admins to the list";
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
			int n;
			cout << "Enter the number of students: ";
			cin >> n;
			cin.ignore();
			addNewAdmin(n);
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

//DISPLAY METHODS
void AdList::display()
{
	if (head == NULL)
	{
		cout << "\nLIST IS EMPTY\n";
		return;
	}
	cout << endl;
	cout << setw(70) << left << "";
	for (int i = 1; i <= 10; i++)
		cout << char(205);
	cout << "INFORMATION ADMIN";
	for (int i = 1; i <= 10; i++)
		cout << char(205);

	cout << "\n\n\t" << char(218);
	for (int i = 2; i <= 156; i++)
	{
		if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131)
			cout << char(194);
		else
			cout << char(196);
	}
	cout << char(191);


	cout << "\n\t" << char(179) << setw(25) << left << "           ID" << char(179) << setw(25) << left << "         Fullname" << char(179) << setw(25) << left << "          Gender" << char(179) << setw(25) << left << "         Address"
		<< char(179) << setw(25) << left << "     Date Of Birthday" << char(179) << setw(25) << left << "      Date Start Work" << char(179) << endl;


	cout << "\t" << char(195);
	for (int i = 2; i <= 156; i++)
	{
		if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131)
			cout << char(197);
		else
			cout << char(196);
	}
	cout << char(180);


	for (Admin* i = head; i != NULL; i = i->getNext())
	{
		cout << "\n\t" << char(179) << setw(7) << left << "" << setw(18) << left << i->getID() << char(179) << setw(3) << left << "" << setw(22) << left << i->getlastName() + " " + i->getfirstName() << char(179) << setw(10) << left << "" << setw(15) << left << i->getGenderr() << char(179) << setw(9) << left << "" << setw(16) << left << i->getAddress() << char(179) << setw(7) << left << "";
		i->getDateOfBirth().Display();
		cout << setw(8) << left;
		cout << "";
		cout << char(179);
		cout << setw(8) << left << "";
		i->getAdmissionDate().Display();
		cout << setw(7) << left;
		cout << "";
		cout << char(179);
		cout << endl;

		if (i == tail)
		{
			cout << "\t" << char(192);
			for (int i = 2; i <= 156; i++)
			{
				if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131)
					cout << char(193);
				else
					cout << char(196);
			}
			cout << char(217);
		}
		else
		{
			cout << "\t" << char(195);
			for (int i = 2; i <= 156; i++)
			{
				if (i == 27 || i == 53 || i == 79 || i == 105 || i == 131)
					cout << char(197);
				else
					cout << char(196);
			}
			cout << char(180);
		}
	}
	cout << endl << endl;
}
void AdList::displayAccStd(StudentList std)
{
	cout << "\n\t\t\t\t\t\t\t---------ACCOUNT INFORMATION-------------\n\n";
	cout << "\t\t\t\t\t" << setw(20) << left << "Account's Name" << setw(20) << left << "Password" << endl;
	for (Student* i = std.getHead(); i != NULL; i = i->getNext())
	{
		cout << "\t\t\t\t\t" << setw(20) << left << i->getID() << setw(20) << left << i->getPassword() << endl;
	}
}

//FILE INTERACTION
void AdList::Export_to_file(fstream& Export)
{
	Export.open("BAITAPLONEXPORTAD.txt", ios::out);
	if (!Export) cout << "Cannot open file!";
	else
	{
		string day, month, year;
		Export << "\n\n\t\t\t\t\t\t\t\t\t===============INFORMATION ADMIN================\n\n";
		Export << "\t\t\t\t\t" << setw(15) << left << "Identifier" << setw(25) << left << "Fullname" << setw(10) << left << "Gender" << setw(15) << left << "Address" << setw(5) << left << "GPA" << setw(25) << left << "Date Of Birthday" << setw(25) << left << "AdmissionDate" << endl;
		for (Admin* i = head; i != NULL; i = i->getNext())
		{
			Export << "\t\t\t\t\t" << setw(15) << left << i->getID() << setw(25) << left << i->getlastName() + " " + i->getfirstName() << setw(10) << left << i->getGenderr() << setw(15) << left << i->getAddress();
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
			Export << i->getPassword();
			Export << endl;
		}
	}
	Export.close();
}