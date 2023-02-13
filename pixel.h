#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

class pixel {
    double x,y;     // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool v;         // 0 if not visited yet, 1 else
    //coucou

public:
    double getX();
    double getY();
    Color getColor();
    double getConfidence();
    double getData();
    double getPriority();
    bool getV();

    void setPixel(double x1, double y1, Color col1, double c1, double d1, bool v1);
    void setBlanck(double x1, double y1);    // To initialize the pixels in the target zone
};


