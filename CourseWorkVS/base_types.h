#pragma once

#include <iosfwd>

struct point_t
{
	double x;
	double y;

	double getDistance(const point_t& point) const;
	bool operator<(const point_t& right);
	friend std::ostream& operator<<(std::ostream& output, point_t point);
	friend std::istream& operator>>(std::istream& input, point_t& point);
};

struct rectangle_t
{
	double width;
	double height;
	point_t pos;

	point_t getCorner(bool isRight, bool isUpper) const;
	double getArea();
};
