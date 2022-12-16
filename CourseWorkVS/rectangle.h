#pragma once

#include "base_types.h"
#include "shape.h"

class Rectangle : public Shape
{
private:
	point_t pointA_;
	point_t pointC_;
	point_t center_;

	rectangle_t frameRect_;
public:
	Rectangle(point_t pointA_, point_t pointC_);

	double getArea() const override;

	rectangle_t getFrameRect() const override;

	void move(const double x, const double y) override;

	void move(const point_t point) override;

	void scale(const double k) override;

	std::string getName() const override;

	Shape* clone() const override;

private:
	void calculateFrameRect();
};