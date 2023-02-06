#include "pixel.h"
#include <cmath>
using namespace std;

double pixel::getX(){
    return x;
}
double pixel::getY(){
    return y;
}

void pixel::set(double x1, double y1){
    x=x1;
    y=y1;
}

pixel pixel::operator+(pixel b) {
    pixel c;
    c.x = x + b.x;
    c.y = y + b.y;
	return c;
}

pixel pixel::operator-(pixel b) {
    pixel c;
    c.x = x - b.x;
    c.y = y - b.y;
	return c;
}

pixel pixel::operator*(double lambda) {
    pixel c;
    c.x = x * lambda;
    c.y = y * lambda;
	return c;
}

pixel pixel::operator/(double lambda) {
    pixel c;
    c.x = x / lambda;
    c.y = y / lambda;
	return c;
}

double pixel::operator*(pixel b) {
    return x * b.x + y * b.y;
}

double pixel::norm() {
    return sqrt( x * x + y * y );
}

pixel pixel::rotate(double angle) {
	angle *= M_PI / 180;
    pixel c;
	double co = cos(angle);
	double si = sin(angle);
    c.x = co * x + si * y;
    c.y = - si * x + co * y;
	return c;
}

