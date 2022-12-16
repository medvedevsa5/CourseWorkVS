#pragma once
#include "shape.h"


class Concave : public Shape
{
public:
	point_t pointA_;
	point_t pointB_;
	point_t pointC_;
	point_t pointD_;

	rectangle_t frameRect_;

public:

	Concave(point_t pointA, point_t pointB, point_t pointC, point_t pointD);

	// Унаследовано через Shape
	virtual double getArea() const override;

	virtual rectangle_t getFrameRect() const override;

	virtual void move(double x, double y) override;

	virtual void move(point_t point) override;

	virtual void scale(double k) override;

	virtual std::string getName() const override;

	virtual Shape* clone() const override;

private:

	bool isPointIncluded() const;

	bool isContainTriangle() const;

	void calculateFrameRect();
};