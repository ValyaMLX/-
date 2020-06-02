#include <iostream>
#include "Figure.h"

//========//
// Points //
//========//
Points::Points(int x, int y)
    :x(x), y(y) {}


//========//
// Figure //
//========//
Figure::Figure() {}

Figure::Figure(Points* points, int* tops)
{
    this->points = points;
    this->tops = tops;
}

void Figure::GetName()
{
    std::cout << "Фигура" << std::endl;
}

float Figure::GetSquare()
{
    float* square = new float(0.0);

    for (int i = 0; i < *tops - 1; i++)
    {
        *square += 0.5 * abs(points[i].x * points[i + 1].y - points[i + 1].x * points[i].y);
    }
    *square += 0.5 * abs(points[*tops].x * points[0].y - points[0].x * points[*tops].y);

    return *square;
}

float Figure::GetPerimeter()
{
    float* perimeter = new float(0.0);

    for (int i = 0; i < *tops - 1; i++)
    {
        *perimeter += sqrt(pow(points[i + 1].x - points[i].x, 2) + pow(points[i + 1].y - points[i].y, 2));
    }
    *perimeter += sqrt(pow(points[*tops - 1].x - points[0].x, 2) + pow(points[*tops - 1].y - points[0].y, 2));

    return *perimeter;
}

Figure::~Figure()
{
    delete[] points;
    delete tops;
}


//===========//
// Rectangle //
//===========//
Rectangle::Rectangle(int w, int h)
    : Figure(new Points[4]{ Points(0, 0), Points(w, 0), Points(w, h), Points(0, h) }, new int(4)) {}

void Rectangle::GetName()
{
    std::cout << "Прямоугольник" << std::endl;
}


//========//
// Square //
//========//
Square::Square(int side)
    : Rectangle(side, side) {}

void Square::GetName()
{
    std::cout << "Квадрат" << std::endl;
}



//========//
// Circle //
//========//
Circle::Circle(int radius)
{
    this->radius = new int(radius);
}

void Circle::GetName()
{
    std::cout << "Круг" << std::endl;
}

float Circle::GetSquare()
{
    return 3.14 * pow(*radius, 2);
}

float Circle::GetPerimeter()
{
    return 2 * 3.14 * *radius;
}

Circle::~Circle()
{
    delete radius;
}


//=========//
// Ellipse //
//=========//
Ellipse::Ellipse(int r, int R)
{
    this->r = new int(r);
    this->R = new int(R);
}

void Ellipse::GetName()
{
    std::cout << "Эллипс" << std::endl;
}

float Ellipse::GetSquare()
{
    return 3.14 * *r * *R;
}

float Ellipse::GetPerimeter()
{
    return 2 * 3.14 * sqrt(pow(*r, 2) * pow(*R, 2) / 2);
}

Ellipse::~Ellipse()
{
    delete r, R;
}
