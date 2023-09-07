#include "Date.h"
#include "Course.h"
#include "Subject.h"
#include "Student.h"
#include "StudentList.h"
#include "Admin.h"
#include "AdList.h"
#include "DoHoa.h"

#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

int cursor(int &select, int minH, int maxH,int maxSe, int posCur)
{
	char x;
	int y = minH;
	gotoxy(posCur, y); 
	textcolor(12);
	cout << char(17);
	textcolor(7);
	gotoxy(0, 0);

	gotoxy(posCur, y);
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
				gotoxy(posCur, y);
				cout << "  ";
				y = minH;
				gotoxy(posCur, y);
				textcolor(12);
				cout << char(17);
				textcolor(7);
				select = 1;
			}
			else
			{
				gotoxy(posCur, y);
				cout << "  ";
				gotoxy(posCur, y += 1);
				textcolor(12);
				cout << char(17);
				textcolor(7);
				select++;
			}
		}
		if (x == 72) //UP
		{
			if (y == minH)
			{
				gotoxy(posCur, y);
				cout << "  ";
				y = maxH;
				gotoxy(posCur, y);
				textcolor(12);
				cout << char(17);
				textcolor(7);
				select = maxSe;
			}
			else
			{
				gotoxy(posCur, y);
				cout << "  ";
				gotoxy(posCur, y -= 1);
				textcolor(12);
				cout << char(17);
				textcolor(7);
				select--;
			}
		}
	}
	return select;
}

