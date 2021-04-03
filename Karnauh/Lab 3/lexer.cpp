//variant 30
//Piven Denys K-11

#include <iostream>
#include <string>
#include "lexer.h"
using namespace std;

LineType Lexer::load(string line) {
	state = LineType::Line;
	if (line.find("header") == 0 && line.find_first_of(separators, 0) == 6) {
		line = line.substr(line.find_first_of(separators) + 1);
		state = LineType::Header;
	}
	else
		if (line.find("footer") == 0 && line.find_first_of(separators, 0) == 6) {
			line = line.substr(line.find_first_of(separators) + 1);
			state = LineType::Footer;
		}
		else
			if ((int)line.find_first_not_of(whiteSymbols) == -1) {
				this->line = line;
				state = LineType::Empty;
			}
	this->line = line;
	return state;
}

bool Lexer::next(string &field) {
	
    int endOfFieldPosition = line.find_first_of(separators, currentPosition);

    if (endOfFieldPosition >= 0) {
		field = line.substr(currentPosition, endOfFieldPosition - currentPosition);
        currentPosition = endOfFieldPosition + 1;
    } else {
		field = line.substr(currentPosition, line.length() - currentPosition);
		currentPosition = line.length() + 1;
    }

    int a = field.find_first_not_of(whiteSymbols);
    int b = field.find_last_not_of(whiteSymbols);
    if (a > -1) {
		field = field.substr(a, b - a + 1);
    } else {
        field = "";
    }

	//check eof
	if (eof()) {
		currentPosition = 0;
		return false;
	}

    return true;
}

bool Lexer::eof() const noexcept {
	if (currentPosition == (int)line.length() + 1) {
		return true;
	}
	else {
		return false;
	}
}