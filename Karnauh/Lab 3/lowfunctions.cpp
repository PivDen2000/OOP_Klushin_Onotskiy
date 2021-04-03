//variant 30
//Piven Denys K-11

#include <iostream>
#include <string>
#include "lowfunctions.h"
#include "info.h"

bool checkFilename(std::string filename) {
	if (filename.length() > 4) {
		if (filename.compare(filename.length() - 4, 4, ".txt") == 0) {
			return true;
		}
	}
	return false;
}

bool checkConsole(std::string console) {
	if (console == "#con") {
		return true;
	}
	return false;
}

bool comp(const Info::Student& a, const Info::Student& b)
{
	if (a.skipPracticeCounter > b.skipPracticeCounter) {
		return true;
	}
	else {
		if (a.skipPracticeCounter == b.skipPracticeCounter) {
			if (a.skipLectureCounter < b.skipLectureCounter) {
				return true;
			}
		}
	}
	return false;
}