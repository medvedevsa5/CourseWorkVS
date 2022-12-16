#include "base_types.h"
#include <iostream>
#include <cmath>

//rectangle_t

point_t rectangle_t::getCorner(bool isRight, bool isUpper) const
{
	int signumX = -1 + 2 * isRight;
	int signumY = -1 + 2 * isUpper;

	point_t corner = { this->pos.x + signumX * (width / 2), this->pos.y + signumY * (height / 2) };

	return corner;
}

double rectangle_t::getArea()
{
	return width * height;
}


//point_t

std::ostream& operator<<(std::ostream& output, point_t point)
{
	output.precision(1);

	output << round(point.x * 10) / 10 << " ";
	output << round(point.y * 10) / 10;

	return output;
}

std::istream& operator>>(std::istream& input, point_t& point)
{
	input >> point.x;
	input >> point.y;

	return input;
}

double point_t::getDistance(const point_t& point) const
{
	double vector[2] = { point.x - this->x, point.y - this->y };

	double length = sqrt(pow(vector[0], 2) + pow(vector[1], 2));

	return length;
}

bool point_t::operator<(const point_t& right)
{
	double leftSquare = pow(this->x, 2) + pow(this->y, 2);
	double rightSquare = pow(right.x, 2) + pow(right.y, 2);

	return leftSquare < rightSquare;
}

