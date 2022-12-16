#pragma once

#include <string>
#include <cmath>

#define EPSILON 1E-3

enum CommandCode
{
	RECTANGLE = 1,
	CONCAVE = 2,
	COMPLEX = 3,
	MOVE = 10,
	SCALE = 11,
};

int getCommandCode(std::string command);
