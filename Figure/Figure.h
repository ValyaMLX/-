#ifndef FIGURE_H 
#define FIGURE_H

struct Points
{
    int x, y;

    Points(int x, int y);
};

class Figure
{
    private:
        Points* points = nullptr;
        int* tops = nullptr;
    public:
        Figure();

        Figure(Points* points, int* tops);

        virtual void GetName();

        virtual float GetSquare();

        virtual float GetPerimeter();
        
        ~Figure();
};

class Rectangle : public Figure
{
    public:
        Rectangle(int w, int h);

        void GetName();
};

class Square : public Rectangle
{
    public:
        Square(int side);

        void GetName();
};

class Circle : public Figure
{
    private:
        int* radius = nullptr;
    public:
        Circle(int radius);

        void GetName();

        float GetSquare();

        float GetPerimeter();

        ~Circle();
};

class Ellipse : public Figure
{
    private:
        int* r = nullptr;
        int* R = nullptr;
    public:
        Ellipse(int r, int R);

        void GetName();

        float GetSquare();

        float GetPerimeter();

        ~Ellipse();
};

#endif 

