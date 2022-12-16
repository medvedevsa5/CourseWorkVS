#include "complex.h"
#include <algorithm>
#include <iterator>

Complex::Complex(Shape** array, size_t shapeCount)
{
    shapeArray_ = new Shape* [shapeCount];
    shapeArrayLength_ = shapeCount;

    for (size_t i = 0; i < shapeCount; i++)
    {
        shapeArray_[i] = array[i]->clone();
    }

    this->calculateFrameRect();
    this->center_ = getFrameRect().pos;
}

double Complex::getArea() const
{
    return this->getFrameRect().getArea();
}

rectangle_t Complex::getFrameRect() const
{
    return this->frameRect_;
}

void Complex::move(double x, double y)
{
    for (size_t i = 0; i < shapeArrayLength_; i++)
    {
        shapeArray_[i]->move(x, y);
    }

    center_.x += x;
    center_.y += y;

    this->calculateFrameRect();
}

void Complex::move(point_t point)
{
    for (size_t i = 0; i < shapeArrayLength_; i++)
    {
        shapeArray_[i]->move(point);
    }

    center_.x = point.x;
    center_.y = point.y;

    this->calculateFrameRect();
}

void Complex::scale(double k)
{
    for (size_t i = 0; i < shapeArrayLength_; i++)
    {
        rectangle_t rect = shapeArray_[i]->getFrameRect();
        
        double coordOffset[2] = { k * (rect.pos.x - this->center_.x) + this->center_.x,
                                  k * (rect.pos.y - this->center_.y) + this->center_.y };

        shapeArray_[i]->move(coordOffset[0], coordOffset[1]);
        shapeArray_[i]->scale(k);
    }

    this->calculateFrameRect();
}

std::string Complex::getName() const
{
    return "COMPLEX";
}

Shape* Complex::clone() const
{
    Complex* copy = new Complex(this->shapeArray_, this->shapeArrayLength_);

    return copy;
}

void Complex::calculateFrameRect()
{
    point_t maxPointA = point_t{ 0, 0 };
    point_t maxPointB = point_t{ 0, 0 };
    point_t maxPointC = point_t{ 0, 0 };
    point_t maxPointD = point_t{ 0, 0 };

    for (size_t i = 0; i < shapeArrayLength_ - 1; i++)
    {
        point_t pointA = this->shapeArray_[i]->getFrameRect().getCorner(false, false);
        point_t pointB = this->shapeArray_[i]->getFrameRect().getCorner(false, true);
        point_t pointC = this->shapeArray_[i]->getFrameRect().getCorner(true, true);
        point_t pointD = this->shapeArray_[i]->getFrameRect().getCorner(true, false);

        if (maxPointA < pointA)
        {
            maxPointA = pointA;
        }

        if (maxPointB < pointB)
        {
            maxPointB = pointB;
        }

        if (maxPointC < pointC)
        {
            maxPointC = pointC;
        }

        if (maxPointD < pointD)
        {
            maxPointD = pointD;
        }
    }

    double minimalX = std::min(maxPointA.x, maxPointB.x);
    double minimalY = std::min(maxPointA.x, maxPointD.x);
    double maximalX = std::max(maxPointC.x, maxPointD.x);
    double maximalY = std::min(maxPointB.x, maxPointC.x);

    point_t intersectionA = { minimalX, maximalY};
    point_t intersectionC = { maximalX, minimalY };

    double width = maximalX - minimalX;
    double height = maximalY - minimalY;

    point_t center = point_t{ (intersectionC.x - intersectionA.x) / 2 + intersectionA.x,
                              (intersectionC.y - intersectionA.y) / 2 + intersectionA.y };

    this->frameRect_ = rectangle_t{width, height, center};
}
