#pragma once

#include <string>
#include <iosfwd>
#include "base_types.h"

class Shape
{
private:

public:
	//чисто виртуальные методы

	virtual double getArea() const = 0;

	virtual rectangle_t getFrameRect() const = 0;

	virtual void move(const double x, const double y) = 0;

	virtual void move(const point_t point) = 0;

	virtual void scale(const double k) = 0;

	virtual std::string getName() const = 0;

	virtual Shape* clone() const = 0;

	// перегрузка операторов

	bool operator<(Shape& right) const;

	friend std::ostream& operator<<(std::ostream& out, Shape* shape);
};