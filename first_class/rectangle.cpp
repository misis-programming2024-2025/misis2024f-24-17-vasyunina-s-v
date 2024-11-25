#include <iostream>

class Rectangle{
private:
	double width;
	double  height;

public:

	Rectangle(double w, double h) : width(w), height(h) {}

	double getWidth() const { return width; }

	double getHeight() const { return height; }

	double getPerimeter() const { return 2 * (width + height); }

	double getArea() const { return width * height; }

};


int main() {
	int x, y;
	std::cin >> x;
	std::cin >> y;
	Rectangle rectangle(x, y);
	std::cout << "Width: " << rectangle.getWidth() << std::endl;
	std::cout << "Height: " << rectangle.getHeight() << std::endl;
	std::cout << "Perimeter: " << rectangle.getPerimeter() << std::endl;
	std::cout << "Area: " << rectangle.getArea() << std::endl;
	return 0;
}