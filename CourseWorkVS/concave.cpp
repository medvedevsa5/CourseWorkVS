#include "stanislaw_lib.h"
#include "concave.h"
#include "base_types.h"
#include <algorithm>
#include <iostream>
#include <cmath>

#define COS_ALGORITHM
#define LINE_ALGORITHM

Concave::Concave(point_t pointA, point_t pointB, point_t pointC, point_t pointD)
{
	this->pointA_ = pointA;
	this->pointB_ = pointB;
	this->pointC_ = pointC;
	this->pointD_ = pointD;

	if (!this->isContainTriangle() || !this->isPointIncluded())
	{
		throw std::exception("Это не выпуклый четырёхугольник");
	}

	calculateFrameRect();
}

double Concave::getArea() const
{
	double lengthAB = this->pointA_.getDistance(this->pointB_);
	double lengthBC = this->pointB_.getDistance(this->pointC_);
	double lengthAC = this->pointA_.getDistance(this->pointC_);

	double lengthAD = this->pointA_.getDistance(this->pointD_);
	double lengthCD = this->pointA_.getDistance(this->pointC_);

	double semiperimeterBig = (lengthAB + lengthBC + lengthAC) / 2;
	double semiperimeterSmall = (lengthAD + lengthCD + lengthAC) / 2;

	double bigTriangleArea = 
		sqrt(semiperimeterBig *
		(semiperimeterBig - lengthAB) *
		(semiperimeterBig - lengthBC) *
		(semiperimeterBig - lengthAC));

	double smallTriangleArea = 
		sqrt(semiperimeterSmall *
			(semiperimeterSmall - lengthAD) *
			(semiperimeterSmall - lengthCD) *
			(semiperimeterSmall - lengthAC));

	double concaveArea = bigTriangleArea - smallTriangleArea;

	return concaveArea;
}

rectangle_t Concave::getFrameRect() const
{
	return this->frameRect_;
}

void Concave::move(double x, double y)
{
	this->pointA_.x += x;
	this->pointA_.y += y;

	this->pointB_.x += x;
	this->pointB_.y += y;
	
	this->pointC_.x += x;
	this->pointC_.y += y;

	this->pointD_.x += x;
	this->pointD_.y += y;

	calculateFrameRect();
}

void Concave::move(point_t point)
{
	this->pointA_.x += point.x - pointD_.x;
	this->pointA_.y += point.y - pointD_.y;

	this->pointC_.x += point.x - pointD_.x;
	this->pointC_.y += point.y - pointD_.y;

	this->pointB_.x += point.x - pointD_.x;
	this->pointB_.x += point.x - pointD_.x;

	this->pointD_.x = point.x;
	this->pointD_.y = point.y;

	calculateFrameRect();
}

void Concave::scale(double k)
{
	pointA_.x = k * (pointA_.x - pointD_.x) + pointD_.x;
	pointA_.y = k * (pointA_.y - pointD_.y) + pointD_.y;

	pointB_.x = k * (pointB_.x - pointD_.x) + pointD_.x;
	pointB_.y = k * (pointB_.y - pointD_.y) + pointD_.y;

	pointC_.x = k * (pointC_.x - pointD_.x) + pointD_.x;
	pointC_.y = k * (pointC_.y - pointD_.y) + pointD_.y;

	calculateFrameRect();
}

std::string Concave::getName() const
{
	return "CONCAVE";
}

Shape* Concave::clone() const
{
	return new Concave(this->pointA_, this->pointB_, this->pointC_, this->pointD_);
}


// private methods

