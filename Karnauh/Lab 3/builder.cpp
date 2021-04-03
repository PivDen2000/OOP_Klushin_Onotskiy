//variant 30
//Piven Denys K-11

#include <iostream>
#include <string>
#include <fstream>
#include "builder.h"
#include "lexer.h"
#include "info.h"
using namespace std;

bool Builder::loadData(Info& info, const char* filename)
{
	bool result = false;
	try {
		ifstream fin(filename);

		if (fin.is_open()) {
			Lexer lexer;
			string line;
			string field;
			
			//order
			int trueOrder[3] = { 0,1,2 };
			int order[3] = { -1,-1,-1 };
			int k = 0;
			
			//header
			int audMinNum = 0;
			int headerCounter = 0;
			int audRealMinNum = 0;
			
			//line
			int lineCounter = 0;
			
			//footer
			int pairNumSum = 0;
			int footerCounter = 0;

			while (getline(fin, line))
			{
				switch (lexer.load(line)) {
				case LineType::Empty:
					result = true;
					break;
				case LineType::Footer:
					if (headerCounter == 0) { throw out_of_range("100 missing header (in first line find footer)"); }
					if (lineCounter == 0) { order[k] = 1; k++; }
					//sum of pairs num
					footerCounter++;
					if (footerCounter == 1) { order[k] = 2; k++; };
					if (audRealMinNum != audMinNum) { throw out_of_range("102 header does not match the contents of the file"); };
					if (lexer.next(field)) { throw out_of_range("203 inappropriate number of fields in footer"); };
					if (pairNumSum != atoi(field.c_str())) throw out_of_range("202 footer does not match the contents of the file");
					//pairNumSum = atoi(field.c_str());
					info.SetpairNumSum(pairNumSum);
					result = true;
					break;
				case LineType::Header:
					//min num of auditorium
					headerCounter++;
					if (headerCounter == 1) { order[k] = 0; k++; };
					if (lexer.next(field)) { throw out_of_range("103 inappropriate number of fields in header"); };
					audMinNum = atoi(field.c_str());
					info.SetauditoriumMinNum(audMinNum);
					result = true;
					break;
				case LineType::Line:
					if (headerCounter == 0) { throw out_of_range("100 missing header (in first line find not header)"); }
					if (footerCounter > 0) { throw out_of_range("300 footer before line has detected"); }
					lineCounter++;
					if (lineCounter == 1) { order[k] = 1; k++;}

					string lineNumberString;
					lexer.next(lineNumberString);
					int lineNumber = atoi(lineNumberString.c_str());
					if (lineNumber != lineCounter) { throw out_of_range("301 incorrect line number"); };

					string weekString;
					lexer.next(weekString);
					int week = atoi(weekString.c_str());
					if (week < 1 || week > 15) throw out_of_range("303 Incorrect value of week");

					string name;
					lexer.next(name);
					if (name.length() > 25) throw out_of_range("303 Too long Name");

					string subject;
					lexer.next(subject);
					if (subject.length() > 20) throw out_of_range("303 Too long Subject");

					string stateString;
					LessonType state;
					lexer.next(stateString);
					if (stateString == "L") {
						state = LessonType::L;
					}
					else
						if (stateString == "p") {
							state = LessonType::p;
						}
						else
							if (stateString == "S") {
								state = LessonType::S;
							}
							else
								if (stateString == "lab") {
									state = LessonType::lab;
								}
								else {
									throw out_of_range("303 Incorrect value of LessonType");
								}

					string patronymicname;
					lexer.next(patronymicname);
					if (patronymicname.length() > 29) throw out_of_range("303 Too long Patronymic");

					string surname;
					lexer.next(surname);
					if (surname.length() > 30) throw out_of_range("303 Too long Surname");

					string dayString;
					lexer.next(dayString);
					int day = atoi(dayString.c_str());
					if (day < 1 || day > 5) throw out_of_range("303 Incorrect value of day");

					string pairNumString;
					lexer.next(pairNumString);
					int pairNum = atoi(pairNumString.c_str());
					if (pairNum < 1 || pairNum > 4) throw out_of_range("303 Incorrect value of pairNum");
					pairNumSum += pairNum;

					string gradeString;
					lexer.next(gradeString);
					int grade = atoi(gradeString.c_str());
					if (grade < 1 || grade > 4) throw out_of_range("303 Incorrect value of grade");

					string group;
					lexer.next(group);
					if (group.length() > 5) throw out_of_range("303 Too long group");

					string auditoriumString;
					if (lexer.next(auditoriumString)) { throw out_of_range("302 inappropriate number of fields in line"); }
					int auditorium = atoi(auditoriumString.c_str());
					if (auditorium < 0) throw out_of_range("303 Incorrect value of auditorium");
					if (lineCounter == 1) { audRealMinNum = auditorium; }
					if (auditorium < audRealMinNum) {
						audRealMinNum = auditorium;
					}
					if (auditorium < audMinNum) throw out_of_range("102 header does not match the contents of the file");

					//add student to vector(container)
					if (!info.FindStudent(info.vectorOfStudents, surname, name, patronymicname)) {
						info.load(name, patronymicname, surname, grade, group);
					}
					else {
						if (!info.FindStudentGroupGrade(info.vectorOfStudents, surname, name, patronymicname, group, grade)) {
							throw out_of_range("303 Find student, but not in his group or grade");
						}
					}

					//add skip(miss) to student in vector(container)
					info.load(name, patronymicname, surname, subject, state, week, day, pairNum, auditorium);
					result = true;
					break;
				}
			}
			if (headerCounter == 0) { throw out_of_range("100 missing header"); }
			if (headerCounter > 1) { throw out_of_range("101 there is more than one header"); }
			if (footerCounter == 0) { throw out_of_range("200 missing footer"); }
			if (footerCounter > 1) { throw out_of_range("201 there is more than one footer"); }
			for (int i = 0; i < 3; i++) {
				if (order[i] != trueOrder[i]) { throw out_of_range("300 the order of header-line-footer has been violated"); }
			}
		}
		else {
			result = false;
			throw out_of_range("400 error working with a physical file");
		}
		return result;
	}
	catch (const out_of_range &e) {
		throw out_of_range(e);
	}
	catch (const bad_alloc &e) {
		throw bad_alloc(e);
	}
	catch (...) {
		throw exception();
	}
}