#include "pixel.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;


/* ******************************* */

double pixel::getX(){
    return x;
}
double pixel::getY(){
    return y;
}

Color pixel::getColor(){
    return col;
}
double pixel::getConfidence(){
    return c;
}
double pixel::getData(){
    return d;
}
double pixel::getPriority(){
    return c*d;
}
bool pixel::getV(){
    return v;
}


void pixel::setPixel(double x1, double y1, Color col1, double c1, double d1, bool v1){
    x=x1;
    y=y1;
    col=col1;
    c=c1;
    d=d1;
    v=v1;
}
void pixel::setBlanck(double x1, double y1){
    x=x1;
    y=y1;
}
