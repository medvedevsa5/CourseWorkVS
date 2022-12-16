#pragma once

#include "shape.h"

class Complex : public Shape
{
private:

	Shape** shapeArray_;
	size_t shapeArrayLength_;
	point_t center_;

	rectangle_t frameRect_;

public:

	Complex(Shape** array, size_t shapeCount);

	// Унаследовано через Shape
	virtual double getArea() const override;

	virtual rectangle_t getFrameRect() const override;
	
	virtual void move(double x, double y) override;
	
	virtual void move(point_t point) override;
	
	virtual void scale(double k) override;
	
	virtual std::string getName() const override;
	
	virtual Shape* clone() const override;

private:
	void calculateFrameRect();
};