bool Concave::isPointIncluded() const
{

	// если точка лежит в треугольке, то сумма косинусов углов между векторами DA DB DC меньше -1 (нашёл сам)
	
#if defined COS_ALGORITHM or (defined COS_ALGORITHM == defined LINE_ALGORITHM)

	bool result = true;

	double tensorA[2] = { this->pointA_.x - this->pointD_.x, this->pointA_.y - this->pointD_.y };
	double tensorB[2] = { this->pointB_.x - this->pointD_.x, this->pointB_.y - this->pointD_.y }; 
	double tensorC[2] = { this->pointC_.x - this->pointD_.x, this->pointC_.y - this->pointD_.y };

	double tensorLengthA = this->pointD_.getDistance(this->pointA_);
	double tensorLengthB = this->pointD_.getDistance(this->pointB_);
	double tensorLengthC = this->pointD_.getDistance(this->pointC_);

	double cosAlpha = (tensorA[0] * tensorB[0] + tensorA[1] * tensorB[1]) / (tensorLengthA * tensorLengthB);
	double cosBeta = (tensorB[0] * tensorC[0] + tensorB[1] * tensorC[1]) / (tensorLengthB * tensorLengthC);
	double cosGamma = (tensorA[0] * tensorC[0] + tensorA[1] * tensorC[1]) / (tensorLengthA * tensorLengthC);

	return cosAlpha + cosBeta + cosGamma < -1 && !(cosAlpha + cosBeta + cosGamma + 1 < EPSILON);

#endif

	// мне очень понравился мой изначальный алгоритм, основанный на трёх неравенствах уравнения прямой, проходящей через 2 точки.
	// поэтому не хотел его удалять, решил просто его как альтернативу оставить

#if defined LINE_ALGORITHM and !defined COS_ALGORITHM

	bool result = false;

	double tensorDA[2]= {this->pointA.x - this->pointD.x, this->pointA.y - this->pointD.y };
	double tensorDB[2]= {this->pointB.x - this->pointD.x, this->pointB.y - this->pointD.y }; 

	double productTensorProjection = tensorDA[0] * tensorDB[1] - tensorDA[1] * tensorDB[0];
	
	point_t pointArray[4] = { this->pointA, this->pointB, this->pointC, this->pointA };

	// расположены ли точки A, B, C по часовой стрелке.
	bool isClockwise = !(productTensorProjection > 0);

	// определение порядка обхода массива - с начала или с конца.
	int i = !isClockwise ? 0 : 2;
	int k = !isClockwise ? 1 : -1;

	while ((i >= 0 && i < 3) && result != false)
	{
		result = (this->pointD.y - pointArray[i].y) * (pointArray[i + 1].x - pointArray[i].x)
			- (this->pointD.x - pointArray[i].x) * (pointArray[i + 1].y - pointArray[i].y) > 0;

		i += k;
	}

	return result;

#endif
}


// в задании меня просят проверить, является ли ABC треугольником
// это очень странно, ведь в условии гарантировано, что фигуры не самопересекающиеся

bool Concave::isContainTriangle() const
{
	double lengthAB = this->pointA_.getDistance(this->pointB_);
	double lengthBC = this->pointB_.getDistance(this->pointC_);
	double lengthAC = this->pointA_.getDistance(this->pointC_);

	double lengthArray[3] = { lengthAB, lengthBC, lengthAC };

	std::sort(std::begin(lengthArray), std::end(lengthArray));

	return lengthArray[0] + lengthArray[1] > lengthArray[2] && !(lengthArray[0] + lengthArray[1] + lengthArray[2] + 1 < EPSILON);
}

void Concave::calculateFrameRect()
{
	double xArray[3] = { this->pointA_.x, this->pointB_.x, this->pointC_.x };
	double yArray[3] = { this->pointA_.y, this->pointB_.y, this->pointC_.y };

	std::sort(std::begin(xArray), std::end(xArray));
	std::sort(std::begin(yArray), std::end(yArray));

	point_t intersectionA = { xArray[0], yArray[2] };
	point_t intersectionC = { xArray[2], yArray[0] };

	double width = xArray[2] - xArray[0];
	double height = yArray[2] - yArray[0];

	point_t center = point_t{ (intersectionC.x - intersectionA.x) / 2 + intersectionA.x,
							  (intersectionC.y - intersectionA.y) / 2 + intersectionA.y };

	this->frameRect_ = rectangle_t{ width, height, center };
}
