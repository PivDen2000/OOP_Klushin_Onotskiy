//variant 30
//Piven Denys K-11

#pragma once
#include <iostream>
#include <string>
#include "info.h"

//check word on ".txt" form
bool checkFilename(std::string filename);
//check word on "#con"
bool checkConsole(std::string console);
bool comp(const Info::Student& St1, const Info::Student& St2);