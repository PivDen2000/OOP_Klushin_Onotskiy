//variant 30
//Piven Denys K-11

#include <iostream>
#include <string>
#include "info.h"
#include <vector>
using namespace std;

Info::Student::Skip::Skip(string Subject, LessonType state, int week, int day, int pairNum, int auditorium)
{
	this->week = week;
	this->day = day;
	this->pairNum = pairNum;
	this->auditorium = auditorium;
	this->Subject = Subject;
	this->state = state;
}

bool Info::Student::Skip::operator==(const Skip &other)
{
	if (this->Subject == other.Subject&&this->state == other.state&&this->week == other.week&&this->day == other.day&&this->pairNum == other.pairNum&&this->auditorium == other.auditorium) {
		return true;
	}
	else {
		return false;
	}
}
bool Info::Student::Skip::operator!=(const Skip &other)
{
	if (this->Subject == other.Subject&&this->state == other.state&&this->week == other.week&&this->day == other.day&&this->pairNum == other.pairNum&&this->auditorium == other.auditorium) {
		return false;
	}
	else {
		return true;
	}
}
bool Info::Student::Skip::operator<(const Skip &other)
{
	if (this->Subject < other.Subject) {
		return true;
	}
	else {
		if (this->Subject == other.Subject) {
			if (this->state < other.state) {
				return true;
			}
			else {
				if (this->state == other.state) {
					if (this->week < other.week) {
						return true;
					}
					else {
						if (this->week == other.week) {
							if (this->day < other.day) {
								return true;
							}
							else {
								if (this->day == other.day) {
									if (this->pairNum < other.pairNum) {
										return true;
									}
									else {
										if (this->pairNum == other.pairNum) {
											if (this->auditorium < other.auditorium) {
												return true;
											}
											else {
												return false;
											}
										}
										else {
											return false;
										}
									}
								}
								else {
									return false;
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
}
bool Info::Student::Skip::operator<=(const Skip &other)
{
	if (*this < other) {
		return true;
	}
	else {
		if (*this == other) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool Info::Student::Skip::operator>(const Skip &other)
{
	if (this->Subject > other.Subject) {
		return true;
	}
	else {
		if (this->Subject == other.Subject) {
			if (this->state > other.state) {
				return true;
			}
			else {
				if (this->state == other.state) {
					if (this->week > other.week) {
						return true;
					}
					else {
						if (this->week == other.week) {
							if (this->day > other.day) {
								return true;
							}
							else {
								if (this->day == other.day) {
									if (this->pairNum > other.pairNum) {
										return true;
									}
									else {
										if (this->pairNum == other.pairNum) {
											if (this->auditorium > other.auditorium) {
												return true;
											}
											else {
												return false;
											}
										}
										else {
											return false;
										}
									}
								}
								else {
									return false;
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
}
bool Info::Student::Skip::operator>=(const Skip &other)
{
	if (*this > other) {
		return true;
	}
	else {
		if (*this == other) {
			return true;
		}
		else {
			return false;
		}
	}
}

//void Info::Student::AddSkip(std::string Subject, LessonType state,int week, int day, int pairNum, int auditorium)
//{
//	try {
//		if (week > 0 && week <= 15 && day > 0 && day <= 5 && pairNum > 0 && pairNum <= 4 && auditorium > 0 && size(Subject) <= 20 && (state == LessonType::S || state == LessonType::lab || state == LessonType::p || state == LessonType::L)) {
//			Skip skip(Subject, state, week, day, pairNum, auditorium);
//			pairCountSkip++;
//			if (skip.GetState() == LessonType::p) {
//				pairCountSkipPractice++;
//			}
//			cout << "Skip was added to student" << endl;
//		}
//		else {
//			throw out_of_range("Not right value");
//		}
//	}
//	catch (out_of_range& e) {
//		cout << e.what() << endl;
//	}
//}

//void Info::Student::FindSkip(std::string Subject, LessonType state,int week, int day, int pairNum, int auditorium)
//{
//	try {
//		if (week > 0 && week <= 15 && day > 0 && day <= 5 && pairNum > 0 && pairNum <= 4 && auditorium > 0 && size(Subject) <= 20 && (state == LessonType::S || state == LessonType::lab || state == LessonType::p || state == LessonType::L)) {
//			cout << "Skip was founded" << endl;
//		}
//		else {
//			throw out_of_range("Not right value");
//		}
//	}
//	catch (out_of_range& e) {
//		cout << e.what() << endl;
//	}
//}
//
//int Info::Student::GetPairCountSkip()
//{
//	return pairCountSkip;
//}
int Info::Student::Skip::GetDay()
{
	return day;
}
//int Info::Student::GetPairCountSkipPractice()
//{
//	return pairCountSkipPractice;
//}
int Info::Student::Skip::GetWeek()
{
	return week;
}
int Info::Student::Skip::GetPairNum()
{
	return pairNum;
}
int Info::Student::Skip::GetAuditorium()
{
	return auditorium;
}
std::string Info::Student::Skip::GetSubject()
{
	return Subject;
}
string Info::Student::Skip::GetState()
{
	switch (state) {
	case LessonType::L:
		return "L";
		break;
	case LessonType::p:
		return "p";
		break;
	case LessonType::S:
		return "S";
		break;
	case LessonType::lab:
		return "lab";
		break;
	}
	return "L";
}

bool Info::Student::operator==(const Student &other)
{
	if (this->patronymicname == other.patronymicname&&this->name == other.name&&this->surname == other.surname&&this->grade == other.grade&&this->group == other.group) {
		return true;
	}
	else return false;
}
bool Info::Student::operator!=(const Student &other)
{
	if (this->patronymicname != other.patronymicname||this->name != other.name||this->surname != other.surname||this->grade == other.grade||this->group == other.group) {
		return true;
	}
	else return false;
}
bool Info::Student::operator<(const Student &other)
{
	if (this->grade < other.grade) {
		return true;
	}
	else {
		if (this->grade == other.grade) {
			if (this->group < other.group) {
				return true;
			}
			else {
				if (this->group == other.group) {
					if (this->surname < other.surname) {
						return true;
					}
					else {
						if (this->surname == other.surname) {
							if (this->name < other.name) {
								return true;
							}
							else {
								if (this->name == other.name) {
									if (this->patronymicname < other.patronymicname) {
										return true;
									}
									else {
										return false;
									}
								}
								else {
									return false;
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
}
bool Info::Student::operator<=(const Student &other)
{
	if (*this < other) {
		return true;
	}
	else {
		if (*this == other) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool Info::Student::operator>(const Student &other)
{
	if (this->grade > other.grade) {
		return true;
	}
	else {
		if (this->grade == other.grade) {
			if (this->group > other.group) {
				return true;
			}
			else {
				if (this->group == other.group) {
					if (this->surname > other.surname) {
						return true;
					}
					else {
						if (this->surname == other.surname) {
							if (this->name > other.name) {
								return true;
							}
							else {
								if (this->name == other.name) {
									if (this->patronymicname > other.patronymicname) {
										return true;
									}
									else {
										return false;
									}
								}
								else {
									return false;
								}
							}
						}
						else {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
}
bool Info::Student::operator>=(const Student &other)
{
	if (*this > other) {
		return true;
	}
	else {
		if (*this == other) {
			return true;
		}
		else {
			return false;
		}
	}
}

Info::Student::Student(string name, string patronymicname, string surname, int grade, string group)
{
	this->patronymicname = patronymicname;
	this->name = name;
	this->surname = surname;
	this->grade = grade;
	this->group = group;
}

std::string Info::Student::GetPatronymicName()
{
	return patronymicname;
}

std::string Info::Student::GetName()
{
	return name;
}

std::string Info::Student::GetSurname()
{
	return surname;
}

std::string Info::Student::GetGroup()
{
	return group;
}

int Info::Student::GetGrade()
{
	return grade;
}


//void Info::load(std::string patronymicname, std::string name, std::string surname, int grade, std::string group, std::string Subject, LessonType state, int week, int day, int pairNum, int auditorium)
//{
//	cout << "I am Method 'load from Info WITHOUT details' and I download the Student to Students..." << endl;
//	Info::Student student(patronymicname, name, surname, grade, group);
//	student.load(week, day, pairNum, auditorium, Subject, state);
//	cout << "Student " << patronymicname << " " << name << " " << surname << " was added to Students" << endl;
//}


Info::Student::Skip Info::Student::load(std::string subject, LessonType state, int week, int day, int pairNum, int auditorium)
{
	Skip skip(subject, state, week, day, pairNum, auditorium);
	vectorOfSkips.push_back(skip);
	return skip;
}

void Info::SetauditoriumMinNum(int auditoriumMinNum)
{
	this->auditoriumMinNum = auditoriumMinNum;
}

void Info::SetpairNumSum(int pairNumSum)
{
	this->pairNumSum = pairNumSum;
}

int Info::GetAuditoriumMinNum()
{
	return auditoriumMinNum;
}

int Info::GetPairNumSum()
{
	return pairNumSum;
}

//void Info::FindStudentSkipPracticeMoreAverage()
//{
//	int counter = 0;
//	for (size_t i = 0; i < vectorOfStudents.size(); i++) {
//		for (size_t j = 0; j < vectorOfStudents[i].vectorOfSkips.size(); j++) {
//			if (vectorOfStudents[i].vectorOfSkips[j].GetState() == "p") {
//				vectorOfStudents[i].skipPracticeCounter++;
//				counter++;
//			}
//		}
//	}
//	double Average = vectorOfStudents.size() / counter;
//	for (size_t i = 0; i < vectorOfStudents.size(); i++) {
//		if (vectorOfStudents[i].skipPracticeCounter > Average) {
//
//		}
//	}
//}

bool Info::FindStudent(vector<Student> vectorOfStudents, string surname, string name, string patronymic)
{
	for (size_t i = 0; i < vectorOfStudents.size(); i++) {
		if (vectorOfStudents[i].GetSurname() == surname && vectorOfStudents[i].GetName() == name && vectorOfStudents[i].GetPatronymicName() == patronymic) {
			return true;
		}
	}
	return false;
}

bool Info::FindStudentGroupGrade(std::vector<Student> vectorOfStudents, std::string surname, std::string name, std::string patronymic, std::string group, int grade)
{
	for (size_t i = 0; i < vectorOfStudents.size(); i++) {
		if (vectorOfStudents[i].GetSurname() == surname && vectorOfStudents[i].GetName() == name && vectorOfStudents[i].GetPatronymicName() == patronymic)
		{
			if (vectorOfStudents[i].GetGrade() == grade && vectorOfStudents[i].GetGroup() == group)
			{
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

void Info::load(std::string name, std::string patronymicname, std::string surname, int grade, std::string group)
{
	Info::Student student(name, patronymicname, surname, grade, group);
	vectorOfStudents.push_back(student);
	
}

void Info::load(std::string name, std::string patronymicname, std::string surname,std::string subject, LessonType state, int week, int day, int pairNum, int auditorium)
{
	for (size_t i = 0; i < vectorOfStudents.size(); i++) {
		if (name == vectorOfStudents[i].GetName() &&
			patronymicname == vectorOfStudents[i].GetPatronymicName() &&
			surname == vectorOfStudents[i].GetSurname()
			) {
			vectorOfStudents[i].load(subject, state, week, day, pairNum, auditorium);
			break;
		}
	}
}