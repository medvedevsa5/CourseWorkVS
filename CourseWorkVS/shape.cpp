#include "stanislaw_lib.h"
#include "shape.h"
#include <iostream>


std::ostream& operator<<(std::ostream& output, Shape* shape)
{
	output << shape->getName() << " ";
	output << shape->getArea() << " ";
	output << shape->getFrameRect().getCorner(false, true) << " ";
	output << shape->getFrameRect().getCorner(true, false);

	return output;
}

bool Shape::operator<(Shape& right) const
{
	double leftArea = this->getArea();
	double rightArea = right.getArea();

	return leftArea < rightArea && !(leftArea - rightArea < EPSILON);
}
