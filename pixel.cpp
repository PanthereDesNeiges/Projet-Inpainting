#include "pixel.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;


/* ******************************* */
pixel::pixel(int X,int Y){
    x=X;
    y=Y;
    v=false;
}

int pixel::getX(){
    return x;
}
int pixel::getY(){
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


void pixel::setConfidence(double conf){
    c=conf;
}

void pixel::setData(double dat){
    d=dat;
}

void pixel::setX(int val){
    x=val;
}

void pixel::setY(int val){
    y=val;
}

void pixel::setV(int v1){
    // v1 = 0 ou 1
    v = v1;
}

void pixel::initPixel(Color col1, double c1, double d1, bool v1){
    col=col1;
    c=c1;
    d=d1;
    v=v1;
}

void pixel::setBlanck(){
}

bool pixel::operator==( pixel p){
    return( col == p.getColor() and c== p.getConfidence() and d == p.getData() and v == getV());
}

const pixel& pixel::operator=(const pixel& p){
    x=p.x, y=p.y, col=p.col, c=p.c, d=p.d, v=p.v;
    return p;
}
