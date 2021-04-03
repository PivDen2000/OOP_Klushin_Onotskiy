//variant 30
//Piven Denys K-11

#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "lexer.h"
#include "info.h"
#include "builder.h"
#include "lowfunctions.h"
#include "copyright.h"

using namespace std;
using InfoResults = ostream &(ostream &, Info &);

//take the information from filename
bool input(Info &info, const char *filename) {
    Builder builder;
    return builder.loadData(info, filename);
}

//output statistics to file or console
ostream& stat(ostream& fout, Info& info) {
	int counter = 0;

	//set to zero all skips(misses) of practice and lectures
	for (size_t i = 0; i < info.vectorOfStudents.size(); i++) {
		for (size_t j = 0; j < info.vectorOfStudents[i].vectorOfSkips.size(); j++) {
			info.vectorOfStudents[i].skipLectureCounter = 0;
			info.vectorOfStudents[i].skipPracticeCounter = 0;
		}
	}

	for (size_t i = 0; i < info.vectorOfStudents.size(); i++) {
		for (size_t j = 0; j < info.vectorOfStudents[i].vectorOfSkips.size(); j++) {
			if (info.vectorOfStudents[i].vectorOfSkips[j].GetState() == "L") {
				info.vectorOfStudents[i].skipLectureCounter++;
			}
			if (info.vectorOfStudents[i].vectorOfSkips[j].GetState() == "p") {
				info.vectorOfStudents[i].skipPracticeCounter++;
				counter++;
			}
		}
	}

	if (counter == 0) return fout;

	double Average = info.vectorOfStudents.size() / counter;

	//correct sort
	sort(info.vectorOfStudents.begin(), info.vectorOfStudents.end(), comp);

	for (size_t i = 0; i < info.vectorOfStudents.size(); i++) {
		if (info.vectorOfStudents[i].skipPracticeCounter > Average) {
			fout << info.vectorOfStudents[i].GetSurname() << "\t" << info.vectorOfStudents[i].GetName() << "\t" << info.vectorOfStudents[i].GetPatronymicName() << "\t" << info.vectorOfStudents[i].vectorOfSkips.size() << "\t" << info.vectorOfStudents[i].skipPracticeCounter << endl;
			//correct sort
			sort(info.vectorOfStudents[i].vectorOfSkips.begin(), info.vectorOfStudents[i].vectorOfSkips.end());
			for (size_t j = 0; j < info.vectorOfStudents[i].vectorOfSkips.size(); j++) {
				fout << "\t" << info.vectorOfStudents[i].vectorOfSkips[j].GetSubject() << "\t" << info.vectorOfStudents[i].vectorOfSkips[j].GetState() << "\t" << info.vectorOfStudents[i].vectorOfSkips[j].GetWeek() << "\t" << info.vectorOfStudents[i].vectorOfSkips[j].GetDay() << "\t" << info.vectorOfStudents[i].vectorOfSkips[j].GetPairNum() << endl;
				}
		}
	}
	return fout;
}

//output list of skips(misses) of students
ostream& output(ostream& fout, Info& info) {
	fout <<"header;"<< info.GetAuditoriumMinNum() << endl;
	int k = 1;
	for (size_t i = 0; i < info.vectorOfStudents.size(); i++) {
		for (size_t j = 0; j < info.vectorOfStudents[i].vectorOfSkips.size(); j++) {
			fout << k << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetWeek() << ";" << info.vectorOfStudents[i].GetName() << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetSubject() << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetState() << ";" << info.vectorOfStudents[i].GetPatronymicName() << ";" << info.vectorOfStudents[i].GetSurname() << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetDay() << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetPairNum() << ";" << info.vectorOfStudents[i].GetGrade() << ";" << info.vectorOfStudents[i].GetGroup() << ";" << info.vectorOfStudents[i].vectorOfSkips[j].GetAuditorium() << endl;
			k++;
		}
	}
	fout << "footer;" << info.GetPairNumSum() << endl;
	return fout;
}

