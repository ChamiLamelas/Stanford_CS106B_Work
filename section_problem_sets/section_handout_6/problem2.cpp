#include <stdexcept>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\testing_lib.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\testing_lib.cpp"
using namespace std;

class Rectangle {
    public:
        Rectangle(double initLength, double initWidth, double initX = 0, double initY = 0);
        double getPerimeter() const;
        double getArea() const;
        void translate(double deltaX, double deltaY);
        void scale(double lengthScaleFactor, double widthScaleFactor);
        double getWidth() const;
        double getLength() const;
        double getBtmLeftX() const;
        double getBtmLeftY() const;

    private:
        double length, width; 
        double btmLeftX, btmLeftY;
};

Rectangle::Rectangle(double initLength, double initWidth, double initX, double initY) {
    if (initLength < 0 || initWidth < 0) {
        throw invalid_argument("Length & width must be positive.");
    }
    length = initLength;
    width = initWidth;
    btmLeftX = initX;
    btmLeftY = initY;
}

double Rectangle::getPerimeter() const {
    return 2*length + 2*width;
}

double Rectangle::getArea() const {
    return length*width;
}

void Rectangle::translate(double deltaX, double deltaY) { 
    btmLeftX += deltaX;
    btmLeftY += deltaY;
}

void Rectangle::scale(double lengthScaleFactor, double widthScaleFactor) {
    if (lengthScaleFactor < 0 || widthScaleFactor < 0) {
        throw invalid_argument("Scale factors must be >= 0.");
    }
    length *= lengthScaleFactor;
    width *= widthScaleFactor;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getLength() const {
    return length;
}

double Rectangle::getBtmLeftX() const {
    return btmLeftX;
}

double Rectangle::getBtmLeftY() const {
    return btmLeftY;
}

int main() {
    Tester t;
    Rectangle r(10, 5);
    t.report(r.getLength(), 10.0);
    t.report(r.getWidth(), 5.0);
    t.report(r.getBtmLeftX(), 0.0);
    t.report(r.getBtmLeftY(), 0.0);
    t.report(r.getArea(), 50.0);
    t.report(r.getPerimeter(), 30.0);
    r.translate(-5, 5);
    t.report(r.getBtmLeftX(), -5.0);
    t.report(r.getBtmLeftY(), 5.0);
    r.translate(-5, 5);
    t.report(r.getBtmLeftX(), -10.0);
    t.report(r.getBtmLeftY(), 10.0);
    r.scale(0.5, 2);
    t.report(r.getLength(), 5.0);
    t.report(r.getWidth(), 10.0);
    t.report(r.getArea(), 50.0);
    t.report(r.getPerimeter(), 30.0);
    r.scale(0, 0);
    t.report(r.getLength(), 0.0);
    t.report(r.getWidth(), 0.0);
    t.report(r.getArea(), 0.0);
    t.report(r.getPerimeter(), 0.0);
    return 0;
}
