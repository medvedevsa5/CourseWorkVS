#include "rectangle.h"

Rectangle::Rectangle(point_t pointA_, point_t pointC_)
{
	this->pointA_ = pointA_;
	this->pointC_ = pointC_;

	double centerX = (this->pointC_.x - this->pointA_.x) / 2;
	double centerY = (this->pointA_.y - this->pointC_.y) / 2;

	center_ = { centerX, centerY };

	calculateFrameRect();
}

double Rectangle::getArea() const
{
	double vectorAC[2] = { this->pointC_.x - this->pointA_.x, this->pointC_.y - this->pointA_.y };
	double vectorDB[2] = { this->pointC_.x - this->pointA_.x, this->pointA_.y - this->pointC_.y };

	double scalarMultiply = abs(vectorAC[0] * vectorDB[1] - vectorAC[1] * vectorDB[0]);
	double area = 0.5 * scalarMultiply;

	return round(area * 10) / 10;
}

rectangle_t Rectangle::getFrameRect() const
{
	return frameRect_;
}

void Rectangle::move(double x, double y)
{
	this->pointA_.x += x;
	this->pointA_.y += y;

	this->pointC_.x += x;
	this->pointC_.y += y;

	this->center_.x += x;
	this->center_.y += y;

	calculateFrameRect();
}

void Rectangle::move(const point_t point)
{
	this->pointA_.x += point.x - center_.x;
	this->pointA_.y += point.y - center_.y;

	this->pointC_.x += point.x - center_.x;
	this->pointC_.y += point.y - center_.y;

	this->center_.x = point.x;
	this->center_.y = point.y;

	calculateFrameRect();
}

void Rectangle::scale(double k)
{
	pointA_.x = k * (pointA_.x - center_.x) + center_.x;
	pointA_.y = k * (pointA_.y - center_.y) + center_.y;

	pointC_.x = k * (pointC_.x - center_.x) + center_.x;
	pointC_.y = k * (pointC_.y - center_.y) + center_.y;

	calculateFrameRect();
}

std::string Rectangle::getName() const
{
	return "RECTANGLE";
}

Shape* Rectangle::clone() const
{
	return new Rectangle(this->pointA_, this->pointC_);
}

void Rectangle::calculateFrameRect()
{
	double width = pointC_.x - pointA_.x;
	double height = pointA_.y - pointC_.y;

	this->frameRect_ = rectangle_t{ width, height, center_ };
}
