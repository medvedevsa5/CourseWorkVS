#include "stanislaw_lib.h"

int getCommandCode(std::string command)
{
	if (command == "RECTANGLE")
	{
		return RECTANGLE;
	}

	if (command == "CONCAVE")
	{
		return CONCAVE;
	}

	if (command == "COMPLEX")
	{
		return COMPLEX;
	}

	if (command == "MOVE")
	{
		return MOVE;
	}

	if (command == "SCALE")
	{
		return SCALE;
	}

	return -1;
}