//variant 30
//Piven Denys K-11

#pragma once
#include <string>

enum class LineType
{
	Empty,
	Footer,
	Header,
	Line
};

class Lexer
{
public:
	//load determines type of line, and load line to class`es line
	LineType load(std::string line);
	//returns field between separators
	bool next(std::string &field);
	//eof determines end of line
	bool eof() const noexcept;
private:
	std::string separators = { "$;<:" };
	std::string whiteSymbols = { " \n\r\t\v\f\0" };
	std::string line;
	LineType state = LineType::Line;
	int currentPosition = 0;
};
