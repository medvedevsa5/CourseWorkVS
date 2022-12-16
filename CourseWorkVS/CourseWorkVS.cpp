#define MAX_SHAPES_COUNT 100

#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "rectangle.h"
#include "concave.h"
#include "base_types.h"
#include "stanislaw_lib.h"

Shape** shapeSort(Shape** shapeArray, size_t shapeArrayLength);

int main()
{
	setlocale(LC_ALL, "ru");

	std::ifstream inputFile("test.txt");
	if(!inputFile.is_open())
	{
		std::cout << "Не открылся файл с тестом!";
		return -1;
	}
	
	int lineCount = std::count(std::istreambuf_iterator<char>(inputFile),
							   std::istreambuf_iterator<char>(), '\n');
	lineCount += 1;
	inputFile.clear();
	inputFile.seekg(0);

	Shape** shapeArray = new Shape*[lineCount];
	for (size_t i = 0; i < lineCount; i++)
	{
		shapeArray[i] = nullptr;
	}

	int writedCount = 0;
	for (size_t i = 0; i < lineCount; i++)
	{
		std::string command = "";
		inputFile >> command;
		int commandCode = getCommandCode(command);

		switch (commandCode)
		{
		case RECTANGLE:
			point_t rectanglePointA = point_t{ 0, 0 };
			point_t rectanglePointC = point_t{ 0, 0 };

			inputFile >> rectanglePointA >> rectanglePointC;
			if (!inputFile)
			{
				std::cerr << "Точки заданы неправильно!";
				break;
			}

			shapeArray[writedCount] = new Rectangle(rectanglePointA, rectanglePointC);
			writedCount += 1;

			break;
		case CONCAVE:
			point_t concavePointA = point_t{ 0, 0 };
			point_t concavePointB = point_t{ 0, 0 };
			point_t concavePointC = point_t{ 0, 0 };
			point_t concavePointD = point_t{ 0, 0 };

			inputFile >> concavePointA >> concavePointB >> concavePointC >> concavePointD;
			if (!inputFile)
			{
				std::cerr << "Точки заданы неправильно!";
				break;
			}

			try
			{
				shapeArray[writedCount] = new Concave(concavePointA, concavePointB, concavePointC, concavePointD);
			}
			catch (std::exception& e)
			{
				std::cerr << "Фигура задана неверно - " << e.what();
				break;
			}
			writedCount += 1;

			break;
		case COMPLEX:



			break;
		case MOVE:

			for (int i = 0; i < lineCount; i++)
			{
				double xOffset = 0;
				double yOffset = 0;

				inputFile >> xOffset >> yOffset;

				shapeArray[writedCount]->move(xOffset, yOffset);
			}

			break;
		case SCALE:



			break;
		default:
			std::cerr << "Строка # " << i + 1 << " : команда не найдена" << std::endl;
			break;
		}
	}

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		std::cerr << "Не удалось открыть файл вывода";
		return -1;
	}

	shapeArray = shapeSort(shapeArray, writedCount);

	outputFile.precision(1);
	for (size_t i = writedCount; i > 0; i--)
	{
		outputFile << std::fixed << shapeArray[i - 1] << std::endl;
	}


	inputFile.close();
	outputFile.close();
	for (size_t i = 0; i < writedCount; i++)
	{
		delete shapeArray[i];
	}
	delete[] shapeArray;

	return 0;
}

Shape** shapeSort(Shape** shapeArray, size_t shapeArrayLength)
{
	int j = 0;

	Shape* buffer = nullptr;
	for (size_t i = 1; i < shapeArrayLength; i++)
	{
		buffer = shapeArray[i];
		for (size_t j = i; j >= 1 && !(*shapeArray[j - 1] < *buffer); j--)
		{
			shapeArray[j] = shapeArray[j - 1];
		}
		shapeArray[j] = buffer;
	}

	if (!(*shapeArray[shapeArrayLength - 2] < *shapeArray[shapeArrayLength - 1]))
	{
		std::swap(shapeArray[shapeArrayLength - 2], shapeArray[shapeArrayLength - 1]);
	}

	return shapeArray;
}

Shape* getShape(CommandCode command, point_t* params)
{
	
	switch (command)
	{
	case RECTANGLE:
		return new Rectangle(params[0], params[1]);
		break;
	case CONCAVE:
		return new Concave(params[0], params[1], params[2], params[3]);
		break;
	default:
		throw std::exception("Такая фигура не реализована! ");
		break;
	}

	return nullptr;
}