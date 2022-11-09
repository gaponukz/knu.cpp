#include <iostream>
#include <cmath>
using namespace std;

class Point {
    public:

    float x;
    float y;

    Point(): Point(0, 0) {}
    Point(float x, float y) {
        this -> x = x;
        this -> y = y;

    }

    void show() {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }

};

class Segment {
    public:

    Point start;
    Point end;
    
    Segment(Point start, Point end) {
        this -> start = start;
        this -> end = end;
    }

    void show() {
        cout << "Segment((" << start.x << ", " << start.y << "), (" << end.x << ", " << end.y << "))" << endl;
    }

    float length() {
        return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
    }

    Point average() {
        return Point((this->start.x + this->end.x) / 2, (this->start.y + this->end.y) / 2);
    }
};

class Triangle {
    public:
    Point point1;
    Point point2;
    Point point3;

    float side1length;
    float side2length;
    float side3length;

    Triangle(Point point1, Point point2, Point point3) {
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;

        this->side1length = Segment(point1, point2).length();
        this->side2length = Segment(point2, point3).length();
        this->side3length = Segment(point3, point1).length();
    }

    void show() {
        printf("Triangle((%f, %f), (%f, %f), (%f, %f))", point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
    }

    float perimeter() {
        return this->side1length + this->side2length + this->side3length;
    }

    float square() {
        const float p = this->perimeter() / 2;

        return sqrt(p * (p - this->side1length) * (p - this->side2length) * (p - this->side3length));
    }
};

int main(int argc, char **argv) {
    Segment segment(Point(2, 6), Point(4, 4));

    segment.show();
    segment.average().show();

    return 0;
}