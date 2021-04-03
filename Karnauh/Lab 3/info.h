//variant 30
//Piven Denys K-11

#pragma once

#include <string>
#include <ostream>
#include <vector>

//enum LessonType {
//	L,
//	p,
//	S,
//	lab,
//};

// S < lab < p < L
enum LessonType {
	S,
	lab,
	p,
	L,
};

class Info
{
public:
	Info() = default;
	void SetauditoriumMinNum(int auditoriumMinNum);
	void SetpairNumSum(int pairNumSum);
	int GetAuditoriumMinNum();
	int GetPairNumSum();
	class Student {
		public:
			double skipPracticeCounter = 0;
			double skipLectureCounter = 0;
			//== , != , <, <= , >, >=
			bool operator ==(const Student&);
			bool operator !=(const Student&);
			bool operator <(const Student&);
			bool operator <=(const Student&);
			bool operator >(const Student&);
			bool operator >=(const Student&);
			Student() = default;
			Student(std::string name, std::string patronymicname, std::string surname, int grade, std::string group);
			std::string GetPatronymicName();
			std::string GetName();
			std::string GetSurname();
			std::string GetGroup();
			int GetGrade();
			class Skip {
			public:
				Skip() = default;
				Skip(std::string Subject, LessonType state, int week, int day, int pairNum, int auditorium);
				//== , != , <, <= , >, >=
				std::string GetSubject();
				std::string GetState();

				bool operator ==(const Skip&);
				bool operator !=(const Skip&);
				bool operator <(const Skip&);
				bool operator <=(const Skip&);
				bool operator >(const Skip&);
				bool operator >=(const Skip&);

				int GetWeek();
				int GetDay();
				int GetPairNum();
				int GetAuditorium();
			private:
				int week = 1; //1-15
				int day = 1; //1-5
				int pairNum = 1; //1-4
				int auditorium = 1;//+Z
				std::string Subject;// <=20
				LessonType state = LessonType::S;// L, p, S, lab
			};
			std::vector<Skip> vectorOfSkips;
			Skip load(std::string subject, LessonType state, int week, int day, int pairNum, int auditorium);
		private:
			//Skips skips;
			std::string patronymicname;// <=30
			std::string name;// <=25
			std::string surname;// <=29
			std::string group;// <=5
			int grade = 1; //1-4
			
		};
	//Student GetStudent();
	std::vector<Student> vectorOfStudents;
	bool FindStudent(std::vector<Student> vectorOfStudents, std::string surname, std::string name, std::string patronymic);
	bool FindStudentGroupGrade(std::vector<Student> vectorOfStudents, std::string surname, std::string name, std::string patronymic, std::string group, int grade);
	void load(std::string name, std::string patronymicname, std::string surname, int grade, std::string group);
	void load(std::string name, std::string patronymicname, std::string surname, std::string subject, LessonType state, int week, int day, int pairNum, int auditorium);
private:
	int auditoriumMinNum = 1;//+Z
	int pairNumSum = 1;//+Z
	//Student currentStudent;
};