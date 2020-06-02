#include <iostream>
#include "Figure.h"

int main()
{
    setlocale(0, "");

    const int count = 100;
    Figure* figure[count];

    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
            figure[i] = new Rectangle(i, i * 2);
        else if (i % 3 == 0)
            figure[i] = new Square(i);
        else if (i % 5 == 0)
            figure[i] = new Circle(i / 5);
        else
            figure[i] = new Ellipse(i / 2, i);
    }

    for (int i = 0; i < count; i++)
    {
        figure[i]->GetName();
        std::cout << "S = " << figure[i]->GetSquare() << std::endl;
        std::cout << "P = " << figure[i]->GetPerimeter() << std::endl;
        std::cout << "" << std::endl;
    }

    delete [] figure; 
 
    return 0;
}