//function determines where we should direct our command
bool do_command(Info &info, const char *filename, InfoResults f) {
    // output to console
    if (strcmp(filename, "#con") == 0) return bool(f(cout, info));

    // output to file
    ofstream fout(filename);
    bool res = bool(f(fout, info));
    fout.close();
    if (fout.fail()) res = false;
    return res;
}

//cout information about commands
void help() {
	cout << "Firstly, print <name>.txt where the information will be taken." << endl;
	cout << "Command \'-output\' + <name2>.txt output information from <name>.txt to <name2>.txt." << endl;
	cout << "Command \'-stat\' + <name3>.txt output statistics to <name3>.txt." << endl;
	cout << "Command #con after \'-output\' or \'-stat\' output something to console." << endl;
}

//test line
//in.txt -output out1.txt qwerty -output -output #con -stat s.txt -stat #con

int main(int argc, char **argv) {

	copyright();
	//cout << "Piven Denys K-11" << endl;

	cout << "This program finds students that missed practical pairs more than in average and display information on them." << endl;
	help();
	cout << "*****" << endl;

	//if we havnt arguments
	if (argc == 1) {
		cout << "nothing to do" << endl;
		return 0;
	}

	Info info;

	//start from 1 because skip zero argument
	int i = 1;
	//cycle find first txt file in line and do command input
	while (i < argc) {
		if (checkFilename(argv[i])) {
			try {
				cout << "input " << argv[i] << " : ";
				if (input(info, argv[i])) {
					cout << "OK" << endl;
				}
				else {
					cout << "UPS" << endl;
				}

			}
			catch (const out_of_range &e) {
				cout << "UPS" << endl;
				cout << e.what() << endl;
				cout << "*****" << endl;
				system("pause");
				return 0;
			}
			catch (const bad_alloc &e) {
				cout << "UPS" << endl;
				cout << "500 bad_alloc" << endl;
				cout << "*****" << endl;
				system("pause");
				return 0;
			}
			catch (...) {
				cout << "UPS" << endl;
				cout << "unknown exception" << endl;
				cout << "*****" << endl;
				system("pause");
				return 0;
			}
			break;
		}
		else {
			cout << argv[i] << " : ignored" << endl;
			i++;
		}
	}

	i++;

	//cycle find and [command + file] do command to this file
	while (i < argc) {
		if (strcmp(argv[i], "-stat") == 0) {
			cout << "stat ";
			if (argv[i + 1]) {
				if (checkFilename(argv[i + 1])) {
					cout << argv[i + 1] << " : ";
					if (do_command(info, argv[i + 1], stat)) {
						cout << "OK" << endl;
					}
					else {
						cout << "UPS" << endl;
					}
					i += 2;
				}
				else {
					if (checkConsole(argv[i + 1])) {
						cout << argv[i + 1] << " : " << endl;
						do_command(info, argv[i + 1], stat);
						i += 2;
					}
				}
			}
			else {
				cout << "undefined" << endl;
				i++;
			}
		}
		else if (strcmp(argv[i], "-output") == 0) {
			cout << "output ";
			if (checkFilename(argv[i + 1])) {
				cout << argv[i + 1] << " : ";
				if (do_command(info, argv[i + 1], output)) {
					cout << "OK" << endl;
				}
				else {
					cout << "UPS" << endl;
				}
				i += 2;
			}
			else {
				if (checkConsole(argv[i + 1])) {
					cout << argv[i + 1] << " : " << endl;
					do_command(info, argv[i + 1], output);
					i += 2;
				}
				else {
					cout << "undefined" << endl;
					i++;
				}
			}
		}
		else {
			cout << argv[i] << ": ignored" << endl;
			i++;
		}
	}

	cout << "*****" << endl;
	system("pause");
	return 0;
}