int main()
{
	StudentList std;
	AdList adm;
	Course c;
	fstream Import, Export;
	string username, password, hidepass;
	char x;

	Date deffDate;
	deffDate.setDay(1);
	deffDate.setMonth(1);
	deffDate.setYear(2000);
	Admin* deffAd = adm.createNewAdmin("admin", "MIN", "AD", "SYSTEM", 0, deffDate, deffDate, "123456789");
	adm.setHead(deffAd);
	adm.setTail(deffAd);


	offCursor(1);

	//goto test;

	system("cls");
	do
	{
	again:
		system("cls");
		cout << "\n\t\t\tWELCOME TO STUDENT MANAGEMENT PROJECT\n";
		cout << "\nInput your username and password:";
		int choice = 0;
		password = "";
		hidepass = "";

		cout << "\nUsername: "; getline(cin, username);
		cout << "Password: ";
		int num = 0;
		while (true)
		{
			char c = _getch(); 
			if (int(c) == 13) break;
			else if (int(c) == 8)
			{
				if (num == 0) continue;
				password.pop_back();
				hidepass.pop_back();
				gotoxy(11, 6);
				for (int i = 1; i <= num; i++) cout << " ";
				gotoxy(11, 6); 
				cout<< hidepass;
				num--;
			}
			else
			{
				num++;;
				password.push_back(c);
				hidepass.push_back('*');
				cout << "*";
			}
		}
		if (std.login(username, password) == 0 && adm.login(username, password) == 0)
		{
			cout << "\nIncorrect username or password! \n1. Try again!\n2. Exit\n";
			do
			{
				cout << "-->"; cin >> choice;
				if (choice != 1 && choice != 2) cout << "Error choice! Try again!\n";
			} while (choice != 1 && choice != 2);
			if (choice == 2) goto end;
			cin.ignore();
		}
	} while (std.login(username, password) == 0 && adm.login(username, password) == 0);

	if (std.login(username, password))
	{
		int select;
		while (true)
		{
			system("cls");

			cout << "\n\t\t\t\t\t\t" << char(201);
			for (int i = 1; i <= 34; i++)
				cout << char(205);
			cout << char(187);
			cout << "\n\t\t\t\t\t\t" << char(186);
			textcolor(2);
			cout << setw(10) << left << "" << setw(24) << left << "MENU  STUDENT";
			textcolor(7);
			cout << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 1. Display Account              " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 2. Display Information          " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 3. Display Subject              " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 4. Display All                  " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 5. Change Password              " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 6. Register One Subject         " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 7. Delete Subject               " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 8. Search Subject               " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(34) << left << " 9. Logout                       " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(200);
			for (int i = 1; i <= 34; i++) cout << char(205);
			cout << char(188);
			
			select = cursor(*&select, 4, 12, 9, 82);
			
			if (select == 1)
			{
				system("cls");
				std.display_account(username);
				system("pause");
			}
			else if (select == 2)
			{
				system("cls");
				std.display_(username);
				system("pause");
			}
			else if (select == 3)
			{
				system("cls");
				std.display_subjects_One_Student(username);
				system("pause");
			}
			else if (select == 4)
			{
				system("cls");
				std.display_(username);
				std.display_subjects_One_Student(username);
				system("pause");

			}
			else if (select == 5)
			{
				string newpass;
				cout << "\n\n\n\n\n\nNew Password: ";
				cin.ignore();
				getline(cin, newpass);
				for (Student* k = std.getHead(); k != NULL; k = k->getNext())
				{
					if (k->getID() == username)
					{
						k->setPassword(newpass);
						break;
					}
				}
				cout << "\n=================Changed Successfully==================\n";
				system("pause");
			}
			else if (select == 6)
			{
				system("cls");
				//cin.ignore();
				c.DISPLAY();
				cout << endl;
				string IDS_;
				int count = 0;
				int choice = 0;
				do
				{
					count = 0;
					cout << "\nInput ID Subject You Want To Add: "; getline(cin, IDS_);
					for (Student* k = std.getHead(); k != NULL; k = k->getNext())
					{
						if (k->getID() == username)
						{
							for (Subject* h = k->getSubList().getCourseHead(); h != NULL; h = h->getNextSubject())
							{
								if (h->getIDS() == IDS_)
								{
									count++;
									break;
								}
							}
						}
					}
					if (c.checkIDS(IDS_) == true || count != 0)
					{
						cout << "\nID Subject is not on the list or registered!\n1.Try again!\n2.Exit\n";
						do
						{
							cout << "-->"; cin >> choice;
							cin.ignore();
							if (choice != 1 && choice != 2) cout << "Error choice! Try again!\n";
						} while (choice != 1 && choice != 2);
						if (choice == 2)
							break;
					}
				} while (c.checkIDS(IDS_) == true || count != 0);
				if (choice != 2)
				{
					std.Add_Subject_For_Student(username, IDS_, c.getCourseHead());
					cout << endl;
					system("pause");
				}
			}
			else if (select == 7)
			{
				int choice = 0;
				system("cls");
				//cin.ignore();
				std.display_subjects_One_Student(username);
				cout << endl;
				bool flag = false;
				for (Student* k = std.getHead(); k != NULL; k = k->getNext())
				{
					if (k->getID() == username)
					{
						if (k->getSubList().getCourseHead() == NULL)
							flag = true;
					}
				}
				if (flag == true)
				{
					system("pause");
					continue;
				}
				string IDS_;
				int count = 0;
				do
				{
					cout << "\nInput ID Subject You Want To Delete: "; getline(cin, IDS_);
					for (Student* k = std.getHead(); k != NULL; k = k->getNext())
					{
						if (k->getID() == username)
						{
							for (Subject* h = k->getSubList().getCourseHead(); h != NULL; h = h->getNextSubject())
							{
								if (h->getIDS() == IDS_)
								{
									count++;
									break;
								}
							}
						}
					}

					if (count != 0)
					{
						break;
					}
					else
					{
						cout << "\nInvalid ID Subject!\n1.Try again!\n2.Exit\n";
						do
						{
							cout << "-->"; cin >> choice;
							cin.ignore();
							if (choice != 1 && choice != 2) cout << "Error choice! Try again!\n";
						} while (choice != 1 && choice != 2);
						if (choice == 2)
							break;
					}
				} while (count == 0);
				if (choice != 2)
				{
					std.Delete_Subject_For_Student(username, IDS_);
					cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
					system("pause");
				}
			}
			else if (select == 8)
			{
				//cin.ignore();
				string IDS_;
				do
				{
					cout << "\n\n\n\nInput ID Subject You Want To Search: "; getline(cin, IDS_);
					if (c.checkIDS(IDS_) == false)
					{
						break;
					}
					else
						cout << "\n===Invalid ID Subject!Please try again!===\n";
				} while (c.checkIDS(IDS_) == true);
				std.Search_Subject_For_Student(username, IDS_);
				system("pause");
			}
			else
			{
				//cin.ignore();
				goto again;
			}
		}
	}
	else
	{
		int choice;
		while (true)
		{
			system("cls");

			cout << "\n\t\t\t\t\t\t" << char(201);
			for (int i = 1; i <= 38; i++)
				cout << char(205);
			cout << char(187);
			cout << "\n\t\t\t\t\t\t" << char(186);
			textcolor(12);
			cout << setw(14) << left << "" << setw(24) << left << "MENU ADMIN";
			textcolor(7);
			cout << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(38) << left << " 1. Add                              " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(38) << left << " 2. Display                          " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(38) << left << " 3. Search                           " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(38) << left << " 4. Update                           " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(186) << setw(38) << left << " 5. Logout                           " << char(186);
			cout << "\n\t\t\t\t\t\t" << char(200);
			for (int i = 1; i <= 38; i++)
				cout << char(205);
			cout << char(188);

			cursor(*&choice, 4, 8, 5, 86);

			if (choice == 1)
			{
				int select;
				while (true)
				{
					system("cls");

					cout << "\n\t\t\t\t\t\t" << char(201);
					for (int i = 1; i <= 36; i++)
						cout << char(205);
					cout << char(187);
					cout << "\n\t\t\t\t\t\t" << char(186);
					textcolor(12);
					cout << setw(14) << left << "" << setw(22) << left << "MENU ADD";
					textcolor(7);
					cout << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(36) << left << " 1. Add New Subject               " << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(36) << left << " 2. Add New Student               " << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(36) << left << " 3. Add New Admin                 " << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(36) << left << " 4. Exit                          " << char(186);
					cout << "\n\t\t\t\t\t\t" << char(200);
					for (int i = 1; i <= 36; i++)
						cout << char(205);
					cout << char(188);
					
					cursor(*&select, 4, 7, 4, 84);

					if (select == 1)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(40) << left << "How would you like to add?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 1. Normal Add                                " << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 2. Import From File \"SubjectList.txt\"      " << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 3. Exit                                      " << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(188);					

							cursor(*&select, 4, 6, 3, 102);

							
							if (select == 1)
							{
								int n;
								cout << "\n\n\n\nEnter Number of Subjects: ";
								cin >> n;
								cin.ignore();
								system("cls");
								c.addNewSubject(n);
							}
							else if (select == 2)
							{
								Import.open("C:\__LAPTRINH__\BAITAPLONIMPORTSUB.txt", ios::in);
								char k;
								int count = 0;
								if (!Import) cout << "\n\n\nError file!";
								else
								{
									while (!Import.eof())
									{
										string IDS_, name_, CT;
										int unit, limit;

										getline(Import, IDS_, ',');
										if (c.checkIDS(IDS_) == false)
										{
											cout << "Error data! At -->IDS = " << IDS_ << " Duplicated IDS" << endl;
											break;
										}
										getline(Import, name_, ',');
										if (c.checkName(name_) == false)
										{
											cout << "Error data! At -->Name = " << name_ << " Duplicated SName" << endl;
											break;
										}
										getline(Import, CT, ',');
										Import >> unit;
										if (c.checkUnit(unit) == false)
										{
											cout << "Error data! At -->Unit = " << unit << " Invalid Unit" << endl;
											break;
										}
										Import >> limit;
										if (c.checkLimit(limit) == false)
										{
											cout << "Error data! At -->Limit = " << limit << " Invalid Limit" << endl;
											break;
										}

										Subject* nSub = c.createNewSubject(IDS_, name_, CT, unit, limit);
										if (c.getCourseHead() == NULL)
										{
											c.setCourseHead(nSub);
											c.setCourseTail(nSub);
										}
										else
										{
											c.getCourseTail()->setNextSubject(nSub);
											c.setCourseTail(nSub);

										}
										count++;
										Import.get(k);
									}
								}
								Import.close();
								cout << "\n\t\t============Insert successfully " << count << " subject(s)==============\n\n";
								system("pause");
							}
							else
							{
								break;
							}
						}
					}
					else if (select == 2)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(40) << left << "How would you like to add?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 1. Normal Add" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 2. Import From File \"StudentList.txt\"" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 102);

							if (select == 1)
							{
								int n;
								cout << "\n\n\n\nEnter Number of Students: ";
								cin >> n;
								cin.ignore();
								system("cls");
								std.addNewStudent(n, c.getCourseHead());
							}
							else if (select == 2)
							{
								Import.open("C:\__LAPTRINH__\BAITAPLONIMPORTSTD.txt", ios::in);
								char k;
								int count = 0;
								if (!Import) cout << "\n\n\nError file!";
								else
								{
									while (!Import.eof())
									{
										string ID, firstName, lastName, address, class_, password;
										int gender_choice;
										double GPA;

										getline(Import, ID, ',');
										if (std.checkID(ID) == 0)
										{
											cout << "Error data! At -->ID= " << ID << " Duplicated ID" << endl;
											break;
										}
										getline(Import, firstName, ',');
										getline(Import, lastName, ',');
										Import >> gender_choice;
										if (std.checkGender(gender_choice) == 0)
										{
											cout << "Error data! At -->Gender= " << gender_choice << " of ID=" << ID << " Your choice must be 0 or 1" << endl;
											break;
										}
										Import.get(k);
										getline(Import, address, ',');
										getline(Import, class_, ',');
										Import >> GPA;
										if (std.checkGPA(GPA) == 0)
										{
											cout << "Error data! At -->GPA= " << GPA << " of ID=" << ID << " GPA must be >= 0.0 or <= 10.0" << endl;
											break;
										}
										int day;
										Import >> day;
										int month;
										Import >> month;
										int year;
										Import >> year;
										if (std.checkDate(day, month, year) == 0)
										{
											cout << "Error data! At -->Date= " << day << "/" << month << "/" << year << " of ID=" << ID << " Date not exist!";
											break;
										}
										Date DateOfBirth(day, month, year);
										int day_;
										Import >> day_;
										int month_;
										Import >> month_;
										int year_;
										Import >> year_;
										if (std.checkDate(day_, month_, year_) == 0)
										{
											cout << "Error data! At -->Date= " << day_ << "/" << month_ << "/" << year_ << " of ID=" << ID << " Date not exist!";
											break;
										}
										Date AdmissionDate(day_, month_, year_);
										Import.get(k);
										getline(Import, password, ',');

										Course sublist_;
										string IDsub;
										int x;
										Import >> x;
										Import.get(k);
										if (x != 0)
										{
											//Import.get(k);
											for (int i = 1; i <= x; i++)
											{
												getline(Import, IDsub, ',');
												if (c.findSubject(IDsub) == NULL)
												{
													cout << "Invalid subject at IDsubject =" << IDsub << " of StudentID = " << ID;
													break;
												}
												else if (sublist_.checkIDS(IDsub) == 0)
												{
													cout << "Invalid subject at IDsubject =" << IDsub << " of StudentID = " << ID << " : Duplicated subject" << endl;
													goto end_dup;
												}
												else
												{
													Subject* result = c.findSubject(IDsub);
													Subject* newSub = sublist_.createNewSubject(IDsub, result->getName(), result->getClassTeacher(), result->getUnit(), result->getLimit());
													if (sublist_.getCourseHead() == NULL)
													{
														sublist_.setCourseHead(newSub);
														sublist_.setCourseTail(newSub);
													}
													else
													{
														sublist_.getCourseTail()->setNextSubject(newSub);
														sublist_.setCourseTail(newSub);
													}
													//Import.get(k);
												}
											}

											Import.get(k);
										}
										else
										{
											Import.get(k);
										}

										if ((c.findSubject(IDsub) == NULL && x != 0)) break;

										Student* newStudent = std.createNewStudent(ID, firstName, lastName, gender_choice, address, class_, GPA, DateOfBirth, AdmissionDate, password, sublist_);
										if (std.getHead() == NULL)
										{
											std.setHead(newStudent);
											std.setTail(newStudent);
										}
										else
										{
											std.getTail()->setNext(newStudent);
											std.setTail(newStudent);
										}
										count++;
									}
								}
							end_dup:
								Import.close();
								cout << "\n\t\t============Insert successfully " << count << " student(s)==============\n\n";
								system("pause");
							}
							else
							{
								break;
							}
						}
					}
					else if (select == 3)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(40) << left << "How would you like to add?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 1. Normal Add" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 2. Import From File \"AdminList.txt\"" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(54) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 54; i++)
								cout << char(205);
							cout << char(188);


							cursor(*&select, 4, 6, 3, 102); 

							if (select == 1)
							{
								int n;
								cout << "\n\n\n\nEnter Number of Admins: ";
								cin >> n;
								cin.ignore();
								system("cls");
								adm.addNewAdmin(n);
							}
							else if (select == 2)
							{
								Import.open("C:\__LAPTRINH__\BAITAPLONIMPORTAD.txt", ios::in);
								int count = 0;
								char k;
								if (!Import) cout << "\n\n\nError file!";
								else
								{
									while (!Import.eof())
									{
										string ID, firstName, lastName, address, password;
										int gender_choice;

										getline(Import, ID, ',');
										if (adm.checkID(ID) == 0)
										{
											cout << "Error data! At -->ID= " << ID << " Duplicated ID" << endl;
											break;
										}
										getline(Import, firstName, ',');
										getline(Import, lastName, ',');
										Import >> gender_choice;
										if (adm.checkGender(gender_choice) == 0)
										{
											cout << "Error data! At -->Gender= " << gender_choice << " of ID=" << ID << " Your choice must be 0 or 1" << endl;
											break;
										}
										Import.get(k);
										getline(Import, address, ',');
										int day;
										Import >> day;
										int month;
										Import >> month;
										int year;
										Import >> year;
										if (adm.checkDate(day, month, year) == 0)
										{
											cout << "Error data! At -->Date= " << day << "/" << month << "/" << year << " of ID=" << ID << " Date not exist!";
											break;
										}
										Date DateOfBirth(day, month, year);
										int day_;
										Import >> day_;
										int month_;
										Import >> month_;
										int year_;
										Import >> year_;
										if (adm.checkDate(day_, month_, year_) == 0)
										{
											cout << "Error data! At -->Date= " << day_ << "/" << month_ << "/" << year_ << " of ID=" << ID << " Date not exist!";
											break;
										}
										Date AdmissionDate(day_, month_, year_);
										Import.get(k);
										getline(Import, password, ',');
										Import.get(k);

										Admin* newAdmin = adm.createNewAdmin(ID, firstName, lastName, address, gender_choice, DateOfBirth, AdmissionDate, password);
										if (adm.getHead() == NULL)
										{
											adm.setHead(newAdmin);
											adm.setTail(newAdmin);
										}
										else
										{
											adm.getTail()->setNext(newAdmin);
											adm.setTail(newAdmin);
										}
										count++;
									}
								}
								Import.close();
								cout << "\n\t\t============Insert successfully " << count << " admin(s)==============\n\n";
								system("pause");
							}
							else
							{
								break;;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
			else if (choice == 2)
			{
				int select;
				while (true)
				{
					system("cls");
					cout << "\n\t\t\t\t\t\t" << char(201);
					for (int i = 1; i <= 40; i++)
						cout << char(205);
					cout << char(187);
					cout << "\n\t\t\t\t\t\t" << char(186);
					textcolor(12);
					cout << setw(14) << left << "" << setw(26) << left << "MENU DISPLAY";
					textcolor(7);
					cout << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 1. Display Studentlist" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 2. Display Adminlist" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 3. Display Subjectlist" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 4. Exit" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(200);
					for (int i = 1; i <= 40; i++)
						cout << char(205);
					cout << char(188);

					cursor(*&select, 4, 7, 4, 88);
					
					if (select == 1)
					{
						int select;
						while (true)
						{
						again_dis_menu1:
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 50; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(36) << left << "STUDENT LIST";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 1. Display Account Of Student List" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 2. Display One Student With ID" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 3. Display Information Of Student List" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 4. Display Subjectlist Of Student" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 5. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 50; i++)
								cout << char(205);
							cout << char(188);
							
							cursor(*&select, 4, 8, 5, 98);
							
							if (select == 1)
							{
								int select;
								while (true)
								{
									system("cls");
									cout << "\n\t\t\t\t\t\t" << char(201);
									for (int i = 1; i <= 58; i++)
										cout << char(205);
									cout << char(187);
									cout << "\n\t\t\t\t\t\t" << char(186);
									textcolor(12);
									cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
									textcolor(7);
									cout << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(200);
									for (int i = 1; i <= 58; i++)
										cout << char(205);
									cout << char(188);

									cursor(*&select, 4, 6, 3, 106);
									
									if (select == 1)
									{
										system("cls");
										std.Display_Acc();
										system("pause");
									}
									else if (select == 2)
									{
										std.Export_to_file_Acc(Export);
										cout << "\n\t\t============Exported Successfully!===============\n\n";
										system("pause");
									}
									else
									{
										break;
									}
								}
							}
							else if (select == 2)
							{
								string id;
								//cin.ignore();
								do
								{
									int choice = 1;
									cout << "\n\n\n\nInput ID Student You Want To Display: "; getline(cin, id);
									if (std.checkID(id) == true)
									{
										cout << "\nNot Found Student!\n0.Exit\n1.Try again";
										do
										{
											cout << "\n-->"; cin >> choice;
											if (choice < 0 || choice>1) cout << "Invalid choice!";
										} while (choice < 0 || choice>1);
										if (choice == 0) goto again_dis_menu1;
										if (choice == 1) cin.ignore();
									}
								} while (std.checkID(id) == true);
								system("cls");
								std.display_(id);
								cout << endl;
								std.display_subjects_One_Student(id);
								system("pause");
							}
							else if (select == 3)
							{
								int select;
								while (true)
								{
									system("cls");
									cout << "\n\t\t\t\t\t\t" << char(201);
									for (int i = 1; i <= 58; i++)
										cout << char(205);
									cout << char(187);
									cout << "\n\t\t\t\t\t\t" << char(186);
									textcolor(12);
									cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
									textcolor(7);
									cout << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
									cout << "\n\t\t\t\t\t\t" << char(200);
									for (int i = 1; i <= 58; i++)
										cout << char(205);
									cout << char(188);

									cursor(*&select, 4, 6, 3, 106);

									if (select == 1)
									{
										system("cls");
										std.display();
										system("pause");
									}
									else if (select == 2)
									{
										std.Export_to_file(Export);
										cout << "\n\t\t============Exported Successfully!===============\n\n";
										system("pause");
									}
									else
									{
										break;
									}
								}
							}
							else if (select == 4)
							{
								system("cls");
								std.Display_SubjectList();
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else if (select == 2)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 106);
							
							if (select == 1)
							{
								system("cls");
								adm.display();
								system("pause");
							}
							else if (select == 2)
							{
								adm.Export_to_file(Export);
								cout << "\n\t\t============Exported Successfully!===============\n\n";
								system("pause");
							}
							else
							{
								break;
							}

						}
					}
					else if (select == 3)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 106);
							
							if (select == 1)
							{

								system("cls");
								c.DISPLAY();
								system("pause");
							}
							else if (select == 2)
							{
								c.Export_to_file(Export);
								cout << "\n\t\t============Exported Successfully!===============\n\n";
								system("pause");
							}
							else
							{
								break;
							}

						}
					}
					else
					{
						break;
					}
				}
			}
			else if (choice == 3)
			{
				int select;
				while (true)
				{
					system("cls");
					cout << "\n\t\t\t\t\t\t" << char(201);
					for (int i = 1; i <= 40; i++)
						cout << char(205);
					cout << char(187);
					cout << "\n\t\t\t\t\t\t" << char(186);
					textcolor(12);
					cout << setw(14) << left << "" << setw(26) << left << "MENU  SEARCH";
					textcolor(7);
					cout << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 1. Search With Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 2. Search With Admin" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 3. Search With Subject" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(40) << left << " 4. Exit" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(200);
					for (int i = 1; i <= 40; i++)
						cout << char(205);
					cout << char(188);
					
					cursor(*&select, 4, 7, 4, 88);
					
					if (select == 1)
					{
						system("cls");
						std.Menu_Search();						
					}
					else if (select == 2)
					{
						system("cls");
						adm.Menu_Search();						
					}
					else if (select == 3)
					{
						system("cls");
						c.Menu_Search();						
					}
					else
					{
						break;
					}
				}

			}
			else if (choice == 4)
			{
				//test:
				int select;
				while (true)
				{
					system("cls");
					cout << "\n\t\t\t\t\t\t" << char(201);
					for (int i = 1; i <= 70; i++)
						cout << char(205);
					cout << char(187);
					cout << "\n\t\t\t\t\t\t" << char(186);
					textcolor(12);
					cout << setw(29) << left << "" << setw(41) << left << "MENU  UPDATE";
					textcolor(7);
					cout << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 1. Modified  With  Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 2. Modified  With  Admin" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 3. Modified  With  Subject" << char(186);
					//cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << "" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 4. Delete    With  Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 5. Delete    With  Admin" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 6. Delete    With  Subject" << char(186);
					//cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << "" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 7. Sort      With  Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 8. Sort      With  Admin" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 9. Sort      With  Subject" << char(186);
					//cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << "" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 10.Display  Information Of Each Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 11.Display  The List Of Subjects Of Each Student" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 12.Display  Adminlist" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 13.Display  Subjectlist" << char(186);
					//cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << "" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(186) << setw(70) << left << " 14.Exit" << char(186);
					cout << "\n\t\t\t\t\t\t" << char(200);
					for (int i = 1; i <= 70; i++)
						cout << char(205);
					cout << char(188);
					
					cursor(*&select, 4, 17, 14, 118);
					
					if (select == 1)
					{
						system("cls");
						std.Menu_Modifier();
					}
					else if (select == 2)
					{
						system("cls");
						adm.Menu_Modifier();
					}
					else if (select == 3)
					{
						//==============MODIFIED SUBJECT====================
						int choice;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(22) << left << "" << setw(36) << left << "MENU  MODIFIED" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Modified Subject with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Modified IDS with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 3. Modified Name with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 4. Modified Teacher's Name with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 5. Modified Units with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 6. Modified Limit with matches IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 7. Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 8. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);
						
							cursor(*&choice, 4, 11, 8, 106);
							
							if (choice == 1)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n\n\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_All_InFormation_With_IDS_COURSE(IDS_);
								std.Modified_All_InFormation_With_IDS_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 2)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_With_IDS(IDS_);
								std.Modified_With_IDS_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 3)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_With_Name(IDS_);
								std.Modified_With_Name_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 4)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_With_Teacher_Name(IDS_);
								std.Modified_With_Teacher_Name_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 5)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_With_Units(IDS_);
								std.Modified_With_Units_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 6)
							{
								string IDS_;
								//cin.ignore();
								cout << "\n\n\n\n";
								do
								{
									cout << "\nInput ID Subject You Want To Modified: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								string temp = IDS_;
								Subject* sub = c.GetSubjectWithID(IDS_);
								c.Modified_With_Limit(IDS_);
								std.Modified_With_Limit_Std(sub, temp);
								cout << "\n\t\t============Modified Successfully!===============\n\n";
								system("pause");
							}
							else if (choice == 7)
							{
								system("cls");
								c.DISPLAY();
								system("pause");
							}
							else
							{
								break;
							}

						}

					}
					else if (select == 4)
					{
						system("cls");
						std.Menu_Delete();
					}
					else if (select == 5)
					{
						system("cls");
						adm.Menu_Delete();
					}
					else if (select == 6)
					{
						int choice;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 50; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(19) << left << "" << setw(31) << left << "MENU  DELETE" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 1. Delete With IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 2. Delete With Name" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 3. Delete With Teacher's Name" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 4. Delete With Units" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 5. Delete With Limit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 6. Delete All" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 7. Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(50) << left << " 8. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 50; i++)
								cout << char(205);
							
							cursor(*&choice, 4, 11, 8, 98);

							if (choice == 1)
							{
								//cin.ignore();
								system("cls");
								c.DISPLAY();
								if (c.getCourseHead() == NULL)
								{
									cout << endl;
									system("pause");
									continue;
								}
								cout << endl;
								string IDS_;
								cout << "\n\n\n\n\n\n\n\n\n";
								do
								{
									cout << "Input ID Subject You Want To Delete: "; getline(cin, IDS_);
									if (c.checkIDS(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid ID Subject!Please try again!===\n";
								} while (c.checkIDS(IDS_) == true);
								c.Delete_With_IDS(IDS_);
								std.Delete_With_IDS_Std(IDS_);
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");

							}
							else if (choice == 2)
							{
								//cin.ignore();
								system("cls");
								c.DISPLAY();
							
								if (c.getCourseHead() == NULL)
								{
									cout << endl;
									system("pause");
									continue;
								}
								cout << endl;
								string IDS_;
								do
								{
									cout << "\n\n\n\n\n\n\nInput Subject's Name You Want To Delete: "; getline(cin, IDS_);
									if (c.checkName(IDS_) == false)
									{
										break;
									}
									else
										cout << "\n===Invalid Name!Please try again!===\n";
								} while (c.checkName(IDS_) == true);
								c.Delete_With_Name(IDS_);
								std.Delete_With_Name_Std(IDS_);
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");

							}
							else if (choice == 3)
							{
								//cin.ignore();
								system("cls");
								c.DISPLAY();
								if (c.getCourseHead() == NULL)
								{
									cout << endl;
									system("pause");
									continue;
								}
								cout << endl;
								string Firstname_;
								cout << "\n\n\n\n\n\nEnter the \"Teacher's Name\" you want to delete: ";
								getline(cin, Firstname_);
								c.Delete_With_Teacher_Name(Firstname_);
								std.Delete_With_Teacher_Name_Std(Firstname_);
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");
							}
							else if (choice == 4)
							{
								int unit;
								system("cls");
								c.DISPLAY();
								if (c.getCourseHead() == NULL)
								{
									cout << endl;
									system("pause");
									continue;
								}
								cout << endl;
								do {
									cout << "\n\n\n\n\nInput Number Of Unit (Only accept from 1 to 15 Units): "; cin >> unit;
									if (c.checkUnit(unit) == false)
										cout << "Invalid Unit! Please type again!\n";
								} while (c.checkUnit(unit) == false);
								c.Delete_With_Units(unit);
								std.Delete_With_Units_Std(unit);
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");
							}
							else if (choice == 5)
							{
								int limit;
								system("cls");
								c.DISPLAY();
								if (c.getCourseHead() == NULL)
								{
									cout << endl;
									system("pause");
									continue;
								}
								cout << endl;
								cout << "\n\n\n";
								do {
									cout <<"\n\n\n\nInput Max NumberStudent : "; cin >> limit;
									if (c.checkLimit(limit) == false)
										cout << "Invalid Input! Please type again!\n";
								} while (c.checkLimit(limit) == false);
								c.Delete_With_Limit(limit);
								std.Delete_With_Limit_Std(limit);
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");

							}
							else if (choice == 6)
							{
								c.Delete_All();
								std.Delete_ALL();
								cout << "\n\n\t\t===============Deleted Successfully!================\n\n";
								system("pause");

							}
							else if (choice == 7)
							{
								system("cls");
								c.DISPLAY();
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else if (select == 7)
					{
						system("cls");
						std.Menu_Sort();
					}
					else if (select == 8)
					{
						system("cls");
						adm.Menu_Sort();
					}
					else if (select == 9)
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
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 1. Sort by IDS" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 2. Sort by Name" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 3. Sort by Teacher's Name" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 4. Sort by Units" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 5. Sort by Limit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 6. Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(48) << left << " 7. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 48; i++)
								cout << char(205);
							cout << char(188);
							
							cursor(*&choice, 4, 10, 7, 96);
							
							if (choice == 1)
							{
								c.Sort_With_IDS();
								std.Sort_With_IDS_Std();
								cout << "\n\n\n\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
								system("pause");
							}
							else if (choice == 2)
							{
								c.Sort_With_Name();
								std.Sort_With_Name_Std();
								cout << "\n\n\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
								system("pause");
							}
							else if (choice == 3)
							{
								c.Sort_With_Teacher_Name();
								std.Sort_With_Teacher_Name();
								cout << "\n\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
								system("pause");
							}
							else if (choice == 4)
							{
								c.Sort_With_Unit();
								std.Sort_With_Unit_Std();
								cout << "\n\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
								system("pause");
							}
							else if (choice == 5)
							{
								c.Sort_With_Limit();
								std.Sort_With_Limit_Std();
								cout << "\n\n\n\n\t\t==========Sorted Successfully!=========\n\n";
								system("pause");
							}
							else if (choice == 6)
							{
								system("cls");
								c.DISPLAY();
								cout << endl;
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else if (select == 10)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 3. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 102); 
							
							if (select == 1)
							{
								system("cls");
								std.display();
								cout << endl;
								system("pause");
							}
							else if (select == 2)
							{
								std.Export_to_file(Export);
								cout << "\n\n\n\t\t============Exported Successfully!===============\n\n";
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else if (select == 11)
					{
						system("cls");
						std.Display_SubjectList();
						cout << endl;
						system("pause");	
					}
					else if (select == 12)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 102); 
							
							if (select == 1)
							{
								system("cls");
								adm.display();
								cout << endl;
								system("pause");
							}
							else if (select == 2)
							{
								adm.Export_to_file(Export);
								cout << "\n\n\n\t\t============Exported Successfully!===============\n\n";
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else if (select == 13)
					{
						int select;
						while (true)
						{
							system("cls");
							cout << "\n\t\t\t\t\t\t" << char(201);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(187);
							cout << "\n\t\t\t\t\t\t" << char(186);
							textcolor(12);
							cout << setw(14) << left << "" << setw(44) << left << "How would you like to display?";
							textcolor(7);
							cout << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 1. Normal Display" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 2. Export To File" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(186) << setw(58) << left << " 0. Exit" << char(186);
							cout << "\n\t\t\t\t\t\t" << char(200);
							for (int i = 1; i <= 58; i++)
								cout << char(205);
							cout << char(188);

							cursor(*&select, 4, 6, 3, 102); 
							
							if (select == 1)
							{
								system("cls");
								c.DISPLAY();
								cout << endl;
								system("pause");
							}
							else if (select == 2)
							{
								c.Export_to_file(Export);
								cout << "\n\n\n\t\t============Exported Successfully!===============\n\n";
								system("pause");
							}
							else
							{
								break;
							}
						}

					}
					else
					{
						break;
					}
				}

			}
			else
			{
				//cin.ignore();
				goto again;
			}
		}
	}

end:
	system("cls");
	cout << "\n\n\n\t\t\t\t\t\t\t\t=====THANK YOU SO MUCH!=====";
	cout << "\n\t\t\t\t\t\t\t\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3";
	return 0;
}